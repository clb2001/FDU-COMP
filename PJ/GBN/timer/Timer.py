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
            # print("TIME", TIME)
            if TIME > 0:
                try:
                    time.sleep(TIME)
                    # print("\n")
                    if self.myHost is not None:
                        print(self.myHost.getHostName(), "等待ACK超时")
                        self.myHost.timeOut()
                    self.timeModel.setTime(0)
                except Exception as e:
                    print(e)