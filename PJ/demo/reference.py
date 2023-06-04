from socket import *
from threading import *
import time

class MyTCP:
    __maxPackageSize = 1468
    __sysSocket: socket = None
    __srcSeqNumber = 0
    __dstSeqNumber = 0
    __srcAckNumber = 0
    __dstAckNumber = 0
    __dstHostName = None
    __dstPort = None
    __srcPort = -1
    __rtt = 0.5
    __condition = None
    __sendCondition = None
    __backdoorRecvThread = None
    __recvBuffer = []
    __recvCondition = None
    __state = 0
    __stateCondition = None
    __conn = None
    __acceptCondition = None
    __connectCondition = None
    __nextPort = 12500

    def __init__(self, sysSocket, dstHostName, dstPort, srcPort = -1):
        self.__sysSocket = sysSocket
        self.__sysSocket.settimeout(0.5)
        self.__dstHostName = dstHostName
        self.__dstPort = dstPort
        self.__srcPort = srcPort

        self.__condition = Condition()
        self.__sendCondition = Condition()
        self.__acceptCondition = Condition()
        self.__connectCondition = Condition()

        self.__state = 1
        self.__stateCondition = Condition()

        self.__backdoorRecvThread = Thread(target = self.__backdoorRecv, args = ())
        self.__backdoorRecvThread.start()

        self.__recvCondition = Condition()


    def __finActivity(self, passive):
        self.__sendCondition.acquire()
        self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, 0, 0, bytes(0), 0, 0, 1, 0), (self.__dstHostName, self.__dstPort))
        self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, 0, 0, bytes(0), 1, 0, 1, 0), (self.__dstHostName, self.__dstPort))
        self.__sendCondition.release()

    def setSrcSeqNumber(self, v):
        self.__srcSeqNumber = v

    def setDstSeqNumber(self, v):
        self.__dstSeqNumber = v

    def getDstSeqNumber(self):
        return self.__dstSeqNumber

    def getSrcSeqNumber(self):
        return self.__srcSeqNumber

    def __backdoorRecv(self):
        fileBuff = {}
        fileStart = 0
        fileEnd = -1
        state = 1

        while state == 1:
            package: bytes = bytes(0)

            self.__stateCondition.acquire()
            state = self.__state
            self.__stateCondition.release()

            try:
                package, addr = self.__sysSocket.recvfrom(2048)
            except Exception as e:
                continue

            if package.__len__() == 0:
                continue

            srcPort, dstPort, seqNumber, ackNumber, flag_ACK, flag_SYN, flag_FIN, flag_EOF, message, isValid = self.__resolvePackage(package)
            message: bytes

            size = message.__len__()

            if isValid:
                if flag_ACK == 1:
                    if flag_FIN == 1:
                        self.__closeByFin()
                        continue
                    elif flag_SYN == 1:
                        self.__dstSeqNumber = seqNumber
                        self.__dstPort = srcPort
                        self.__connectCondition.acquire()
                        self.__connectCondition.notify()
                        self.__connectCondition.release()
                        continue
                    self.__condition.acquire()
                    self.__dstAckNumber = ackNumber
                    self.__condition.notify()
                    self.__condition.release()



                elif flag_SYN == 1:
                    self.__SynActivity(addr, seqNumber)

                elif flag_FIN == 1:
                    self.__finActivity(1)

                if size > 0:
                    if flag_EOF == 1:
                        fileEnd = seqNumber + size

                    if self.__dstSeqNumber == seqNumber:
                        fileBuff[seqNumber] = message
                        i = seqNumber + size
                        self.__dstSeqNumber += size
                        while fileBuff.get(i) != None:
                            i += fileBuff[i].__len__()
                        self.__dstSeqNumber = i
                        self.__sendAck(i)

                        if i == fileEnd:
                            file = bytes(0)

                            j = fileStart

                            while j < fileEnd:
                                file += fileBuff[j]
                                j += fileBuff[j].__len__()

                            self.__recvCondition.acquire()
                            self.__recvBuffer.append(file)
                            self.__recvCondition.notify()
                            self.__recvCondition.release()
                            fileStart = fileEnd
                            fileEnd = -1
                            fileBuff.clear()
                    else:
                        fileBuff[seqNumber] = message
                        self.__sendAck(self.__dstSeqNumber)
            else:
                self.__sendAck(self.__dstSeqNumber)

    def __getPort(self):
        self.__nextPort += 1
        if self.__nextPort > 13000:
            self.__nextPort = 12500
        return self.__nextPort

    def __SynActivity(self, addr: tuple, seqNumber):
        srcPort = self.__getPort()
        dstPort = addr[1]
        tmpSocket = socket(AF_INET, SOCK_DGRAM)
        tmpSocket.bind(("", srcPort))

        conn = MyTCP(tmpSocket, addr[0], dstPort, srcPort)
        conn.setDstSeqNumber(seqNumber)

        self.__sendCondition.acquire()
        self.__sysSocket.sendto(self.__makePackage(srcPort, dstPort, conn.getSrcSeqNumber(), seqNumber, bytes(0), 1, 1, 0, 0), addr)
        self.__sendCondition.release()

        self.__conn = conn
        self.__acceptCondition.acquire()
        self.__acceptCondition.notify()
        self.__acceptCondition.release()

    def accept(self):
        self.__acceptCondition.acquire()
        self.__acceptCondition.wait()
        self.__acceptCondition.release()
        return self.__conn

    def __ackTimeOut(self, message: bytes, offset):
        end: int = 0
        flag_EOF = 0
        if offset + self.__maxPackageSize < message.__len__():
            end = offset + self.__maxPackageSize
        else:
            end = message.__len__()
            flag_EOF = 1

        try:
            self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, self.__srcSeqNumber + offset, self.__dstSeqNumber, message[offset: end], 0, 0, 0, flag_EOF), (self.__dstHostName, self.__dstPort))
        except Exception as e:
            pass

        self.__condition.acquire()
        self.__condition.notify()
        self.__condition.release()



    def __sendAck(self, seqNumber):

        package = self.__makePackage(self.__srcPort, self.__dstPort, 0, seqNumber, bytes(0), 1)
        self.__sendCondition.acquire()
        self.__sysSocket.sendto(package, (self.__dstHostName, self.__dstPort))
        self.__sendCondition.release()


    def recv(self, flag = 0, timeout = -1):
        self.__recvCondition.acquire()

        if self.__recvBuffer.__len__() == 0:
            if flag != 0:
                self.__recvCondition.release()
                return bytes(0)
            if timeout == -1:
                self.__recvCondition.wait()
            else:
                self.__recvCondition.wait(timeout)
        returnValue = self.__recvBuffer[0]
        del self.__recvBuffer[0]
        self.__recvCondition.release()
        return returnValue


    def send(self, message):
        message: bytes
        maxPackageSize = self.__maxPackageSize
        self.__condition.acquire()
        beginAckNumber = self.__dstAckNumber
        self.__condition.release()

        windowSize = 10 * maxPackageSize
        windowOffset = 0
        i = 0

        repeatAck = 0
        continueAck = 0

        size = message.__len__()

        if size == 0:
            return

        ackTimer = Timer(interval = self.__rtt, function = self.__ackTimeOut, args = (message, i))
        ackTimer.start()

        while windowOffset < size:
            if not ackTimer.is_alive():
                ackTimer = Timer(interval = self.__rtt, function = self.__ackTimeOut, args = (message, windowOffset))
                ackTimer.start()

            while i < windowOffset + windowSize and i < size:
                self.__sendCondition.acquire()
                if i + maxPackageSize < size:
                    self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, self.__srcSeqNumber + i, self.__dstSeqNumber, message[i: i + maxPackageSize]), (self.__dstHostName, self.__dstPort))
                    i += maxPackageSize
                else:
                    self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, self.__srcSeqNumber + i, self.__dstSeqNumber, message[i:], 0, 0, 0, 1), (self.__dstHostName, self.__dstPort))
                    i = size

                self.__sendCondition.release()

            self.__condition.acquire()
            self.__condition.wait(self.__rtt)

            ackLength = self.__dstAckNumber - beginAckNumber
            self.__condition.release()

            if ackLength > windowOffset:
                windowOffset = ackLength
                continueAck += 1
                if continueAck > windowSize:
                    windowSize += 10
                repeatAck = 0
                ackTimer.cancel()
            else:
                if windowSize > 5:
                    windowSize = windowSize / 2
                continueAck = 0
                repeatAck += 1

            if repeatAck == 2 or repeatAck % (windowSize / 2) == 0:
                repeatAck = windowSize / 2 + 1

                if ackTimer.is_alive():
                    ackTimer.cancel()
                ackTimer = Timer(interval = self.__rtt, function = self.__ackTimeOut, args = (message, windowOffset))

                self.__sendCondition.acquire()
                if windowOffset + maxPackageSize < size:
                    self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, self.__srcSeqNumber + windowOffset, self.__dstSeqNumber, message[windowOffset: windowOffset + maxPackageSize]), (self.__dstHostName, self.__dstPort))
                else:
                    self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, self.__srcSeqNumber + windowOffset, self.__dstSeqNumber, message[windowOffset:], 0, 0, 0, 1), (self.__dstHostName, self.__dstPort))
                ackTimer.start()
                self.__sendCondition.release()

        self.__srcSeqNumber += size

    def __makePackage(self, srcPort, dstPort, seqNumber, ackNumber, message, flag_ACK = 0, flag_SYN = 0, flag_FIN = 0, flag_EOF = 0):
        message: bytes
        line1 = (srcPort << 16) + dstPort
        line4 = (flag_ACK << 3) + (flag_SYN << 2) + (flag_FIN << 1) + flag_EOF
        checksum = srcPort + dstPort + (seqNumber & 0xffff) + ((seqNumber >> 16) & 0xffff) + (ackNumber & 0xffff) + ((ackNumber >> 16) & 0xffff) + line4

        i = 0
        while i < message.__len__() - 2:
            checksum += self.__parseShort(message[i : i + 2])
            i += 2
        while i < message.__len__():
            checksum += message[i]
            i += 1
        checksum &= 0xffff
        checksum <<= 16

        package = self.__getBytesInt(line1)
        package += self.__getBytesInt(seqNumber)
        package += self.__getBytesInt(ackNumber)
        package += self.__getBytesInt(line4 + checksum)
        package += message

        return package

    def close(self):
        if self.__dstPort != -1:

            i = 0
            while i < 10 and self.__state > 0:
                self.__stateCondition.acquire()
                self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, 0, 0, bytes(0), 0, 0, 1, 0), (self.__dstHostName, self.__dstPort))
                self.__stateCondition.release()
                time.sleep(self.__rtt)


        else:
            self.__stateCondition.acquire()
            self.__state = 0
            self.__stateCondition.release()

    def __closeByFin(self):
        self.__stateCondition.acquire()
        self.__state = 0
        self.__sysSocket.sendto(self.__makePackage(self.__srcPort, self.__dstPort, 0, 0, bytes(0), 0, 0, 1, 0), (self.__dstHostName, self.__dstPort))
        self.__stateCondition.release()

    def __resolvePackage(self, package: bytes):
        line1 = self.__parseInt(package[0: 4])
        srcPort = line1 >> 16
        dstPort = line1 & 0xffff
        seqNumber = self.__parseInt(package[4: 8])
        ackNumber = self.__parseInt(package[8: 12])
        line4 = self.__parseInt(package[12: 16])
        message = package[16:]

        checksum = srcPort + dstPort + (seqNumber & 0xffff) + ((seqNumber >> 16) & 0xffff) + (ackNumber & 0xffff) + ((ackNumber >> 16) & 0xffff) + (line4 & 15)
        i = 16
        while i < package.__len__() - 2:
            checksum += self.__parseShort(package[i : i + 2])
            i += 2
        while i < package.__len__():
            checksum += package[i]
            i += 1
        checksum &= 0xffff

        isValid = checksum == ((line4 >> 16) & 0xffff)
        flag_ACK = (line4 & 8) >> 3
        flag_SYN = (line4 & 4) >> 2
        flag_FIN = (line4 & 2) >> 1
        flag_EOF =  line4 & 1

        return srcPort, dstPort, seqNumber, ackNumber, flag_ACK, flag_SYN, flag_FIN, flag_EOF, message, isValid

    def __getBytesInt(self, i):
        i: int
        return bytes([(i >> 24) & 0xff, (i >> 16) & 0xff, (i >> 8) & 0xff, i & 0xff])

    def __parseInt(self, b):
        b: bytes
        return ((int(b[0])) << 24) | ((int(b[1])) << 16) | ((int(b[2])) << 8) | (int(b[3]))

    def __parseShort(self, b):
        b: bytes
        return ((int(b[0])) << 8) + (int(b[1]))

    def connect(self, addr: tuple):
        self.__sendCondition.acquire()
        self.__sysSocket.sendto(self.__makePackage(self.__srcPort, addr[1], self.__srcSeqNumber, 0, bytes(0), 0, 1, 0, 0), addr)
        self.__sendCondition.release()

        self.__connectCondition.acquire()
        try:
            self.__connectCondition.wait(5)
        except:
            raise Exception("错误：连接超时")
        self.__connectCondition.release()

    def setProxy(self, addr: tuple):
        self.__dstHostName = addr[0]
        self.__dstPort = addr[1]

    def __del__(self):
        self.close()