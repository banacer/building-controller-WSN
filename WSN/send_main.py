# -*- coding: utf-8 -*-
"""
Created on Wed Nov 12 11:36:53 2014

@author: krish
"""

import send_Xbee
from time import sleep

if __name__ == "__main__":
    xbee = send_Xbee.send_Xbee(serialport = "COM10")
    sleep(1)
    sent = xbee.Strng(data = 'Hello World', addr = 0x2191, options = 0x01, frameid = 0x00)
    xbee.close()

    