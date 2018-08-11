#include "header.h"

Queue queue; // QUEUE

int main(){

	InitQueue(&queue);
	
	if(wiringPiSetup() == -1)
		return 1;
	
	for(int i=0;i<MODULE_CNT;i++){
		pinMode(latch_pin[i], OUTPUT);
		pinMode(clock_pin[i], OUTPUT);
		pinMode(data_pin[i], OUTPUT);
	}

}

void decoder(int unicode){
	unsigned char data;
	switch (unicode) {
		case 0x1100: // ㄱ
			data = SOL_NUM[1];
			Enqueue(&queue, data);
			break;
		case 0x1102: // ㄴ
			data = SOL_NUM[0]+SOL_NUM[1];
			Enqueue(&queue, data);
			break;
		case 0x1103: // ㄷ
			data = SOL_NUM[1]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x1105: //ㄹ
			data = SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1106: //ㅁ
			data = SOL_NUM[0]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1107: // ㅂ
			data = SOL_NUM[1]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1109: //ㅅ
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x110B: // ㅇ
			//data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3];
			//Enqueue(&queue, data);
			break;
		case 0x110C: // ㅈ
			data = SOL_NUM[1]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x110E: // ㅊ
			data = SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x110F: // ㅋ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x1110: // ㅌ
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1111: // ㅍ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1112: // ㅎ
			data = SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1101: // ㄲ
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			data = SOL_NUM[1];
			Enqueue(&queue, data);
			break;
		case 0x1104: // ㄸ
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			data = SOL_NUM[1]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x1108: // ㅃ
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			data = SOL_NUM[1]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x110A: // ㅆ
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x110D: // ㅉ
			data = SOL_NUM[5];
			Enqueue(&queue, data);
			data = SOL_NUM[1]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		/******************************************/
		case 0x11A8: // ㄱ
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			break;
		case 0x11AB: // ㄴ
			data = SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x11AE: // ㄷ
			data = SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11AF: //ㄹ
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x11B7: //ㅁ
			data = SOL_NUM[2]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11B8: // ㅂ
			data = SOL_NUM[0]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x11BA: //ㅅ
			data = SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11BC: // ㅇ
			data = SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11BD: // ㅈ
			data = SOL_NUM[0]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11BE: // ㅊ
			data = SOL_NUM[2]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11BF: // ㅋ
			data = SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11C0: // ㅌ
			data = SOL_NUM[2]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11C1: // ㅍ
			data = SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11C2: // ㅎ
			data = SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11A9: // ㄲ
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			break;
		case 0x11BB: // ㅆ
			data = SOL_NUM[1]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
	}
}

void clear(int module_num){
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, 0x00);
	digitalWrite(latch_pin[module_num], HIGH);
	delay(1);
}

void clear_all(){
	for(int i=0;i<MODULE_CNT;i++)
		clear(i);
}

void control_module(int module_num, unsigned char data){
	digitalWrite(latch_pin[module_num], LOW);
	shiftOut(data_pin[module_num], clock_pin[module_num], MSBFIRST, data);
	digitalWrite(latch_pin[module_num], HIGH);
	delay(1);
}

/**********************QUEUE**************************/
void InitQueue(Queue *queue)
{
	queue->front = queue->rear = NULL; 
	queue->count = 0;
}

int IsEmpty(Queue *queue)
{
	return queue->count == 0;    
}

void Enqueue(Queue *queue, unsigned char data)
{
	Node *now = (Node *)malloc(sizeof(Node)); 
	now->data = data;
	now->next = NULL;

	if (IsEmpty(queue))
	{
		queue->front = now;      
	}
	else
	{
		queue->rear->next = now;
	}
	queue->rear = now;  
	queue->count++;
}

unsigned char Dequeue(Queue *queue)
{
	unsigned char re = 0;
	Node *now;
	if (IsEmpty(queue))
	{
		return re;
	}
	now = queue->front;
	re = now->data;
	queue->front = now->next;
	free(now);
	queue->count--;
	return re;
}
/*********************************************************/
