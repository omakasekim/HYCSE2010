#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int queue[10];
	int front, rear;
}Queue;

void init(Queue *q)
{
	q->front = q->rear = 0;
}

int is_empty(Queue *q)
{
	return q->front == q->rear;
}

int is_full(Queue *q)
{
	return ((q-> rear + 1) % 10 == q->front);
}

void enqueue(Queue *q, int item)
{
	if(is_full(q)){
		printf("Queue is empty\n");
		return;
	}
	q->rear = (q->rear + 1) % 10;
	q->queue[q->rear] = item;

}
int dequeue(Queue *q)
{
	if(is_empty(q)){
		printf("Queue is empty\n");
		return;
	}
	q->front = (q->front + 1) % 10;
	return q->queue[q->front];
}

void main()
{
	FILE *fp = fopen("input.txt","r");


	char delim[] = " ";
	char line[100];
	int buffer[24];
	int nodecount = 0;

	fgets(line, sizeof(line), fp);
	char *buf = strtok(line, delim);
	while(buf != NULL){
		nodecount++;
		buf= strtok(NULL, delim);
	}


	int adj_mat[nodecount][nodecount];
	int indeg[nodecount];
	int flag[nodecount];

	for(int i =0; i<nodecount;i++)
	{
		indeg[i] = 0;
		flag[i] = 0;
		for(int j=0; j<nodecount; j++)
			adj_mat[i][j] = 0;
	}


	int vertices = 0;
	int idx = 0;
	fgets(line, sizeof(line), fp);
	buf = strtok(line, delim);
	char* temparr[nodecount*nodecount];
	while(buf != NULL){
		temparr[idx++] = buf;
		vertices++;
		buf = strtok(NULL, delim);
	}

	idx = 0;
	int u[vertices];
	int v[vertices];

	for(int i=0; i<vertices; i++){
		sscanf(temparr[idx++], "%d-%d", &u[i], &v[i]);
		adj_mat[u[i]-1][v[i]-1] = 1;
	}




	for(int i=0;i<nodecount;i++){
		for(int j=0;j<nodecount;j++){
			if(adj_mat[j][i] == 1)
				indeg[i]++;
		}
	}

	for(int i =0; i<nodecount; i++){
		for(int j=0; j<nodecount; j++){
			printf("%d ", adj_mat[i][j]);
		}
		printf("\n");
	}
	for(int i=0;i<nodecount;i++)
		printf("indeg: %d  ", indeg[i]);

	int count =0;
	
	printf(" Topological sort : ");

	//DFS(1);	
	int result[nodecount];
	int index = 0;


	int y[10],z[10];
	int c = 0;
	int n = 4;
/*
	for(int i = 0; i < nodecount; i++)
	{
		for(int j = 0; j < nodecount; j++)
		{
			am[j][i] = adj_mat[i][j];
		}
	}
*/
	
	int q = 0;
	while(q<vertices){

		for(int i = 0; i < nodecount;i++)
		{
			if(indeg[i]==0 && flag[i]==0){
				flag[i] = 1;
				printf("%d->",(1+i));
		}	

	}
		q++;
	}

	int am[4][4];
	int zz[4][4] = {
		{0,1,1,1},
		{0,0,1,0},
		{0,0,0,0},
		{0,1,0,0}
	};

	for(int i=0;i<4;i++)
	{
		for(int j=0;j<n;j++)
		{
			am[j][i] = zz[i][j];
		}
	}



	for(int i = 0; i < n; i++)
	{
		y[i] = 0;
		z[i] = 0;
	}

	for(int i = 0; i < n; i++)
	{
		for(int j = 0; j < n; j++)
		{
			y[i] = y[i]+am[i][j];
		}
	//	printf("%",y[i]);
	}
	printf("\n");

	while(c<=n)
	{
		for(int k = 0; k < n; k++)
		{
			if((y[k]==0)&&(z[k]==0))
			{
				printf("%d-> ", (k+2));
				z[k] = 1;
				for(int i = 0; i<n;i++)
				{
					if(am[i][k] == 1)
						am[i][k] = am[i][k]-1;
				}
				for(int i = 0;i < n; i++)
				{
					y[i] = 0;
				}

				for(int m = 0; m<n; m++)
				{
					for(int j = 0; j < n;j++)
					{
						y[m]=y[m]+am[m][j];
					}
				}
			}
		}
		c++;
	}



	/*while(count<vertices){

		for(int k=0;k<nodecount;k++){

			for(int i =0; i<nodecount; i++)
			{
				if((indeg[i]==0 && flag[i]== 0)){
					flag[i] = 1;
					result[index] = (i+1);
					printf("%d ",result[count]);
					index++;
					//printf("%d ",(i+1));
				}
			}
			for(int i = 0; i<nodecount; i++){
				if(adj_mat[result[index-1i]-1][i] == 1)
					indeg[i]--;
			}
			}
	count++;
	}*/	
		fclose(fp);

}


