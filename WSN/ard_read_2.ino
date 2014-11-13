#include <XBee.h>
#include <SoftwareSerial.h>
#define Rx 2
#define Tx 3
#define buffLen 30

SoftwareSerial XBee(Rx, Tx);
byte inBuff[buffLen];
int eoD = 0;


void setup()
{
  XBee.begin(9600);
  Serial.begin(9600);
}
void loop() 
{
  while(XBee.available() > 0)
  {
    for(int i = 0; i < buffLen; i++)
    {
      inBuff[i] = (byte) XBee.read();
      Serial.print(i);
      Serial.print('\t');
      Serial.print(inBuff[i], HEX);
      Serial.println();
    }  
    eoD = 1;
  }
  if(eoD == 1)
  {
    byte TxLen = inBuff[2];
    Serial.print("TxLen = ");
    Serial.print(TxLen, HEX);
    Serial.println();
    byte dataLen = inBuff[2] - 5;
    byte RxData[dataLen] ;
    for(int j = 8; j < dataLen; j++)
    {
      RxData[j] = inBuff[j];
      //Serial.println(RxData[j], HEX);
    }
    eoD = 0;
  }
    
             
}
