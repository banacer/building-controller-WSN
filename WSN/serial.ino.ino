#include <SoftwareSerial.h>
#define Tx 3
#define Rx 2
char* incomingByte;

SoftwareSerial XBee(Rx, Tx);

void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
}
void loop()
{
  if(XBee.available() > 0)
  {
    char incomingByte = XBee.read(); 
    delay(100);
    Serial.write(incomingByte);
    //XBee.write(incomingByte);
  }
  if(Serial.available() > 0)
  {
    XBee.write(Serial.read());
  }
 // Serial.println("I got this ->");
  
}
