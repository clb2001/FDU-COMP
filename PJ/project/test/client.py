import socket
from ref import crc16, packet
from UDT import UDT
import os
import time
import threading


def receive(sock, filename, IP_PORT):
    UDTER = UDT.UDT(0.005, 0.005)
    file = open(filename, "wb")
    log_filename = IP_PORT[0] + "_" + str(IP_PORT[1]) + "_" + "log.txt"
    log_file = open("../log/client/" + log_filename, "a+")
    log_file.write("-------------------------------\n")
    frame_expected = 0
    log_file.write("Receiving %s...\n" % filename)

    while True:
        pdu, addr = UDTER.recv(sock)
        if not pdu:
            break
        seq_num, crc_num, data = packet.extract(pdu)
        
        print('Got PDU', seq_num)

        crc_expected = crc16.crc16xmodem(data)
        if crc_expected != crc_num:
            log_file.write("%s: Receive PDU = %d, STATUS = DataErr, FRAME_EXPECTED = %d from %s\n" \
                           %(time.ctime(), seq_num, frame_expected, str(addr)))
            print("data with error")
            continue

        if seq_num == frame_expected:
            print('Got expected packet')
            log_file.write("%s: Receive PDU = %d,STATUS = OK, FRAME_EXPECTED = %d from %s\n" \
                           %(time.ctime(), seq_num, frame_expected, str(addr)))
            print('Sending ACK', frame_expected)
            UDTER.sendack(frame_expected, sock, addr)
            frame_expected += 1
            file.write(data)
        
        else:
            print('Got unexpected packet')
            log_file.write("%s: Receive PDU = %d, STATUS = NoErr, FRAME_EXPECTED = %d from %s\n" \
                           %(time.ctime(), seq_num, frame_expected, str(addr)))
            print('Sending ACK', frame_expected - 1)
            UDTER.sendack(frame_expected - 1, sock, addr)

    print("over")
    log_file.write("Receive succeed\n")
    log_file.write("-------------------------------\n\n\n")
    log_file.close()
    file.close()


def main():
    IP = ""
    PORT = 808
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    IP_PORT = (IP, PORT)
    sock.bind(IP_PORT)

    LIENT_DIR = os.path.dirname(__file__) + '/data/client'
    filename = LIENT_DIR + "/copy.jpg"

    lock = threading.Lock()
    lock.acquire()
    lock.release()
    receive_thread = threading.Thread(target = receive, args = (sock, filename, IP_PORT))
    receive_thread.start()
    receive_thread.join()


if __name__=='__main__':
    main()