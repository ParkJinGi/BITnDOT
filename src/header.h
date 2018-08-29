#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "queue.h"
#include "stack.h"
#define MODULE_CNT 7

int latch_pin[MODULE_CNT] = {8,0,12,30,23,15,6};
int clock_pin[MODULE_CNT] = {9,2,13,21,24,16,10};
int data_pin[MODULE_CNT] = {7,3,14,22,25,1,11};

int back_button = 28;
int foward_button = 29;
int speaker = 26;

unsigned char SOL_NUM[6] = {
	0b00000010, 0b00000100, 0b00001000,
	0b00010000, 0b00100000, 0b01000000
};
