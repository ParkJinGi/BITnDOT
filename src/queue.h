typedef struct Node {
	unsigned char data;
	struct Node *next;
}Node;

typedef struct Queue {
	Node *front; 	
	Node *rear; 
	int count;
}Queue;

void InitQueue(Queue *queue);
int IsEmpty(Queue *queue); 
void Enqueue(Queue *queue, unsigned char data); 
unsigned char Dequeue(Queue *queue); 
unsigned char Dequeue_Back(Queue *queue);

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
