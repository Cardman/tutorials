import threading
import sys
import time
class AtomicInteger():
    def __init__(self, value=0):
        self._value = value
        self._lock = threading.Lock()

    def inc(self):
        with self._lock:
            self._value += 1
            return self._value

    def dec(self):
        with self._lock:
            self._value -= 1
            return self._value

    @property
    def value(self):
        with self._lock:
            return self._value

    @value.setter
    def value(self, v):
        with self._lock:
            self._value = v
            return self._value
class Calcul(threading.Thread):
    def __init__(self, at):
        threading.Thread.__init__(self)
        self.at = at
        self.i = 0

    def run(self):
        while self.i < 20:
            time.sleep(1)
            self.i += 1
        at.dec()

class Etat(threading.Thread):
    def __init__(self,aff, at):
        threading.Thread.__init__(self)
        self.aff = aff
        self.at = at

    def run(self):
        while self.at.value:
            print(self.aff.i)
            time.sleep(0.25)

at = AtomicInteger(0)
at.inc()
thread_1 = Calcul(at)
thread_2 = Etat(thread_1,at)

thread_1.start()
thread_2.start()

thread_1.join()
thread_2.join()