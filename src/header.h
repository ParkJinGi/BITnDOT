#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include "queue.h"
#define MODULE_CNT 7

Queue queue;

int clock_pin[MODULE_CNT] = {29,};
int latch_pin[MODULE_CNT] = {28,};
int data_pin[MODULE_CNT] = {27,};

unsigned char SOL_NUM[6] = {
	0b00000010, 0b00000100, 0b00001000,
	0b00010000, 0b00100000, 0b01000000
};


