#include "decoder.h"

#ifndef FOR_TEST
#include <wiringPi.h>
#include <wiringShift.h>
#endif

/*init module*/
void InitModule();

/*shut down specific module*/
void clear(int module_num);

/*shut down every module*/
void clear_all();

/*control specific module*/
void control_module(int module_num, unsigned char data);
Queue queue;

void a(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int main() {

#ifndef FOR_TEST
	InitModule();
#endif
	InitQueue(&queue);
	
	Enqueue(&queue, SOL_NUM[0]);
	Enqueue(&queue, SOL_NUM[1]);
	Enqueue(&queue, SOL_NUM[2]);
	Enqueue(&queue, SOL_NUM[3]);
	Enqueue(&queue, SOL_NUM[4]);
	Enqueue(&queue, SOL_NUM[5]);

	Enqueue(&queue, SOL_NUM[0]+SOL_NUM[1]);
	Enqueue(&queue, SOL_NUM[2]+SOL_NUM[3]);
	Enqueue(&queue, SOL_NUM[4]+SOL_NUM[5]);

	Enqueue(&queue, SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]);
	Enqueue(&queue, SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5]);

	Enqueue(&queue, SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5]);
	/***************  Module test Code  *********************/
	while(1){
		a();
		printf("1번 솔레노이드 작동 ! \n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("2번 솔레노이드 작동 ! \n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("3번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("4번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("5번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("6번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("1번 2번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("3번 4번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("5번 6번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("1번 2번 3번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("4번 5번 6번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
		printf("모든 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		delay(5000);
		a();
	}
}

void clear(int module_num) {
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, 0x00);
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
	wiringPiSetup();
	for (int i = 0;i < MODULE_CNT;i++) {
		pinMode(latch_pin[i], OUTPUT);
		pinMode(clock_pin[i], OUTPUT);
		pinMode(data_pin[i], OUTPUT);
	}
}
