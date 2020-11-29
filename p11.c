#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int ElementType;

struct HashTable{
	int TableSize;
	ElementType* TheLists;
};

void Insert(ElementType key, struct HashTable *H);
int Find(struct HashTable *H, ElementType value);
int HashFunction(ElementType key, struct HashTable *H);

void Insert(ElementType key, struct HashTable *H)
{
	int index = HashFunction(key, H);
	if(Find(H, key)==1){
			printf("Duplicated value[%d]\n", key);
			return;
			}

	else if(H->TheLists[index] != 0){
		printf("collision for the key [%d] has occured.\n", key);
		while(1){
			if((H->TheLists[index++])!= 0){
				H->TheLists[index] = key;
				break;
			}
			else
				index++;
		}
	}
	else
	{
		H->TheLists[index] = key;
	}	
}

int Find(struct HashTable *H, ElementType value)
{
	for(int i = 0; i< H->TableSize; i++)
	{
		if((int)value == (int)H->TheLists[i])
			return 1;
	}
	return 0;
}

int HashFunction(ElementType key, struct HashTable *H)
{
	return key % H->TableSize;
}

void MainPrint(struct HashTable *H)
{
	for(int i = 0; i < H->TableSize; i++)
	{
		printf("<%d> => ", i);
		if(H->TheLists[i] != 0)
			printf("[%d]\n", H->TheLists[i]);
		else
			printf("\n");
	}
}


void MainFind(struct HashTable *H, ElementType value)
{
	if(Find(H, value) != 0)
		printf("The key [%d] exists in the list\n", value);
	else
		printf("The key [%d] doesn't exist in the list\n", value);
}


void main()
{
	struct HashTable Hash;
	FILE *fp = fopen("input.txt", "r");
	int size;
	fscanf(fp,"%d\n",&size);
	Hash.TableSize = size;
	Hash.TheLists = (ElementType*)malloc(size*sizeof(ElementType));

	char delim[] = " ";
	char line[100];
	int idx = 0;
	int buffer[14];

	fgets(line, sizeof(line), fp);
	char *buf = strtok(line, delim);
	while(buf != NULL){
		buffer[idx++] = atoi(buf);
		buf = strtok(NULL, delim);
	}

	for(int i = 0; i<14;i++){
		Insert(buffer[i], &Hash);
	}

	idx = 0;
	int finder[5];
	fgets(line, sizeof(line), fp);
	buf = strtok(line, delim);
	while(buf != NULL){
		finder[idx++] = atoi(buf);
		buf = strtok(NULL, delim);
	}

	for(int i = 0; i < 5; i++){
		MainFind(&Hash, finder[i]);
}
	MainPrint(&Hash);
	fclose(fp);
}
