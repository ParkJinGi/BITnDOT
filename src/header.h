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

/*unicode to data for module*/
unsigned char decoder(int unicode);
