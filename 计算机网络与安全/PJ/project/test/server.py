import socket
from udt import udt
import _thread
from timer import timer
import os
from ref import crc16, packet
import time
import threading

interval = 1
expected_ack = 0      #累计确认，只用维护一个
packets_num = 0
send_timer = timer.timer(interval)
log_filename = ""
mutex = _thread.allocate_lock()
UDTER = udt.UDT(0.005, 0.005)


def send(sock, filename, IP_PORT, RECEIVER_ADDR):
    global UDTER
    global mutex
    global expected_ack
    global packets_num
    global send_timer
    global log_filename

    # log printing
    log_filename = IP_PORT[0] + "_" + str(IP_PORT[1]) + "_" + "log.txt"
    log_file = open("../log/server/" + log_filename, "a+")
    file = open(filename,"rb")
    log_file.write("-------------------------------\n")
    log_file.write("%s send %s to %s\n" % (IP_PORT[0] + " " + str(IP_PORT[1]), filename, RECEIVER_ADDR[0] + " " + str(RECEIVER_ADDR[1])))

    packets = []
    seq_num = 0
    while True:
        data = file.read(512)    #data size
        if not data:
            break
        crc_num = crc16.crc16xmodem(data)    # calculate crc
        pdu = packet.make(seq_num, crc_num, data)    # make packet
        packets.append(pdu)
        seq_num += 1
    packets_num = len(packets)
    log_file.write("total %d packets(512bytes)\n" % packets_num)
    print('packets num:', packets_num)
    window_size = 200
    next_frame_to_send = 0

    #start receive ack thread
    THREAD = threading.Thread(target = receive,args = (sock, ))
    THREAD.start()
    overtime_flag = 0
    scale = 50
    start = time.perf_counter()
    pre = start
    while expected_ack < len(packets):
        mutex.acquire()
        while next_frame_to_send < expected_ack + window_size:
            if next_frame_to_send >= len(packets):
                break
            print('Sending packet', next_frame_to_send)
            if overtime_flag == 0:
                log_file.write("%s: Send frame = %d, STATUS = New, ACKed = %d to %s\n" % (time.ctime(), next_frame_to_send, expected_ack, str(RECEIVER_ADDR)))
            elif overtime_flag == 1:
                log_file.write("%s: Send frame = %d, STATUS = TO, ACKed = %d to %s\n" % (time.ctime(), next_frame_to_send, expected_ack, str(RECEIVER_ADDR)))
            send_timer.satrt(next_frame_to_send)
            UDTER.send(packets[next_frame_to_send], sock, RECEIVER_ADDR)
            next_frame_to_send += 1
        overtime_flag = 0
        if send_timer.overtime(expected_ack):
            print("overtime")
            overtime_flag = 1
            next_frame_to_send = expected_ack

        # print result
        if (time.perf_counter() - pre) > 1:
            pre = time.perf_counter()
            param = int(packets_num / 50)
            i = int(next_frame_to_send / param)
            a = '*' * i
            b = '.' * (scale - i)
            c = min((i / scale) * 100, 100)
            dur = pre - start
            print("\r{:^3.0f}%[{}->{}]{:.2f}s".format(c, a, b, dur), end='')
        mutex.release()
    print("\nover")
    UDTER.send(packet.make_empty(), sock, RECEIVER_ADDR)
    log_file.write("send succeed\n") 
    log_file.write("-------------------------------\n\n\n")
    file.close()
    log_file.close()

def receive(sock):
    global mutex
    global expected_ack
    global packets_num
    
    while True:
        ack, _ = UDTER.recvack(sock)
        print('Got Ack', ack)
        if ack >= expected_ack:
            mutex.acquire()
            expected_ack = ack + 1
            print('ack_expected', expected_ack)
            mutex.release()
        if expected_ack >= packets_num:
            break


def main():
    hostname = socket.gethostname()
    IP = socket.gethostbyname(hostname)
    PORT = 809
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    IP_PORT = (IP, PORT)
    sock.bind(IP_PORT)

    lock = threading.Lock()
    lock.acquire()
    LIENT_DIR = os.path.dirname(__file__) + '/data/server'
    filename = LIENT_DIR + "/data.jpg"
    RECEIVER_IP = socket.gethostbyname(hostname)
    RECEIVER_PORT = 808
    RECEIVER_IP_PORT = (RECEIVER_IP, RECEIVER_PORT)
    lock.release()

    send_thread = threading.Thread(target=send, args=(sock, filename, IP_PORT, RECEIVER_IP_PORT))
    send_thread.start()
    send_thread.join()


if __name__=='__main__':
    main()
