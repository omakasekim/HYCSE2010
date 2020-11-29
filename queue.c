#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_QUEUE_SIZE 5

typedef int element;
typedef struct{
	element queue[MAX_QUEUE_SIZE];
	int front, rear;
}QueueType;

void init(QueueType *q){
	q->front = q->rear = 0;
}

void error(char *message)
{
	printf("%s\n",message);
	return;
}

int is_empty(QueueType *q){
	return q->front == q->rear;
}

int is_full(QueueType *q){
	return q->front == (q->rear +1)%MAX_QUEUE_SIZE;
}

void enqueue(QueueType *q, element item)
{
	if(is_full(q))
		error("Queue Overflow\n");
	q->rear = (q->rear +1) % MAX_QUEUE_SIZE;
	q->queue[q->rear] = item;

}

element dequeue(QueueType *q)
{
	if(is_empty(q))
		error("Queue Underflow\n");
	q->front = (q->front + 1) % MAX_QUEUE_SIZE;
	return q->queue[q->front];
}

element peek(QueueType *q)
{
	return q->queue[q->front + 1];
}

void main()
{
	QueueType q;
	init(&q);
	printf("front = %d, rear = %d\n", q.front, q.rear);
	enqueue(&q, 1);
	enqueue(&q, 2);
	enqueue(&q, 3);
	printf("dequeue() = %d\n",dequeue(&q));
	printf("dequeue() = %d\n",dequeue(&q));
	printf("dequeue() = %d\n",dequeue(&q));
	printf("front = %d, rear = %d\n", q.front, q.rear);
}


