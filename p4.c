#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct CircularQueue{
	int *key;
	int front;
	int rear;
	int max_queue_size;
}CircularQueue;

void MakeEmpty(CircularQueue *Q, int max);
int IsEmpty(CircularQueue *Q);
int IsFull(CircularQueue *Q);
void Dequeue(CircularQueue *Q);
void Enqueue(CircularQueue *Q, int X);
void PrintFirst(CircularQueue *Q);
void PrintRear(CircularQueue *Q);

void error(char *message){
	printf("%s", message);
}


void main(){

	FILE *fp = fopen("input.txt", "r");
	char ch, buf;
	char buffer[24];
	int x;

    struct CircularQueue queue;
    struct CircularQueue *pt = &queue;

	while(fscanf(fp, "%c %d",&ch, &x)!=EOF){
		switch(ch){
			case 'n':
				{
					MakeEmpty(&queue, x);
					break;
				}
			case 'e':
				{
					Enqueue(&queue, x);
					break;
				}

			case 'd':
				{
					Dequeue(&queue);
					break;
				}
			case 'f':
				{
					PrintFirst(&queue);
					break;
				}
			case 'r':
				{
					PrintRear(&queue);
					break;
				}
			default:
				break;
			}
	}
	fclose(fp);
}




void MakeEmpty(CircularQueue *Q,int max){
    //Q = malloc(sizeof(struct CircularQueue));
	Q->max_queue_size = max;
	Q->key = malloc(max*sizeof(int));
	Q->front = 0;
	Q->rear = 0;
}

int IsEmpty(CircularQueue *Q){
	return Q->front == Q->rear;
}

int IsFull(CircularQueue *Q){
	return (Q->front != Q->rear && (Q->rear == ((Q->max_queue_size))));
}

void Enqueue(CircularQueue *Q, int X){
    if(!IsFull(Q)&&!IsEmpty(Q)){
	    //Q->key[Q->rear] = X;
	    Q->rear = (Q->rear+1);
	    Q->key[Q->rear] = X;
	}
	else if(!IsFull(Q)&&IsEmpty(Q)){
	    Q->key[Q->rear] = X;
	    Q->rear = (Q->rear+1);
	}
	else
		error("Queue is full.\n");
}

void Dequeue(CircularQueue *Q){
	if(!IsEmpty(Q)){
		Q->front = (Q->front+1);
	}
	else
		error("Queue is Empty.\n");
}

void PrintFirst(CircularQueue *Q){
	if(!IsEmpty(Q)){
		printf("First element is %d.\n",Q->key[Q->front]);
	}
	else
		printf("Queue is empty.\n");
}

void PrintRear(CircularQueue *Q){
	if(!IsEmpty(Q)){
		printf("Last element is %d.\n", Q->key[Q->rear]);
	}
	else
		printf("Queue is empty.\n");
}









