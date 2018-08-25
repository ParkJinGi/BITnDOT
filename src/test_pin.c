#include <wiringPi.h>
#include <wiringShift.h>
#include <stdio.h>

/************* 수정 금지 **************/
int clock_pin = 29; // 40번 핀
int latch_pin = 28; // 38번 핀
/*************************************/

int data_pin[26] = {8,9,7,0,2,3,12,13,14,30,21,22,23,24,25,15,16,1,4,5,6,10,11,31,26,27};

int physical_pin[26]={3,5,7,11,13,15,19,21,23,27,29,31,33,35,37,8,10,12,16,18,22,24,26,28,32,36};

void test(int i){
	digitalWrite(latch_pin, LOW);
	shiftOut(data_pin[i], clock_pin, MSBFIRST, 0xFF);
	digitalWrite(latch_pin, HIGH);
	delay(1000);
	digitalWrite(latch_pin, LOW);
	shiftOut(data_pin[i], clock_pin, MSBFIRST, 0x00);
	digitalWrite(latch_pin, HIGH);
	delay(1);
}

int main(){

	wiringPiSetup();	
	for (int i = 0;i < MODULE_CNT;i++) {
		pinMode(latch_pin, OUTPUT);
		pinMode(clock_pin, OUTPUT);
	}

	for(int i=0;i<26;i++)
		pinMode(data_pin[i], OUTPUT);

	printf("\n\n=================================== TEST CODE =======================================\n");
	for(int i=0;i<26;i++){
		printf(" >>>>>> %d 번 핀에 (physical pin) data pin을 연결하고 Enter를 누르시오. <<<<<<<<<<<,\n", physical_pin[i]);
		getchar();
		test(data_pin[i]);
	}

}
