int analogreadPin = A0;
float voltage = 0;
int val = 0;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  delay (1000);
  val = analogRead(analogreadPin);
  Serial.print("Val = ");
  Serial.print(val);
  Serial.print('\t');
  voltage = val*(5.0/1023.0);
  Serial.print("Voltage = ");
  Serial.print(voltage);
  Serial.println();
 
  
}
