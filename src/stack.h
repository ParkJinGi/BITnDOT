#include <string.h>
#define STACKSIZE 100

typedef struct {
	int size;
	unsigned char data[STACKSIZE];
} Stack;

typedef struct {
	int size;
	char data[STACKSIZE][13];
} Stack_arr;

void InitStack(Stack *stack);
void Stack_push(Stack *stack, unsigned char data);
unsigned char Stack_pop(Stack *stack);

void InitStack_arr(Stack_arr *stack);
void Stack_push_arr(Stack_arr *stack, char* data);
char* Stack_pop_arr(Stack_arr *stack);

void InitStack(Stack *stack) {
	stack->size = 0;
	for(int i=0;i<7;i++)
		Stack_push(stack, 0x00);
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
		return 1;
	else
		return stack->data[--stack->size];
}

void InitStack_arr(Stack_arr *stack) {
	stack->size = 0;
	for(int i=0;i<7;i++)
		Stack_push_arr(stack, "");
}

void Stack_push_arr(Stack_arr *stack, char* data){
	if (stack->size == STACKSIZE) {
		for (int j = 1;j <= STACKSIZE;j++)
			strcpy(stack->data[j - 1],stack->data[j]);
		stack->size--;
	}
	strcpy(stack->data[stack->size++], data);
}

char* Stack_pop_arr(Stack_arr *stack){
	if (stack->size == 0) 
		return "";
	else
		return stack->data[--stack->size];
}
