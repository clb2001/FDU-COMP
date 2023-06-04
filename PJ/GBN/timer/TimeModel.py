import threading


class TimeModel:
    def __init__(self):
        self._lock = threading.Lock()
        self.time = 0

    def getTime(self):
        with self._lock:
            return self.time

    def setTime(self, time):
        with self._lock:
            self.time = time