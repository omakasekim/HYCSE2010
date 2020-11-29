#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct studentT{
	char *name;
	int literature;
	int math;
	int science;
}studentT;

void collectData();

int main(void){
	FILE *fp = fopen("input.txt","r");
	int i;
	char tmpbuffer[24];

	fscanf(fp, "%d", &i);
	fgets(tmpbuffer,24,fp);
	
	struct studentT* record = malloc(i*sizeof(struct studentT));
	collectData(record,i,fp);

	FILE *fout;
	char *str1 = "Name   Literature    Math   Science    Ave.\n";
	fout = fopen("output.txt", "w");
	fprintf(fout,"%s\n", str1);

	float tempave;
	float stusum;
	for(int zidx=0;zidx<i;zidx++)
	{
		fprintf(fout, "%s\t %d\t %d\t%d\t", record[zidx].name, record[zidx].literature, record[zidx].math, record[zidx].science);

		tempave = (record[zidx].math + record[zidx].literature + record[zidx].science)/3;
		//fwrite(record[idx],sizeof(struct studentT),1,fout);
		fprintf(fout, "%.2f\n", tempave);
		stusum+=tempave;
	}
	float stuave = (stusum/3);

	float mathsum;
	float scisum;
	float litsum;

	for(int aidx=0;aidx<i;aidx++)
	{
		mathsum+=record[aidx].math;
		litsum+=record[aidx].literature;
		scisum+=record[aidx].science;
	}

	float mathave;
	float sciave;
	float litave;

	mathave = (mathsum/3);
	sciave = (scisum/3);
	litave = (litsum/3);

	stuave=((mathave+sciave+litave)/3);

	fprintf(fout, "Ave.\t%.2f\t%.2f\t%.2f\t%.2f", litave, mathave, sciave, stuave);

	fclose(fp);
	fclose(fout);
}

	




void collectData(studentT* stin, int student, FILE* ptr){

	char line[24];
	char *array[4];
	char delim[] = " ";
	int cnt = 0;
	while(fgets(line, sizeof(line), ptr)!=NULL && cnt < student)
	{
		char* buf = strtok(line,delim);
		while(buf!=NULL)
		{
			for(int t = 0;t<4;t++)
			{
				array[t] = malloc(sizeof(char)*strlen(buf));
				strcpy(array[t],buf);
				buf = strtok(NULL, delim);
			}

		}

		stin[cnt].name = malloc(sizeof(char)*strlen(array[0]));
		strcpy(stin[cnt].name,array[0]);

		stin[cnt].literature = atoi(array[1]);
		stin[cnt].math = atoi(array[2]);
		stin[cnt].science = atoi(array[3]);

		line[strlen(line)-1] = '\0';
		cnt++;
	}
}

