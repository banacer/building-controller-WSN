import serial
import os
import time
import sys
os.system('cls')
os.system('clear')

ser = serial.Serial('COM11', 9600)
while True:
    try:
        '''print ser.name'''
        '''ser.write("hello")'''
        time.sleep(1)
        '''print ser.read()'''
        dat = ser.read()
        ser.write(dat)
        
    except KeyboardInterrupt:
        ser.close()

        
if ser.open():
    ser.close()

def signal_handler(signal, frame):
    print 'You pressed Ctrl+C!'
    sys.exit(0)

signal.signal(signal.SIGINT, signal_handler)
print 'Press Ctrl+C'
while True:
    time.sleep(1)  
            
'''dat = ser.read()
ser.write(dat)
time.sleep(1)
except KeyboardInterrupt:
ser.close()'''


      
        
   
'''7E 00 10 01 00 FF FF 01 48 65 6C 6C 6F 20 57 6F 72 6C 64 E3'''    
    

