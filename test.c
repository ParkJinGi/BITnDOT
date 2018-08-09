#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringShift.h>

#define MODULE_CNT 6
int clock_pin[MODULE_CNT] = {29,};
int latch_pin[MODULE_CNT] = {28,};
int data_pin[MODULE_CNT] = {27,};

unsigned char SOL_NUM[6] = {
	0b00000010, 0b00000100, 0b00001000,
	0b00010000, 0b00100000, 0b01000000
};

/*shut down specific module*/
void clear(int module_num);

/*shut down every module*/
void clear_all();

/*control specific module*/
void control_module(int module_num, unsigned char data);


int main(){

	if(wiringPiSetup() == -1)
		return 1;
	
	for(int i=0;i<MODULE_CNT;i++){
		pinMode(latch_pin[i], OUTPUT);
		pinMode(clock_pin[i], OUTPUT);
		pinMode(data_pin[i], OUTPUT);
	}


	control_module(0, SOL_NUM[0]+SOL_NUM[1]);
	delay(5000);
	control_module(0, SOL_NUM[2]+SOL_NUM[3]);
	delay(5000);
	
	for(int i=0;i<6;i++){
		control_module(0, SOL_NUM[i]);
	   	delay(500);
		//clear(0);
	 }
}

void clear(int module_num){
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, 0x00);
	digitalWrite(latch_pin[module_num], HIGH);
 	delay(1);
}

void clear_all(){
	for(int i=0;i<MODULE_CNT;i++)
		clear(i);
}

void control_module(int module_num, unsigned char data){
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, data);
	digitalWrite(latch_pin[module_num], HIGH);
	delay(1);
}


