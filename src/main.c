#include "header.h"

Queue queue; // QUEUE
int prev = -1;
int prevv = -1;

int main(){

	InitQueue(&queue);
/*	
	if(wiringPiSetup() == -1)
		return 1;
	
	for(int i=0;i<MODULE_CNT;i++){
		pinMode(latch_pin[i], OUTPUT);
		pinMode(clock_pin[i], OUTPUT);
		pinMode(data_pin[i], OUTPUT);
	}
*/
	int t[7]={0x110C,0x1161,0x110C,0x1161,0x1175,0x1103,0x1161};
	for(int i=0;i<4;i++)
		decoder(t[i]);
	print_queue();
}

void decoder(int unicode){
	unsigned char data;
	switch (unicode) {
		/**********************초성************************/
		case 0x1100: // ㄱ
			data = SOL_NUM[1];
			Enqueue(&queue, data);
			break;
		case 0x1102: // ㄴ
			if(prev_is_figure())
				Enqueue(&queue, 0);
			data = SOL_NUM[0]+SOL_NUM[1];
			Enqueue(&queue, data);
			break;
		case 0x1103: // ㄷ	
			if(prev_is_figure())
				Enqueue(&queue, 0);
			data = SOL_NUM[1]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x1105: //ㄹ
			data = SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1106: //ㅁ
			if(prev_is_figure())
				Enqueue(&queue, 0);
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
			if ((prev == 0x1161) && (prevv == 0x1102 || prevv == 0x1103 || prevv == 0x1106 || prevv == 0x1107 || prevv == 0x110C || prevv == 0x110F || prevv == 0x1110 || prevv == 0x1111 || prevv == 0x1112)) {
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[5];
				Enqueue(&queue, data);
			}
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
			if(prev_is_figure())
				Enqueue(&queue, 0);
			Enqueue(&queue, data);
			break;
		case 0x1110: // ㅌ
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1111: // ㅍ
			if(prev_is_figure())
				Enqueue(&queue, 0);
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x1112: // ㅎ
			if(prev_is_figure())
				Enqueue(&queue, 0);
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
		/***************종성*******************/
		case 0x11A8: // ㄱ
			if (prev == 0x1165) { // 억
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x1169) { // 옥
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[4] + SOL_NUM[5];
			}else
				data = SOL_NUM[0];
			Enqueue(&queue, data);
			break;
		case 0x11AB: // ㄴ
			if (prev == 0x1165) { // 언
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1167) { // 연
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[5];
			}
			else if (prev == 0x116E) { // 운
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3];
			}
			else if (prev == 0x1169) { // 온
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1173) { // 은
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1175) { // 인
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			}
			else
				data = SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x11AE: // ㄷ
			data = SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11AF: //ㄹ
			if (prev == 0x1165) { // 얼
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4];
			}
			else if (prev == 0x1167) { // 열
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x116E) { // 울
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			}
			else if (prev == 0x1173) { // 을
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4] + SOL_NUM[5];
			}
			else
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
			if (prev == 0x1165) { // 엇
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[3] + SOL_NUM[5];
				Enqueue(&queue, data);
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[4];
			}
			else
				data = SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11BC: // ㅇ
			if (prev == 0x1167) { // 영
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[5];
			}
			else if (prev == 0x1169) { // 옹
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3] + SOL_NUM[4] + SOL_NUM[5];
			}
			else
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
		/***************쌍받침*********************/	
		case 0x11A9: // ㄲ
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			break;
		case 0x11BB: // ㅆ
			if (prev == 0x1161 && prevv == 0x1111) {
				data = data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[1]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		/****************겹받침*******************/
		case 0x11AA: // 윿
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			data = SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11AC: // 읁
			data = SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			data = SOL_NUM[0]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x11AD: // 읂
			data = SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			data = SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11B1: // 읆
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[2]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11B0: // 읅
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			break;
		case 0x11B2: // 읇
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[0]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x11B3: // 읈
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x11B4: // 읉
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[2]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11B5: // 읊
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11B6: // 읋
			data = SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x11B9: // 읎
			data = SOL_NUM[0]+SOL_NUM[2];
			Enqueue(&queue, data);
			data = SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		/*********************모음********************/
		case 0x1161: // ㅏ
			if (prev == 0x1100) { // 가
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[5];
			}
			if (prev == 0x1101) { // 까
				Dequeue_Back(&queue);
				Dequeue_Back(&queue);
				data = SOL_NUM[5];
				Enqueue(&queue, data);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[5];
			}
			else if (prev == 0x1102) { // 나
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1];
			}
			else if (prev == 0x1103) { // 다
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[2];
			}
			else if (prev == 0x1106) { // 마
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[3];
			}
			else if (prev == 0x1107) { // 바
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[3];
			}
			else if (prev == 0x1109) { // 사
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1];
			}
			if (prev == 0x110A) { // 싸
				Dequeue_Back(&queue);
				Dequeue_Back(&queue);
				data = SOL_NUM[5];
				Enqueue(&queue, data);
				data = SOL_NUM[0] + SOL_NUM[1];
			}
			else if (prev == 0x110C) { // 자
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[5];
			}
			else if (prev == 0x110F) { // 카
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[2];
			}
			else if (prev == 0x1110) { // 타
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[2] + SOL_NUM[3];
			}
			else if (prev == 0x1111) { // 파
				Dequeue_Back(&queue);
				data = SOL_NUM[0] + SOL_NUM[1] + SOL_NUM[3];
			}
			else if (prev == 0x1112) { // 하
				Dequeue_Back(&queue);
				data = SOL_NUM[1] + SOL_NUM[2] + SOL_NUM[3];
			}
			else
				data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x1163: // ㅑ
			data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1165: // ㅓ
			data = SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1167: // ㅕ
			data = SOL_NUM[0]+SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x1169: // ㅗ
			data = SOL_NUM[0]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x116D: // ㅛ
			data = SOL_NUM[1]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x116E: // ㅜ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1172: // ㅠ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x1173: // ㅡ
			data = SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x1175: // ㅣ
			data = SOL_NUM[0]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1162: // ㅐ
			if ((prev == 0x110B) && (prevv == 0x1163 || prevv == 0x116E || prevv == 0x116A || prevv == 0x116F) ) {
				data = SOL_NUM[4] + SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1164: // ㅒ
			data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1166: // ㅔ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1168: // ㅖ
			if (!(prevv >= 0x11A8 && prevv <= 0x11C2) && prev == 0x110B) {
				data = SOL_NUM[4] + SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[1]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x116A: // ㅘ
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x116B: // ㅙ
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x116C: // ㅚ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		case 0x116F: // ㅝ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1170: // ㅞ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[4];
			Enqueue(&queue, data);
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1171: // ㅟ
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[4];
			Enqueue(&queue, data);
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[4];
			Enqueue(&queue, data);
			break;
		case 0x1174: // ㅢ
			data = SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3]+SOL_NUM[5];
			Enqueue(&queue, data);
			break;
		/**********************figure**************************/
		case 0x0030: // 0
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x0031: // 1
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0];
			Enqueue(&queue, data);
			break;
		case 0x0032: // 2
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x0033: // 3
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[1];
			Enqueue(&queue, data);
			break;
		case 0x0034: // 4
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x0035: // 5	
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x0036: // 6	
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;
		case 0x0037: // 7
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[1]+SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x0038: // 8	
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[0]+SOL_NUM[2]+SOL_NUM[3];
			Enqueue(&queue, data);
			break;
		case 0x0039: // 9
			if(!prev_is_figure()){
				data = SOL_NUM[1]+SOL_NUM[3]+SOL_NUM[4]+SOL_NUM[5];
				Enqueue(&queue, data);
			}
			data = SOL_NUM[1]+SOL_NUM[2];
			Enqueue(&queue, data);
			break;

	}
	prevv = prev;
	prev = unicode;
}

int prev_is_figure(){
	if(prev >= 0x0030 && prev <= 0x0039)
		return 1;
	else
		return 0;
}
/*
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
*/
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

unsigned char Dequeue_Back(Queue *queue)
{
	unsigned char re = 0;
	Node *now;
	Node *tmp = queue->front;
	if (IsEmpty(queue))
	{
		return re;
	}
	now = queue->rear;
	re = now->data;
	for (int i = 0;i < queue->count - 2;i++)
		tmp = tmp->next;
	queue->rear = tmp;
	free(now);
	queue->count--;
	return re;
}
/*********************************************************/

void print_queue() {
	unsigned char data[MODULE_CNT];
	int bit = 2;
	while (!IsEmpty(&queue)) {
		memset(data, 0xFF, sizeof(unsigned char) * MODULE_CNT);
		for (int i = 0;i<MODULE_CNT;i++) {
			if (IsEmpty(&queue))
				break;
			data[i] = Dequeue(&queue);
		}

		for (int i = 0;i<3;i++) {
			for (int j = 0;j<MODULE_CNT;j++) {
				for (int k = 0;k<2;k++) {
					if (data[j] & (bit << ((i * 2) + k)))
						printf("● ");
					else
						printf("○ ");
				}
				printf("  ");
			}
			printf("\n");
		}
		printf("\n\n");

	}
}
