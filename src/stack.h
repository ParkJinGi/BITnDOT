#define STACKSIZE 100

typedef struct {
	int size;
	unsigned char data[STACKSIZE];
} Stack;

void InitStack(Stack *stack);
void Stack_push(Stack *stack, unsigned char data);
unsigned char Stack_pop(Stack *stack);

void InitStack(Stack *stack) {
	stack->size = 0;
}

void Stack_push(Stack *stack, unsigned char data){
	if (stack->size == STACKSIZE) {
		for (int j = 1;j <= STACKSIZE;j++)
			stack->data[j - 1] = stack->data[j];
		stack->size--;
	}
	stack->data[stack->size++] = data;
}

unsigned char Stack_pop(Stack *stack){
	if (stack->size == 0) 
		return 0;
	else
		return stack->data[--stack->size];
}
