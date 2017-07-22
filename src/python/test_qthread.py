from PyQt4 import QtGui, QtCore
from collections import deque
import time

class TestThread(QtCore.QThread):
    update = QtCore.pyqtSignal()

    def __init__(self, parent, q):
        super(TestThread, self).__init__(parent)
        self.q = q

    def run(self):
        i = 0
        while (True):
            if time.time() % 1 == 0:
                i += 1
                self.q.append("i = {}\n".format(i))
                self.update.emit()
                time.sleep(0.1)
