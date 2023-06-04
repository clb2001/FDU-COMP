import threading
from protocol import GBNHost


def gbn_server():
    host1_port = 808
    host2_port = 809

    server = GBNHost.GBNHost(host2_port, 1, 20, 1, "server")
    server.setDestPort(host1_port)

    def receive_data():
        try:
            server.receiveData()
        except Exception as e:
            print(e)

    thread = threading.Thread(target=receive_data)
    thread.start()


if __name__ == '__main__':
    gbn_server()