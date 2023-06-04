import socket
from abc import ABC, abstractmethod


class MyHost(ABC):
    def __init__(self, RECEIVE_PORT, WINDOW_SIZE, DATA_NUMBER, TIMEOUT, name):
        self.WINDOW_SIZE = WINDOW_SIZE
        self.DATA_NUMBER = DATA_NUMBER
        self.TIMEOUT = TIMEOUT
        self.hostname = name
        self._send_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._receive_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self._receive_socket.bind(("0.0.0.0", RECEIVE_PORT))
        self._dest_port = 80
        self._next_seq = 1
        self._base = 1
        self._expected_seq = 1
        hostname = socket.gethostname()
        self._dest_address = socket.gethostbyname(hostname)

    def setDestPort(self, dest_port):
        self._dest_port = dest_port

    @abstractmethod
    def sendData(self):
        pass

    @abstractmethod
    def timeOut(self):
        pass

    @abstractmethod
    def receiveData(self):
        pass

    def getHostName(self):
        return self.hostname

    def sendACK(self, seq, toAddr, toPort):
        response = self.hostname + " response ACK: " + str(seq)
        response_data = response.encode()
        addr = (toAddr, toPort)
        packet = response_data, addr
        self._receive_socket.sendto(*packet)