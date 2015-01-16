int pingPin[3] = {3, 5, 7};
int inc = 0, Pin;


short temp = 0, lowest, tempInch = 0, refVal = 11;
float inches, cm;
int duration = 0;


float time2cm(float duration)
{
	cm = duration/29.0/2.0;
	return cm;
}

float time2inch(short duration)
{
	float inch;
	inch = duration/74.0/2.0;
	return inch;
}


int getDuration(int Pin)
{
	pinMode(Pin, OUTPUT);
	digitalWrite(Pin, LOW);
	delayMicroseconds(2);
	digitalWrite(Pin, HIGH);
	delayMicroseconds(5);
	digitalWrite(Pin, LOW);

	pinMode(Pin, INPUT);
	duration = pulseIn(Pin, HIGH);
	return duration;

}

	
void setup()
{
	Serial.begin(9600);
}

void loop()
{  
	Pin = pingPin[inc % 3];
	duration = getDuration(Pin);
        Serial.print("Pin = ");
        Serial.println(Pin);
	Serial.println(duration);
	// time2cm(duration);
	// Serial.print("cm = ");
	// Serial.println(cm);
	inc++;
//	if(inc == 3)
//	{
//		inc = 0;
//	}
//	else
//	{
//		inc = inc;
//	}
	delay(1);

}
