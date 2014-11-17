#include <XBee.h>
 
XBee xbee = XBee();

uint8_t data[100];
Tx16Request tx = Tx16Request(0X2190, data, sizeof(data));
Rx16Response rx = Rx16Response();
int data1 = 0, lastData;
int transVal = 0;
int ledPin = 9;
void setup()
{
	xbee.begin(9600);
	Serial.begin(9600);
        xbee.setSerial(Serial);
}

void pwm(int pin, int transVal)
{
   analogWrite(ledPin, transVal);     
   Serial.println("In pwm"); 
}

void loop()
{
	delay(1000);
	xbee.readPacket();
	if(xbee.getResponse().isAvailable())
	{  
		if(xbee.getResponse().getApiId() == RX_16_RESPONSE)
		{
			xbee.getResponse().getRx16Response(rx);
                        data1 = rx.getData(0);
                        int conData = (255/100) * data1;
			memcpy(data, rx.getData(), 100);
                        if((data1 < 0) || (data1 >100))
                        {
                          transVal = transVal;
                        }
                        else
                        {
                          transVal = conData;
                          pwm(ledPin, transVal);
                        }
                        Serial.print("transVa = ");
                        Serial.print(transVal);
                        Serial.println();
		}
		
      }

	
}
