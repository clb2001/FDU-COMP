from timer.Timer import Timer
from timer.TimeModel import TimeModel
import socket
import time
from protocol.MyHost import MyHost


class GBNHost(MyHost):
    def __init__(self, RECEIVE_PORT, WINDOW_SIZE, DATA_NUMBER, TIMEOUT, name):
        super().__init__(RECEIVE_PORT, WINDOW_SIZE, DATA_NUMBER, TIMEOUT, name)
        self._timeModel = TimeModel()
        self._timer = Timer(MyHost, self._timeModel)

    def sendData(self):
        self._timeModel.setTime(0)
        self._timer.start()
        while True:
            while self._next_seq < self._base + self.WINDOW_SIZE and self._next_seq < self.DATA_NUMBER:
                if self._next_seq % 5 == 0:
                    print(self.hostname, "假装丢失Seq = ", self._next_seq)
                    self._next_seq += 1
                    continue
                send = self.hostname + ": Sending to port " + str(self._dest_port) + ", Seq = " + str(self._next_seq)
                send_data = send.encode()
                addr = (self._dest_address, self._dest_port)
                packet = send_data, addr # (b'client: Sending to port 809, Seq = 1', ('172.22.96.1', 809))
                self._send_socket.sendto(*packet)
                print(self.hostname, "发送到", self._dest_port, "端口 Seq =", self._next_seq)
                if self._next_seq == self._base:
                    self._timeModel.setTime(self.TIMEOUT)
                self._next_seq += 1

                try:
                    time.sleep(0.3)
                except InterruptedError as e:
                    print("延迟被中断: ", e)
                buffer_size = 4096

                bytes, address = self._receive_socket.recvfrom(buffer_size)
                print("self._base", self._receive_socket)
                from_server = bytes.decode('utf-8')
                ack_index = from_server.index("ACK: ") + 5
                ack_str = from_server[ack_index:].strip()
                ack = int(ack_str)
                self._base = ack + 1

                if self._base == self._next_seq:
                    self._timeModel.setTime(0)
                else:
                    self._timeModel.setTime(self.TIMEOUT)
                print(self.hostname, "接收到了ACK:", ack)
                if ack == self.DATA_NUMBER:
                    self._timeModel.setTime(0)
                    print(self.hostname, "发送完毕，接收方反馈已全部正确接收")
                    return

    def timeOut(self):
        print("resend", self._base)
        for i in range(self._base, self._next_seq):
            resend = self.hostname + ": Resending to port " + str(self._dest_port) + ", Seq = " + str(i)
            resend_data = resend.encode()
            addr = (self._dest_address, self._dest_port)
            packet = resend_data, addr
            self._send_socket.sendto(*packet)
            print(self.hostname, "重新发送到", self._dest_port, "端口，Seq = ", i)

    def receiveData(self):
        while True:
            self._receive_socket.settimeout(1)
            buffer_size = 4096
            try:
                received_data, address = self._receive_socket.recvfrom(buffer_size)
            except socket.timeout:
                print(self.hostname, " 等待下一个分组超时")
                continue
            received = received_data.decode('utf-8')
            seq_index = received.find("Seq = ")
            if seq_index == -1:
                print(self.hostname, "收到错误数据")
                MyHost.sendACK(self, self._expected_seq - 1, address[0], address[1])
            else:
                if int(received[seq_index + 6:].strip()) == self._expected_seq:
                    if self._expected_seq % 7 != 0:
                        MyHost.sendACK(self, self._expected_seq, address[0], address[1])
                    else:
                        print(self.hostname, " 假装丢失ACK: ", self._expected_seq)
                    print(self.hostname, " 期待的数据Seq =", self._expected_seq)
                    self._expected_seq += 1
                else:
                    print(self.hostname, " 期待的数据Seq =", self._expected_seq)
                    print(self.hostname, " 未收到预期编号")
                    MyHost.sendACK(self, self._expected_seq - 1, address[0], address[1])