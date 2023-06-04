import threading
import time


class Timer(threading.Thread):
    def __init__(self, myHost, timeModel):
        super().__init__()
        self.myHost = myHost
        self.timeModel = timeModel

    def run(self):
        while True:
            TIME = self.timeModel.getTime()
            if TIME > 0:
                try:
                    time.sleep(TIME)
                    print("\n")
                    if self.myHost is not None:
                        # print(self.myHost.getHostName(self.myHost), "等待ACK超时")
                        print("等待ACK超时")
                        self.myHost.timeOut(self.myHost)
                        print("等待超时")
                    self.timeModel.setTime(0)
                except Exception as e:
                    print(e)