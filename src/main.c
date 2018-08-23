#include "decoder.h"

#ifndef FOR_TEST
#include "control_module.h"
#endif

Queue queue;

void a(){
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
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
	
	Enqueue(&queue, SSOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5]);
	/***************  Module test Code  *********************/
	while(1){
		a();
		printf("1번 솔레노이드 작동 ! \n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("2번 솔레노이드 작동 ! \n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("3번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("4번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("5번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("6번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("1번 2번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("3번 4번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("5번 6번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("1번 2번 3번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("4번 5번 6번 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
		printf("모든 솔레노이드 작동 !\n");
		control_module(0, Dequeue(&queue));
		sleep(5000);
		a();
	}
}
