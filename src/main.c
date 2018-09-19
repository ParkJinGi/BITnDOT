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

/*check all module*/
void check_module();

#endif
/**********************************************************/

/*queue for module*/
Queue_char queue_module;

/*queue for unicode*/
Queue_int queue_uni;

/*queue for char*/
Queue_char_arr queue_arr;

/*Stack for Go back*/
Stack stack;
Stack_arr stack_arr;

int main() {

	unsigned char data[7];
	unsigned char tmp;
	char data_char[7][13];
	char tmp_char[13];
	clock_t tm_start;
	int reset;
	int module_num;

	//유우빈 사용 변수들...
	char uniArr[6]={};
	int uniNum = 0;

#ifdef FOR_MODULE // 라즈베리파이를 이용하여 모듈을 사용할 때
	FILE *fp;
	InitModule();
	clear_all();

#ifdef CHECK	
	check_module();
#endif

	while(1){
		InitQueue_char(&queue_module);
		InitQueue_int(&queue_uni);
		InitQueue_char_arr(&queue_arr);
		InitStack(&stack);
		InitStack_arr(&stack_arr);

		system("clear");
		if(reset){
			printf("STATUS : Restart system.\n");
			reset = 0;
		}
		printf("STATUS : Press Button to take a picture.\n");
		//1. 버튼 눌렀을 때 카메라 찍기
		delay(1000);
		while(1){
			if (digitalRead(foward_button) == 0) {
				tm_start = clock();
				while (1) {
					if(clock() < tm_start + 300000)
						continue;
					else if (digitalRead(foward_button) == 1)
						break;
				}
				break;
			}
		}

		printf("STATUS : Capture Start.\n");
		if(fork() == 0)
			execl("/usr/bin/raspistill", "raspistill","--quality","100", "-t","3","--rotation", "180", "-o", "image.jpg", "-co", "100", "-sh", "100", NULL);
		else
			wait((int *)0);
		printf("STATUS : Capture complete.\n");
		//1-2. 카메라로 찍은 이미지를 한 장의 이미지로 변환
		printf("STATUS : Crop picture.\n");
		system("./crop image.jpg"); 
		printf("STATUS : OCR Processing. Please wait....\n");
		//system("python ocr.py");
		delay(3000);

		//2. OCR처리하고 큐에 유니코드 저장
		system("java toUni TEXT.txt");
		fp = fopen("./Unicode.txt", "r");
		while(1){
			memset(uniArr, '\0', sizeof(uniArr));
			uniArr[0]='0';
			uniArr[1]='x';
			for(int i=2; i<6; i++)	
				uniArr[i]=getc(fp);

			if((uniArr[2]=='.')){
				break;
			}else{
				uniNum = strtoul(uniArr, NULL, 16);
				Enqueue_int(&queue_uni, uniNum);
			}
		}
		
		system("clear");

		/*3. unicode를 이용하여 모듈을 제어하는 data로 바꾸어 다른 큐에 저장*/
		while (!IsEmpty_int(&queue_uni))
			decoder(&queue_module, &queue_arr, Dequeue_int(&queue_uni));


		while(!IsEmpty_char(&queue_module)){ // 한 번 스캔한 모든 문자열을 점자로 표현할 때 까지
			memset(data, '\0', sizeof(data));
			memset(data_char, '\0', sizeof(data_char));

			/*4. 7개 씩 모듈 제어*/
			for (module_num = 0;module_num < MODULE_CNT;module_num++) {
				if (IsEmpty_char(&queue_module))
					break;
				else {
					tmp = Dequeue_char(&queue_module);
					strcpy(tmp_char, Dequeue_char_arr(&queue_arr));
					data[module_num] = tmp;
					strcpy(data_char[module_num], tmp_char);
					Stack_push(&stack, tmp);
					Stack_push_arr(&stack_arr, tmp_char);
					control_module(module_num, tmp);
				}
			}
			print_module(data, data_char);
			delay(2000);
			/*5. 다음 버튼을 누를 때 까지 대기*/
			while (1) {
				if (digitalRead(foward_button) == 0) {
					printf("STATUS : Move to Next String.\n");
					tm_start = clock();
					while (1) {
						if(clock() < tm_start + 300000)
							continue;
						else if (digitalRead(foward_button) == 1)
							break;
					}
					break;
				}
				else if (digitalRead(back_button) == 0) { // 뒤로가기 버튼을 눌렀을 때
					tm_start = clock();
					while (1) {
						if(clock() < tm_start + 300000)
							continue;
						else if(clock() > tm_start + 2000000){
							printf("STATUS : Reset Program.\n");
							tm_start = clock();
							reset=1;
							while(1){
								if(clock() < tm_start + 300000)
									continue;
								else if(digitalRead(back_button) == 1)
									break;
							}
							break;
						}
						else if(digitalRead(back_button) == 1){
							printf("STATUS : Move to Previos String.\n");
							break;
						}
					}
					if(reset)
						break;
					for (int i = 0;i < module_num;i++) {
						tmp = Stack_pop(&stack);
						strcpy(tmp_char, Stack_pop_arr(&stack_arr));
						Enqueue_Front_char(&queue_module, tmp);
						Enqueue_Front_char_arr(&queue_arr, tmp_char); 
					}
					for (int i = 0;i < MODULE_CNT;i++) {
						tmp = Stack_pop(&stack);
						strcpy(tmp_char, Stack_pop_arr(&stack_arr));
						if (tmp == 1)
							break;
						Enqueue_Front_char(&queue_module, tmp);
						Enqueue_Front_char_arr(&queue_arr, tmp_char); 
					}
					break;
				}
			}
			if(reset){
				clear_all();
				break;
			}
			/*6. 모듈 초기화*/
			clear_all();
		}
		fclose(fp);
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
	pinMode(back_button, INPUT);
	pinMode(foward_button, INPUT);
}

void check_module(){
	printf("Press enter to start !\n");
	getchar();
			
	for (int i=6;i<MODULE_CNT;i++){
		for(int j=0;j<6;j++){
			printf("[MODULE : %d, SOL : %d]\n", i, j+1);
			control_module(i, SOL_NUM[j]);
			getchar();
		}
		clear_all();
	}
	/*		
	int tmp=0;
	for (int i=0;i<MODULE_CNT;i++){
		for(int j=0;j<6;j++){
			tmp += SOL_NUM[j];
			printf("%d 개",(i*6)+j+1);
			control_module(i, tmp);
			getchar();
		}
		tmp = 0;
	}*/
	exit(0);
}

#endif

