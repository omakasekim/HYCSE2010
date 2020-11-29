#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
	int data;
	struct Node *next;
}Node;

typedef struct top {
	Node *top;
}Stack;

void push(Stack *stack, int data){

	Node *node = (Node*)malloc(sizeof(Node));
	node->data = data;
	node->next = stack->top;
	stack->top = node;
}

int pop(Stack *stack){

	if(stack->top == NULL){
		printf("Stack Underflow");
		return -1;
	}
	Node *node = stack->top;
	int data = node->data;
	stack->top = node->next;
	free(node);
	return data;
}

void display(Stack *stack){
	Node *cur = stack->top;
	while(cur != NULL){
		printf("%d\n",cur->data);
		cur = cur->next;
	}
}
/* array form

void init(StackType *s)
{
	s->top = -1;
}

#define MAX_STACK_SIZE 100

typedef int element;
typedef struct{
element stack[MAX_STACK_SIZE];
int top;
}StackType;




