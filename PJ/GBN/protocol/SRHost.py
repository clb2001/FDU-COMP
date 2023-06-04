from timer.Timer import Timer
from timer.TimeModel import TimeModel
import socket
from protocol.MyHost import MyHost
import time
import sys


class SRHost(MyHost):
    sender_sent_set = set()
    sender_received_ACK_set = set()
    receiver_received_set = set()

    def __init__(self, RECEIVE_PORT, WINDOW_SIZE, DATA_NUMBER, TIMEOUT, name):
        super().__init__(RECEIVE_PORT, WINDOW_SIZE, DATA_NUMBER, TIMEOUT, name)
        self._sender_sent_set = set()
        self._sender_received_ACK_set = set()
        self._receiver_received_set = set()
        self._timeModel = TimeModel()
        self._timer = Timer(MyHost, self._timeModel)

    def sendData(self):
        self._timeModel.setTime(0)
        self._timer.start()
        while True:
            while self._next_seq < self._base + self.WINDOW_SIZE and self._next_seq <= self.DATA_NUMBER \
                    and (self._next_seq not in self._sender_sent_set):
                if self._next_seq % 5 != 0:
                    send = self.hostname + ": Sending to port " + str(self._dest_port) + ", Seq = " + str(self._next_seq)
                    send_data = send.encode()
                    addr = (self._dest_address, self._dest_port)
                    packet = send_data, addr
                    self._send_socket.sendto(*packet)
                    print(self.hostname, "发送到", self._dest_port, "端口 Seq = ", self._next_seq)
                else:
                    print("假装丢失Seq = ", self._next_seq)
                self._sender_sent_set.add(self._next_seq)
                if self._next_seq == self._base:
                    self._timeModel.setTime(self.TIMEOUT)
                self._next_seq += 1
                try:
                    time.sleep(0.3)
                except InterruptedError as e:
                    print("延迟被中断: ", e)
            buffer_size = 4096
            self._send_socket.settimeout(1)
            try:
                bytes, address = self._receive_socket.recvfrom(buffer_size)
            except socket.timeout:
                print(self.hostname, " 等待ACK超时")
                self._next_seq -= 1
                self._sender_sent_set.remove(self._next_seq)
                continue
            from_server = bytes.decode('utf-8')
            ack_index = from_server.index("ACK: ") + 5
            ack_str = from_server[ack_index:].strip()
            ack = int(ack_str)
            self._sender_received_ACK_set.add(ack)
            if self._base == ack:
                while self._base in self.sender_received_ACK_set:
                    self._base += 1
                print("\n当前窗口 base = ", self._base, " 最大发送到", (self._base + self.WINDOW_SIZE - 1), "\n")
                if ack >= self._base + self.WINDOW_SIZE:
                    assert False
                if self._base == self._next_seq:
                    self._timeModel.setTime(0)
                else:
                    self._timeModel.setTime(self.TIMEOUT)
                print(self.hostname, "收到了 ACK: ", ack)
                if self._base == self.DATA_NUMBER + 1:
                    self._timeModel.setTime(0)
                    print(self.hostname, "发送完毕，接收方反馈已全部正确接收")
                    sys.exit(0)

    def timeOut(self):
        temp = self._sender_sent_set.copy()
        temp.difference_update(self._sender_received_ACK_set)
        print("\n", temp, "\n")
        for i in temp:
            resend = self.hostname + ": Resending to port " + str(self._dest_port) + ", Seq = " + str(i)
            resend_data = resend.encode()
            addr = (self._dest_address, self._dest_port)
            packet = resend_data, addr
            self._send_socket.sendto(*packet)
            print(self.hostname, "重新发送到", self._dest_port, "端口，Seq = ", i)
            break

    def receiveData(self):
        rcv_base = 1
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
                seq = int(received[seq_index + 6:].strip())
                if rcv_base <= seq <= rcv_base + self.WINDOW_SIZE - 1:
                    self._receiver_received_set.add(seq)
                    print(self.hostname, "收到一个窗口内的分组，Seq = ", seq, "已确认\n")
                    if seq % 17 != 0:
                        MyHost.sendACK(self, seq, address[0], address[1])
                    else:
                        print(self.hostname, "假装丢失ACK: ", seq)
                    if seq == rcv_base:
                        while rcv_base in self.receiver_received_set:
                            rcv_base += 1
                elif rcv_base - self.WINDOW_SIZE <= seq < rcv_base - 1:
                    print(self.hostname, "收到一个已经确认过的分组，Seq = ", seq, "已再次确认")
                    MyHost.sendACK(self, seq, address[0], address[1])
                else:
                    print(self.hostname, "收到一个不在窗口内的分组，Seq = ", seq, "已舍弃")
