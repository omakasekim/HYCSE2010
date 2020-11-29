#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ENROLLED 2

typedef struct studentT{
	char *name;
	int literature;
	int math;
	int science;
}studentT;

typedef struct courseT{
	studentT students[MAX_ENROLLED];
	int numEnrolled;
}courseT;

int main(void)
{
	FILE *fp = fopen("input.txt", "r");

	char* strdelim = "--";

	char *title1;
	char *title2;

	char buffer[24];
	char delim[] = " ";

	int strcnt = 0;
	int idx = 0;
	int i,j;

	struct studentT* st1;
	struct studentT* st2;

	char *array[4];
	char *buf;
	char line[24];

	fgets(buffer, sizeof(buffer),fp);
	title1 = malloc(sizeof(char)*strlen(buffer));
	strcpy(title1,buffer);
	fscanf(fp, "%d", &i);

	st1 = malloc(i*sizeof(struct studentT));

	while(fgets(line, sizeof(line), fp)!=NULL)
	{
		buf = strtok(line, delim);
		int iter = 0;
		
		if(!strcmp(line,strdelim)){
			for(int k =0; k<4; k++){
				free(array[k]);
			}
			buf = NULL;
			free(buf);
			goto next;
		}


		while(buf!=NULL)
		{

			for(iter = 0; iter < 4; iter++)
			{
				array[iter] = malloc(sizeof(char)*strlen(buf));
				strcpy(array[iter], buf);
				buf = strtok(NULL,delim);
			}
		}

		st1[idx].name = malloc(sizeof(char)*strlen(array[0]));
		strcpy(st1[idx].name,array[0]);

		st1[idx].literature = atoi(array[1]);
		st1[idx].math = atoi(array[2]);
		st1[idx].science = atoi(array[3]);

		line[strlen(line)-1] = '\0';
		idx++;

	}

next:

	if(strcmp(fgets(buffer, sizeof(buffer), fp),"--")==0) printf("skipped delim\n");

	char *arr[4];
	char *buff;

	fgets(buffer, sizeof(buffer), fp);
	title2 = malloc(sizeof(char)*strlen(buffer));
	strcpy(title2,buffer);
	fscanf(fp, "%d", &j);

	idx = 0;

	st2 = malloc(i*sizeof(struct studentT));

	while(fgets(line, sizeof(line), fp)!=NULL)
	{
		buff = strtok(line, delim);
		int iter = 0;

		while(buff!=NULL)
		{
			for(iter = 0; iter<4; iter++)
			{
				arr[iter] = malloc(sizeof(char)*strlen(buff));
				strcpy(arr[iter], buff);
				buff = strtok(NULL, delim);
			}
		}

		st2[idx].name = malloc(sizeof(char)*strlen(arr[0]));
		strcpy(st2[idx].name,array[0]);

		st2[idx].literature=atoi(arr[1]);
		st2[idx].math=atoi(arr[2]);
		st2[idx].science=atoi(arr[3]);

		line[strlen(line)-1] = '\0';
		idx++;
	}


	//
	fclose(fp);
}

