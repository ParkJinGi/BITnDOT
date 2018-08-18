#include <wiringPi.h>
#include <wiringShift.h>
#include "header.h"

/*init module*/
void InitModule();

/*shut down specific module*/
void clear(int module_num);

/*shut down every module*/
void clear_all();

/*control specific module*/
void control_module(int module_num, unsigned char data);

void clear(int module_num) {
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, 0xFF);
	digitalWrite(latch_pin[module_num], HIGH);
	delay(1);
}

void clear_all() {
	for (int i = 0;i < MODULE_CNT;i++)
		clear(i);
}

void control_module(int module_num, unsigned char data) {
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, data);
	digitalWrite(latch_pin[module_num], HIGH);
	delay(1);
}

void InitModule(){
	if (wiringPiSetup() == -1)
		return 1;
	for (int i = 0;i < MODULE_CNT;i++) {
		pinMode(latch_pin[i], OUTPUT);
		pinMode(clock_pin[i], OUTPUT);
		pinMode(data_pin[i], OUTPUT);
	}
}
