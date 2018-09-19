#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "stack.h"
#define MODULE_CNT 7

int clock_pin[MODULE_CNT] = {7,1,3,6,14,31,25};
int latch_pin[MODULE_CNT] = {9,16,2,5,13,11,24};
int data_pin[MODULE_CNT] = {8,15,0,4,12,10,23};

int back_button = 28;
int foward_button = 29;
//int speaker = 26;

unsigned char SOL_NUM[6] = {
	0b00000010, 0b00000100, 0b00001000,
	0b00010000, 0b00100000, 0b01000000
};
