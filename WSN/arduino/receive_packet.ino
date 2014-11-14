#include <XBee.h>

XBee xbee = XBee();
XBeeResponse response = XBeeResponse();
// create reusable response objects for responses we expect to handle 
Rx16Response rx16 = Rx16Response();


uint8_t data[100];//={0,1,2,3};

Tx16Request tx16 = Tx16Request(0x5678, data, sizeof(data));
TxStatusResponse txStatus = TxStatusResponse();

int statusLed = 11;
int errorLed = 12;

void flashLed(int pin, int times, int wait) 
{
    
    for (int i = 0; i < times; i++) {
      digitalWrite(pin, HIGH);
      delay(wait);
      digitalWrite(pin, LOW);
      
      if (i + 1 < times) {
        delay(wait);
      }
    }
}

void setup() {
  
  pinMode(statusLed, OUTPUT);
  pinMode(errorLed, OUTPUT);
  // start serial
  Serial.begin(9600);
  xbee.setSerial(Serial);
}
// continuously reads packets, looking for RX16 
void loop() {
    
    xbee.readPacket();
    
    if (xbee.getResponse().isAvailable()) {
      // got something
      
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
        // got a rx packet
		xbee.getResponse().getRx16Response(rx16);
		//data = rx16.getData();
                memcpy(data,rx16.getData(),100);
                
                xbee.send(tx16);
                //flashLed(statusLed, 3, 5);
                
                // after sending a tx request, we expect a status response
                // wait up to 5 seconds for the status response
                if (xbee.readPacket(5000)) {
                    // got a response!
            
                    // should be a znet tx status            	
                	if (xbee.getResponse().getApiId() == TX_STATUS_RESPONSE) {
                	   xbee.getResponse().getZBTxStatusResponse(txStatus);
                		
                	   // get the delivery status, the fifth byte
                       if (txStatus.getStatus() == SUCCESS) {
                        	// success.  time to celebrate
                         	flashLed(statusLed, 5, 50);
                       } else {
                        	// the remote XBee did not receive our packet. is it powered on?
                         	flashLed(errorLed, 3, 500);
                       }
                    }      
                } else if (xbee.getResponse().isError()) {
                  //nss.print("Error reading packet.  Error code: ");  
                  //nss.println(xbee.getResponse().getErrorCode());
                  // or flash error led
                } else {
                  // local XBee did not provide a timely TX Status Response.  Radio is not configured properly or connected
                  flashLed(errorLed, 2, 50);
                }
        }  
    }     

}
