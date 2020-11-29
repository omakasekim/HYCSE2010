#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 100

struct Stack{
	char *key;
	int top;
	int max_stack_size;
};

struct Stack* init(int len)
{
	struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));

	if(!stack)
		return NULL;

	stack->top = -1;
	stack->max_stack_size = len;
	stack->key = (char*)malloc(len*sizeof(char));
	
	return stack;
}

int isEmpty(struct Stack* s)
{
	return (s->top == -1);
}

int isFull(struct Stack* s)
{
	return (s->top == (s->max_stack_size -1));
}


char peek(struct Stack* s)
{
	return s->key[s->top];
}

char pop(struct Stack* s)
{
	if(isEmpty(s))
	{
		fprintf(stderr, "empty\n");
		exit(1);
	}

	else
		return s->key[(s->top)--];
}

void push(struct Stack* s, char op)
{
	if(isFull(s)){
		fprintf(stderr, "\n");
		return;
	}
	else
		s->key[++(s->top)] = op;
}


int Prec(char ch)
{
	switch(ch)
	{
		case '(':
		case ')':
			return 0;
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
		case '%':
			return 2;
	}
	return -1;
}


int algorithm(char* exp)
{
	int i;

	struct Stack* s = init(strlen(exp));
	if(!s)return -1;

	for(i=0;exp[i];++i)
	{
		if(isdigit(exp[i]))
				push(s,exp[i] - '0');
		else
		{
			int val1 = pop(s);
			int val2 = pop(s);
			switch(exp[i])
			{
			case '+': push(s, val2+val1);break;
			case '-': push(s, val2-val1);break;
			case '*': push(s, val2*val1);break;
			case '/': push(s, val2/val1);break;
			case '%': push(s, val2%val1);break;
			}
		}
	}

	return pop(s);
}

int main()
{
	char delim[] = "#";
	char equation[100];
	char* line;
	FILE *fp = fopen("input.txt", "r");

		fgets(equation,sizeof(equation), fp);
		char* buf = strtok(equation,delim);
		line = malloc(sizeof(char)*strlen(buf));
		strcpy(line, buf);
		buf = strtok(NULL,delim);
		
	printf("coverted postfix form: %s\n", line);
	printf("%d\n",algorithm(line));
	return 0;
}




