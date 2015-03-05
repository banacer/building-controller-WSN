#include <XBee.h>
#include <TF>
#include "kSeries.h"
#include <dht.h>


dht DHT1;
dht DHT2;

// Pin configuration

kSeries K_30(12,13);

#define DHT22_PIN_1 3
#define DHT22_PIN_2 5
#define dampCntrlPin 9

uint8_t payload[5] = {0,0,0,0,0};
uint8_t* data;
int dataLen;
int remoteID; 
short temp1, temp2, humid1, humid2;
XBee xbee = XBee();


Tx16Request tx = Tx16Request(remoteID, payload, sizeof(payload));
Rx16Response rx = Rx16Response();


short getTemperature1()
{
    int chk = DHT1.read22(DHT22_PIN_1);
    short data = (short) (DHT1.temperature*100);
    return data;

}

short getTemperature2()
{
    int chk = DHT2.read22(DHT22_PIN_2);
    short data = (short) (DHT2.temperature*100);
    return data;	
}

short getHumidity1()
{
    int chk = DHT1.read22(DHT22_PIN_1);
    short data = (short) (DHT1.humidity*100);
    return data;
}

short getHumidity2()
{
    int chk = DHT2.read22(DHT22_PIN_2);
    short data = (short) (DHT2.humidity*100);
    return data;
}

int cntrlDamper(int data)
{
	int dampCntrlVal = 0;
	dampCntrlVal = (255/100)* data;
	analogWrite(dampCntrlPin, dampCntrlVal);
	Serial.println(dampCntrlVal);
	return dampCntrlVal;
}


/*int getCO2()
{

}*/

void setup()
{
	Serial.begin(9600);
	xbee.setSerial(Serial);
}

void loop()
{
	delay(1500);
	xbee.readPacket();
	if(xbee.getResponse().isAvailable())
	{
		if(xbee.getResponse().getApiId() == RX_16_RESPONSE)
		{
			xbee.getResponse().getRx16Response(rx);
			data = rx.getData();
			remoteID = rx.getRemoteAddress16();
            dataLen = rx.getDataLength();

		    switch (data[0]) {

		        case 116: // 116 --> ascii decimal equivalent of t
		          	temp1 = getTemperature1();
                  	payload[0] = highByte(temp1);
					payload[1] = lowByte(temp1);

                  	temp2 = getTemperature2();
                  	payload[2] = highByte(temp2);
                  	payload[3] = lowByte(temp2);

					tx.setAddress16(remoteID);
					xbee.send(tx); 
	            break;

		        case 104: // 104 --> ascii decimal equivalent of h
		          	humid1 = getHumidity1();
					payload[0] = highByte(humid1);
					payload[1] = lowByte(humid1);

					humid2 = getHumidity2();
					payload[2] = highByte(humid2);
					payload[3] = lowByte(humid2);

					tx.setAddress16(remoteID);
					xbee.send(tx);
	          	break;

	          	case 100: // 100 --> ascii decimal equivalent of d
	          		if(data[1] < 0 || data[1] > 100)
	      			{
		   				Serial.print("Control Value OUT OF BOUNDS");
		   				payload[4] = 0;
	      			}
	      			else
	      			{
					   payload[4] = cntrlDamper(data[1]);
					   tx.setAddress16(remoteID);
					   xbee.send(tx);
              		}
	          	break;

		        case 99: // 99 --> ascii decimal equivalent of h
		          //int co2 = getCO2();
		          break;

		        default:
		          break;
		    }
		}

	}
}

