#include <wiringPi.h>
#include <stdio.h>

#define SW  5
#define LED 1

int switchControl()
{
	int i;

	pinMode(SW, INPUT);
	pinMode(LED, OUTPUT);

	while(1)
	{
		if(digitalRead(SW) == LOW)
		{
			digitalWrite(LED,HIGH);
			delay(500);
			digitalWrite(LED,LOW);
		}
	};
	return 0;
}
int main(int argc,char** argv)
{
	wiringPiSetup();
	switchControl();

	return 0;
}
