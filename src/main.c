#include "header.h"

int main(){

	if(wiringPiSetup() == -1)
		return 1;

	for(int i=0;i<MODULE_CNT;i++){
		pinMode(latch_pin[i], OUTPUT);
		pinMode(clock_pin[i], OUTPUT);
		pinMode(data_pin[i], OUTPUT);
	}
}

unsigned char decoder(int unicode){

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
