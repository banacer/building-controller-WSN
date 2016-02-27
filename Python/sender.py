from time import sleep
import XBee
#from xbee import XBee

class Sender:
    def __init__(self,serial_,nodeId):
        self.xbee = XBee.XBee(serial_)
        self.nodeId = nodeId

    def sendDamperCmd(self, val):
        val = ['d', int(val)]
        self.xbee.Send(msg = val, addr = self.nodeId, options = 0x01, frameid = 0x00)
        #self.xbee.Receive()

    def getTemp(self):

        self.xbee.RxMessages.clear()
        self.xbee.Send(msg = 't', addr = self.nodeId, options = 0x01, frameid = 0x00)
        sleep(2)
        response = self.xbee.Receive()
        temp = float((response[7]<< 8) | response[8])/100.0
        print temp

    def getHum(self):
        self.xbee.RxMessages.clear()
        self.xbee.Send(msg = 'h', addr = self.nodeId, options = 0x01, frameid = 0x00)
        sleep(2)
        response = self.xbee.Receive()
        #print("Received: " + self.xbee.format(response))
        hum = float((response[7]<< 8) | response[8])/100.0
        print hum

    def getCO2(self):
        self.xbee.RxMessages.clear()
        self.xbee.Send(msg = 'c', addr = self.nodeId, options = 0x01, frameid = 0x00)
        response = self.xbee.Receive()
        print response


    
