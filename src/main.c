#include "decoder.h"

/*****************FOR Test with MODULES********************/
#ifdef FOR_MODULE

#include <wiringPi.h>
#include <wiringShift.h>

/*init module*/
void InitModule();

/*shut down specific module*/
void clear(int module_num);

/*shut down every module*/
void clear_all();

/*control specific module*/
void control_module(int module_num, unsigned char data);

#endif
/**********************************************************/

/*queue for module*/
Queue_char queue_module;

/*queue for unicode*/
Queue_int queue_uni;

/*Stack for Go back*/
Stack stack;

int main() {

	unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char) * 7);
	unsigned char tmp;
	int module_num;

	InitQueue_char(&queue_module);
	InitQueue_int(&queue_uni);
	InitStack(&stack);

#ifndef FOR_MODULE // Test를 위한 코드 .... 각자 컴퓨터를 사용할 때
	while (1) {
		memset(data, 0, sizeof(data));

		//1. 버튼 눌렀을 때 카메라 찍기
		getchar();

		//2. OCR처리하고 큐에 유니코드 저장

		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1107);
		Enqueue_int(&queue_uni, 0x1107);
		Enqueue_int(&queue_uni, 0x1107);
		Enqueue_int(&queue_uni, 0x1107);
		Enqueue_int(&queue_uni, 0x1107);
		Enqueue_int(&queue_uni, 0x1107);
		Enqueue_int(&queue_uni, 0x1107);

		/*3. unicode를 이용하여 모듈을 제어하는 data로 바꾸어 다른 큐에 저장*/
		while (!IsEmpty_int(&queue_uni))
			decoder(&queue_module, Dequeue_int(&queue_uni));

		while (!IsEmpty_char(&queue_module)) { // 한 번 스캔한 모든 문자열을 점자로 표현할 때 까지

			/*4. 7개 씩 모듈 제어*/
			for (module_num = 0;module_num < MODULE_CNT;module_num++) {
				if (IsEmpty_char(&queue_module))
					break;
				else {
					tmp = Dequeue_char(&queue_module);
					data[module_num] = tmp;
					Stack_push(&stack, tmp);
				}
			}
			print_module(data);
			/*5. 다음 버튼을 누를 때 까지 대기*/
			while (1) {
				printf("press 'g' (next) or 'b' (back) !\n");
				char a=getchar();
				if (a == 'g') // 다음 버튼을 눌렀을 때
					break;
				else if (a == 'b') { // 뒤로가기 버튼을 눌렀을 때
					for (int i = 0;i < module_num;i++) {
						tmp = Stack_pop(&stack);
						Enqueue_Front_char(&queue_module, tmp);
					}
					for (int i = 0;i < MODULE_CNT;i++) {
						tmp = Stack_pop(&stack);
						if (tmp == 1) { // 스텍에 데이터가 없을 때
							// 경고음을 넣는거도 좋은 방법
							break;
						}
						Enqueue_Front_char(&queue_module, tmp);
					}
					break;
				}
			}
			getchar(); // 개행을 없애기 위한 코드.

		}
		printf("스캔한 모든 문자 출력 완료. Enter를 누르면 다음 이미지를 스캔.\n");
	}
#endif

#ifdef FOR_MODULE // 라즈베리파이를 이용하여 모듈을 사용할 때
	InitModule();
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


		//2. OCR처리하고 큐에 유니코드 저장

		/*3. unicode를 이용하여 모듈을 제어하는 data로 바꾸어 다른 큐에 저장*/
		while(!IsEmpty_int(&queue_uni))
			Enqueue_char(&queue_module, decoder(Dequeue_int(&queue_uni)));


		while(!IsEmpty(&queue_module)){ // 한 번 스캔한 모든 문자열을 점자로 표현할 때 까지

			/*4. 7개 씩 모듈 제어*/
			for(module_num = 0;module_num < MODULE_CNT;module_num++){
				if(IsEmpty_char(&queue_module))
					break;
				else {
					tmp = Dequeue_char(&queue_module);
					control_module(module_num, tmp);
					Stack_push(&stack, tmp);
				}
			}

			/*5. 다음 버튼을 누를 때 까지 대기*/
			while (1) {
				printf("press 'g' (next) or 'b' (back) !\n");
				char a = getchar();
				if (a == 'g') // 다음 버튼을 눌렀을 때
					break;
				else if (a == 'b') { // 뒤로가기 버튼을 눌렀을 때
					for (int i = 0;i < module_num;i++) {
						tmp = Stack_pop(&stack);
						Enqueue_Front_char(&queue_module, tmp);
					}
					for (int i = 0;i < MODULE_CNT;i++) {
						tmp = Stack_pop(&stack);
						if (tmp == 1) { // 스텍에 데이터가 없을 때
							// 경고음을 넣는거도 좋은 방법
							break;
						}
						Enqueue_Front_char(&queue_module, tmp);
					}
					break;
				}
			}
			getchar(); // 개행을 없애기 위한 코드.

			/*6. 모듈 초기화*/
			clear_all();
		}

	}
#endif

}

#ifdef FOR_MODULE // 라즈베리파이를 이용하여 모듈을 사용할 때
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
#endif
