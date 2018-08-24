#include "decoder.h"

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

/*queue for module*/
Queue_char queue_module;

/*queue for unicode*/
Queue_int queue_uni;

int main() {

	unsigned char *data = (unsigned char *)malloc(sizeof(unsigned char) * 7);
	int module_num;
	InitQueue_char(&queue_module);
	InitQueue_int(&queue_uni);

/***************************************************************************************/
// Test를 위한 코드 .... 각자 컴퓨터를 사용할 때
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
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		Enqueue_int(&queue_uni, 0x1106);
		
		/*3. unicode를 이용하여 모듈을 제어하는 data로 바꾸어 다른 큐에 저장*/
		while (!IsEmpty_int(&queue_uni))
			decoder(&queue_module, Dequeue_int(&queue_uni));

		while (!IsEmpty_char(&queue_module)) { // 한 번 스캔한 모든 문자열을 점자로 표현할 때 까지

										  /*4. 7개 씩 모듈 제어*/
			for (module_num = 0;module_num < MODULE_CNT;module_num++) {
				if (IsEmpty_char(&queue_module))
					break;
				else
					data[module_num] = Dequeue_char(&queue_module);

			}

			print_module(data);

			/*5. 다음 버튼을 누를 때 까지 대기*/
			printf("press Enter to Next !\n");
			getchar();
		}
		printf("스캔한 모든 문자 출력 완료. Enter를 누르면 다음 이미지를 스캔.\n");
		return(1);
	}
/***************************************************************************************/
	
/***************************************************************************************/
// 솔레노이드를 연결하였을 때
#ifdef FOR_MODULE

	InitModule();
	while(1){
		
		/*
			1. 버튼 눌렀을 때 카메라 찍기

			2. OCR처리하고 큐에 유니코드 저장
		*/

		/*3. unicode를 이용하여 모듈을 제어하는 data로 바꾸어 다른 큐에 저장*/
		while(!IsEmpty_int(&queue_uni))
			Enqueue_char(&queue_module, decoder(Dequeue_int(&queue_uni)));
		
		while(!IsEmpty(&queue_module)){ // 한 번 스캔한 모든 문자열을 점자로 표현할 때 까지
			
			/*4. 7개 씩 모듈 제어*/
			for(module_num = 0;module_num < MODULE_CNT;module_num++){
				if(IsEmpty_char(&queue_module))
					break;
				else					
					control_module(module_num, Dequeue_char(&queue_module));
				
			}

			/*5. 다음 버튼을 누를 때 까지 대기*/
			getchar();

			/*6. 모듈 초기화*/
			clear_all();
		}
		
	}
#endif
/***************************************************************************************/

}

#ifdef FOR_MODULE
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
