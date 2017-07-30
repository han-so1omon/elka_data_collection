from PyQt4 import QtGui, QtCore
from collections import deque
import time

'''
import elka_comm__common as ec
import elka_comm__gnd_station as ec_gnd
'''

import elka_ground_port as egp
import elka


class ElkaCommPublishThread(QtCore.QThread):
    update = QtCore.pyqtSignal()

    def __init__(self, parent, q):
        super(ElkaCommPublishThread, self).__init__(parent)
        self.q = q
        self.port = egp.ElkaGroundPort.get_instance()

    def run(self):
        while (True):
            if time.time() % 1 == 0:
                get_msg_res = self.port.get_msg(
                                    self.port._elka_rcv_cmd,
                                    self.port._elka_ack_snd,
                                    True)
                self.q.append("Got a msg: {}\n".format(get_msg_res))
                #self.q.append("{}\n".format(self.port.beep()))
                self.update.emit()
                time.sleep(0.1)


class ElkaCommParseThread(QtCore.QThread):
    update = QtCore.pyqtSignal()

    def __init__(self, parent, q):
        super(ElkaCommParseThread, self).__init__(parent)
        self.q = q
        self.port = egp.ElkaGroundPort.get_instance()

    def run(self):
        while (True):
            if time.time() % 1 == 0:
                get_msg_res = self.port.get_msg(
                                    self.port._elka_rcv_cmd,
                                    self.port._elka_ack_snd,
                                    True)
                self.q.append("Got the msg: {}\n".format(get_msg_res))
                #self.q.append("{}\n".format(self.port.beep()))
                self.update.emit()
                time.sleep(0.1)


