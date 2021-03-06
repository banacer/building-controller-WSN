import sys
import send_Xbee
from time import sleep

# stuff to run always here such as class/def
def main():
    pass

if __name__ == "__main__":
   # stuff only to run when not called via 'import' here
   main()

print('getData(choice in string, address in HEX)')
print '\n choice?\n temp\n humid\n co2\nexit'
xbee = send_Xbee.send_Xbee(serialport = "/dev/ttyUSB0")
sleep(1)


def getData(choice, nodeID):
    """
    :param choice: is temp/ humid/ co2/ exit
    :param nodeID: 16 bit address of the device in HEX; example 0x1234
    :return: Value red from the sensor
    """
    while True:
        if choice == 'temp':
            xbee.rxI()
            xbee.sendInt(data = 't', addr = nodeID, options = 0x01,frameid = 0x00)
            xbee.rxI()
            sleep(2)
            xbee.rx()
        elif choice == 'humid':
            xbee.rxI()
            xbee.sendInt(data = 'h', addr = nodeID, options = 0x01, frameid = 0x00)
            xbee.rxI()
            sleep(2)
            xbee.rx()
        elif choice == 'co2':
            xbee.sendInt(data = 'c', addr = nodeID, options = 0x01, frameid = 0x00)
            xbee.rxI()
            sleep(2)
        # elif  choice == 'damper':
        #     xbee.rxI()
        #     cntrl_val = int(input('enter the damper control value: '))
        #     val = ['d', cntrl_val]
        #     xbee.sendInt(data = val, addr = nodeID, options = 0x01, frameid = 0x00)
        #     xbee.rxI()
        #     sleep(2)
        #     xbee.rx()
        elif choice == 'exit':
            sys.exit('System Exit!!')
        else :
            print 'wrong choice'
        return






