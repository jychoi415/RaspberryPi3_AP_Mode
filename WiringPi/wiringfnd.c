#include <wiringPi.h>
#include <stdio.h>

int fndControl(int num)
{
	int i;
	int gpiopins[4]={25,24,23,22};	// A,B,C,D : 31,33,35,37
	int number[10][4]={ {0,0,0,0},
						{0,0,0,1},
						{0,0,1,0},
						{0,0,1,1},
						{0,1,0,0},
						{0,1,0,1},
						{0,1,1,0},
						{0,1,1,1},
						{1,0,0,0},
						{1,0,0,1} };

	for(i=0;i<4;i++)
		pinMode(gpiopins[i],OUTPUT);
	for(i=0;i<4;i++)
		digitalWrite(gpiopins[i],number[num][i] ? HIGH : LOW);
	delay(1000);

	for(i=0;i<4;i++)
		digitalWrite(number[num][i], LOW);
	getchar();

	return 0;
}
int main(int argc,char **argv)
{
	int no;
	if(argc<2)
	{
		printf("Usage : %s NO\n",argv[0]);
		return -1;
	}
	no=atoi(argv[1]);
	wiringPiSetup();

	fndControl(no);

	return 0;
}
