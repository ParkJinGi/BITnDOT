#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
//#include <wiringPi.h>
//#include <wiringShift.h>

#define MODULE_CNT 7

typedef struct Node {
	unsigned char data;
	struct Node *next;
}Node;


typedef struct Queue {
	Node *front; 	
	Node *rear; 
	int count;
}Queue;

int clock_pin[MODULE_CNT] = {29,};
int latch_pin[MODULE_CNT] = {28,};
int data_pin[MODULE_CNT] = {27,};

unsigned char SOL_NUM[6] = {
	0b00000010, 0b00000100, 0b00001000,
	0b00010000, 0b00100000, 0b01000000
};

/*print to console*/
void print_queue();

/*shut down specific module*/
void clear(int module_num);

/*shut down every module*/
void clear_all();

/*control specific module*/
void control_module(int module_num, unsigned char data);

/*make date using unicode and fill the queue*/
void decoder(int unicode);

/*check prev unicode is figure*/
int prev_is_figure();

/***********QUEUE LIBRARY**************/
void InitQueue(Queue *queue);
int IsEmpty(Queue *queue); 
void Enqueue(Queue *queue, unsigned char data); 
unsigned char Dequeue(Queue *queue); 
unsigned char Dequeue_Back(Queue *queue);
/**************************************/
