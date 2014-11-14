# -*- coding: utf-8 -*-
"""
Created on Wed Nov 12 10:05:47 2014
@author: krish
"""

import serial


class send_Xbee:
    def __init__(self, serialport, baudrate = 9600):
        self.serialport = serialport
        self.set_serial = serial.Serial(port = serialport, baudrate = baudrate)
        print self.serialport
        
    def Strng(self, data, addr, options, frameid):
        self.data = data.encode('hex')
        self.addr = addr
        self.options = options
        self.frameid = frameid
        return self.send(data, addr, options, frameid)
        
    def send(self, data, addr, options, frameid ):   
        if not data:
            return 0
        print data
        
        make_frame = '7E 00 {:02X} 01 {:02X} {:02X} {:02X} {:02X}'.format(
                      len(data) + 5,
                      frameid,
                      (addr & 0xFF00) >> 8,
                      addr & 0x00FF,
                      options
                      )
        frame = bytearray.fromhex(make_frame)
        frame.extend(data)
        checksum = 0xFF - (sum(frame[3:]) & 0xFF)
        frame.append(checksum)
        print ("Tx: " + self.format(frame))
        return self.set_serial.write(frame)
        
    def format(self,data)   :
        return " ".join("{:02x}".format(b) for b in data)
        
    def close(self):
        return self.set_serial.close()
        
