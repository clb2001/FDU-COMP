import threading
from protocol import GBNHost


def gbn_client():
    host1_port = 808
    host2_port = 809

    client = GBNHost.GBNHost(host1_port, 1, 20, 1, "client")
    client.setDestPort(host2_port)

    def send_data():
        try:
            client.sendData()
        except Exception as e:
            print(e)

    thread = threading.Thread(target=send_data)
    thread.start()


if __name__ == '__main__':
    gbn_client()