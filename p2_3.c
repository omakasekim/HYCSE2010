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

void collectData();

int main(void){
	FILE *fp = fopen("input.txt", "r");

	int i,j;
	char title1[12];
	char title2[12];

	char tmpbuffer[24];
	char buffer[3];

	fgets(title1, 12, fp);
	title1[strlen(title1)-1] = '\0';
	fscanf(fp,"%d", &i);
	fgets(tmpbuffer, 24, fp);

	struct studentT *st1 = malloc(i*sizeof(struct studentT));
	collectData(st1, i, fp);

	fgets(tmpbuffer,24,fp);

	fgets(title2, 12, fp);
	title2[strlen(title2)-1] = '\0';
	fscanf(fp, "%d", &j);
	fgets(tmpbuffer,24,fp);
	struct studentT *st2 = malloc(j*sizeof(struct studentT));
	collectData(st2, j, fp);

	FILE *fout = fopen("output.txt", "w");

	int a1litsum;
	int a2litsum;
	int a1matsum;
	int a2matsum;
	int a1scisum;
	int a2scisum;

	for(int counter = 0; counter<i;counter++){
		a1litsum+=st1[counter].literature;
		a1matsum+=st1[counter].math;
		a1scisum+=st1[counter].science;
	}
	for(int counter = 0; counter<j;counter++){
		a2litsum+=st2[counter].literature;
		a2matsum+=st2[counter].math;
		a2scisum+=st2[counter].science;
	}

	float a1litave;
	float a2litave;
	float a1matave;
	float a2matave;
	float a1sciave;
	float a2sciave;


	a1litave = a1litsum/i;
	a1matave = a1matsum/i;
	a1sciave = a1scisum/i;

	a2litave = a2litsum/j;
	a2matave = a2matsum/j;
	a2sciave = a2scisum/j;

	fprintf(fout, "%s %.0f %.0f %.0f\n", title1, a1litave, a1matave, a1sciave);
	fprintf(fout, "%s %.0f %.0f %.0f", title2, a2litave, a2matave, a2sciave);

	fclose(fp);
	fclose(fout);
}

void collectData(studentT* stin, int student, FILE* ptr)
{

	char line[24];
	char *array[4];
	char delim[] = " ";
	int cnt = 0;

	while(fgets(line, sizeof(line), ptr)!=NULL && cnt<student){
		char* buf = strtok(line,delim);

		while(buf!=NULL){
			for(int t = 0; t<4; t++){
				array[t] = malloc(sizeof(char)*strlen(buf));
				strcpy(array[t],buf);
				buf = strtok(NULL,delim);
			}
			cnt++;
		}

		stin[cnt].name = malloc(sizeof(char)*strlen(array[0]));
		strcpy(stin[cnt].name,array[0]);

		stin[cnt].literature = atoi(array[1]);
		stin[cnt].math = atoi(array[2]);
		stin[cnt].science = atoi(array[3]);
		
		line[strlen(line)-1] ='\0';
		cnt++;
	}
}

