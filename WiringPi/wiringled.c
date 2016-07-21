#include <wiringPi.h>
#include <stdio.h>

int ledControl(int gpio)
{
	int i;

	pinMode(gpio,OUTPUT);

	for(i=0;i<5;i++)
	{
		digitalWrite(gpio,HIGH);
		delay(300);
		digitalWrite(gpio,LOW);
		delay(300);
	}
	return 0;
}
int main(int argc,char** argv)
{
	int gno;

	if(argc < 2)
	{
		printf("Usage : %s GPIO_NO\n",argv[0]);
		return -1;
	}

	gno=atoi(argv[1]);

	wiringPiSetup();
	ledControl(gno);

	return 0;
}
