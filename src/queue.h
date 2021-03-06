#include <string.h>

typedef struct Node_char {
	unsigned char data;
	struct Node_char *next;
}Node_char;

typedef struct Queue_char {
	Node_char *front;
	Node_char *rear;
	int count;
}Queue_char;

typedef struct Node_char_arr {
	char data[13];
	struct Node_char_arr *next;
}Node_char_arr;

typedef struct Queue_char_arr {
	Node_char_arr *front;
	Node_char_arr *rear;
	int count;
}Queue_char_arr;

typedef struct Node_int {
	int data;
	struct Node_int *next;
}Node_int;

typedef struct Queue_int {
	Node_int *front;
	Node_int *rear;
	int count;
}Queue_int;

void InitQueue_char(Queue_char *queue);
int IsEmpty_char(Queue_char *queue);
void Enqueue_char(Queue_char *queue, unsigned char data);
void Enqueue_Front_char(Queue_char *queue, unsigned char data);
unsigned char Dequeue_char(Queue_char *queue);
unsigned char Dequeue_Back_char(Queue_char *queue);
Queue_char* queue_copy_char(Queue_char *origin);
void resetQueue_char(Queue_char *queue);

void InitQueue_char_arr(Queue_char_arr *queue);
int IsEmpty_char_arr(Queue_char_arr *queue);
void Enqueue_char_arr(Queue_char_arr *queue, char* data);
void Enqueue_Front_char_arr(Queue_char_arr *queue, char* data);
char* Dequeue_char_arr(Queue_char_arr *queue);
char* Dequeue_Back_char_arr(Queue_char_arr *queue);
Queue_char_arr* queue_copy_char_arr(Queue_char_arr *origin);

void InitQueue_int(Queue_int *queue);
int IsEmpty_int(Queue_int *queue);
void Enqueue_int(Queue_int *queue, int data);
int Dequeue_int(Queue_int *queue);
int Dequeue_Back_int(Queue_int *queue);
Queue_int* queue_copy_int(Queue_int *origin);
void resetQueue_int(Queue_int *queue);

void InitQueue_char(Queue_char *queue)
{
	queue->front = queue->rear = NULL;
	queue->count = 0;
}

int IsEmpty_char(Queue_char *queue)
{
	return queue->count == 0;
}

void Enqueue_char(Queue_char *queue, unsigned char data)
{
	Node_char *now = (Node_char *)malloc(sizeof(Node_char));
	now->data = data;
	now->next = NULL;
	if (IsEmpty_char(queue))
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

void Enqueue_Front_char(Queue_char *queue, unsigned char data)
{
	Node_char *now = (Node_char *)malloc(sizeof(Node_char));
	now->data = data;
	if (IsEmpty_char(queue))
	{
		now->next = NULL;
		queue->rear = now;
	}
	else
	{
		now->next = queue->front;
	}
	queue->front = now;
	queue->count++;
}

unsigned char Dequeue_char(Queue_char *queue)
{
	unsigned char re = 0;
	Node_char *now;
	if (IsEmpty_char(queue))
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

unsigned char Dequeue_Back_char(Queue_char *queue)
{
	unsigned char re = 0;
	Node_char *now;
	Node_char *tmp = queue->front;
	if (IsEmpty_char(queue))
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

Queue_char* queue_copy_char(Queue_char *origin) {
	Queue_char* copy = (Queue_char *)malloc(sizeof(Queue_char));
	Node_char* tmp = origin->front;
	int queue_size = origin->count;
	InitQueue_char(copy);
	for (int i = 0;i < queue_size;i++) {
		Enqueue_char(copy, tmp->data);
		tmp = tmp->next;
	}
	return copy;
}

void InitQueue_char_arr(Queue_char_arr *queue)
{
	queue->front = queue->rear = NULL;
	queue->count = 0;
}

int IsEmpty_char_arr(Queue_char_arr *queue)
{
	return queue->count == 0;
}

void Enqueue_char_arr(Queue_char_arr *queue, char* data)
{
	Node_char_arr *now = (Node_char_arr *)malloc(sizeof(Node_char_arr));
	strcpy(now->data, data);
	now->next = NULL;
	if (IsEmpty_char_arr(queue))
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

void Enqueue_Front_char_arr(Queue_char_arr *queue, char* data)
{
	Node_char_arr *now = (Node_char_arr *)malloc(sizeof(Node_char_arr));
	strcpy(now->data, data);
	if (IsEmpty_char_arr(queue))
	{
		now->next = NULL;
		queue->rear = now;
	}
	else
	{
		now->next = queue->front;
	}
	queue->front = now;
	queue->count++;
}

char* Dequeue_char_arr(Queue_char_arr *queue)
{
	char* re = (char *)malloc(sizeof(char)*13);
	memset(re, '\0', sizeof(re));
	Node_char_arr *now;
	if (IsEmpty_char_arr(queue))
	{
		return re;
	}
	now = queue->front;
	strcpy(re, now->data);
	queue->front = now->next;
	free(now);
	queue->count--;
	return re;
}

char* Dequeue_Back_char_arr(Queue_char_arr *queue)
{
	char* re = (char *)malloc(sizeof(char)*13);
	memset(re, '\0', sizeof(re));
	Node_char_arr *now;
	Node_char_arr *tmp = queue->front;
	if (IsEmpty_char_arr(queue))
	{
		return re;
	}
	now = queue->rear;
	strcpy(re, now->data);
	for (int i = 0;i < queue->count - 2;i++)
		tmp = tmp->next;
	queue->rear = tmp;
	free(now);
	queue->count--;
	return re;
}

Queue_char_arr* queue_copy_char_arr(Queue_char_arr *origin) {
	Queue_char_arr* copy = (Queue_char_arr *)malloc(sizeof(Queue_char_arr));
	Node_char_arr* tmp = origin->front;
	int queue_size = origin->count;
	InitQueue_char_arr(copy);
	for (int i = 0;i < queue_size;i++) {
		Enqueue_char_arr(copy, tmp->data);
		tmp = tmp->next;
	}
	return copy;
}

void InitQueue_int(Queue_int *queue)
{
	queue->front = queue->rear = NULL;
	queue->count = 0;
}

int IsEmpty_int(Queue_int *queue)
{
	return queue->count == 0;
}

void Enqueue_int(Queue_int *queue, int data)
{
	Node_int *now = (Node_int *)malloc(sizeof(Node_int));
	now->data = data;
	now->next = NULL;
	if (IsEmpty_int(queue))
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

int Dequeue_int(Queue_int *queue)
{
	int re = 0;
	Node_int *now;
	if (IsEmpty_int(queue))
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

int Dequeue_Back_int(Queue_int *queue)
{
	int re = 0;
	Node_int *now;
	Node_int *tmp = queue->front;
	if (IsEmpty_int(queue))
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

Queue_int* queue_copy_int(Queue_int *origin) {
	Queue_int* copy = (Queue_int *)malloc(sizeof(Queue_int));
	Node_int* tmp = origin->front;
	int queue_size = origin->count;
	InitQueue_int(copy);
	for (int i = 0;i < queue_size;i++) {
		Enqueue_int(copy, tmp->data);
		tmp = tmp->next;
	}
	return copy;
}
