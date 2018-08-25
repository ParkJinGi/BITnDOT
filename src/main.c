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

/*queue for module*/
Queue queue_module;

/*queue for unicode*/
Queue queue_uni;

int main() {

#ifndef FOR_TEST
	InitModule();
#endif

	int module_num;
	InitQueue(&queue_module);
	InitQueue(&queue_uni);

	while(1){

		/*1. 버튼 눌렀을 때 카메라 찍기*/
		while(1)
		{
			while(1)
			{
				getchar(); // instead of button
				if(execl("/usr/bin/raspistill", "raspistill", "-t", "1", "-o", "image.jpg", NULL) < 0)
				{
					printf("ERROR : Capture\n");
				}
				else
					break;
			}

			if((fp = fopen("./image.jpg", "rb")) == NULL)
			{
				printf("ERROR : Cannot found image.\n");
			}
			else
				break;
		}

		/*2. OCR처리하고 큐에 유니코드 저장*/

		/*3. unicode를 이용하여 모듈을 제어하는 data로 바꾸어 다른 큐에 저장*/
		while(!IsEmpty(&queue_uni))
			Enqueue(&queue_module, decoder(Dequeue(&queue_uni)));

		while(!IsEmpty(&queue_module)){ // 한 번 스캔한 모든 문자열을 점자로 표현할 때 까지

			/*4. 7개 씩 모듈 제어*/
			for(module_num = 0;module_num < MODULE_CNT;module_num++){
				if(IsEmpty(&queue_module))
					break;
				else					
					control_module(module_num, Dequeue(&queue_module));

			}

			/*5. 다음 버튼을 누를 때 까지 대기*/
			getchar();

			/*6. 모듈 초기화*/
			clear_all();
		}

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
