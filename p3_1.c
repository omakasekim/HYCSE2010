#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;
typedef int ElementType;
struct Node
{
	ElementType element;
	Position next;
};

List MakeEmpty(List L);
int IsEmpty(List L);
int IsLast(Position P, List L);
void Delete(ElementType X, List L);
Position FindPrevious(ElementType X, List L);
Position Find(ElementType X, List L);
void Insert(ElementType X, List L, Position P);
void DeleteList(List L);
void Display(List L);
void InsertAtHeader(ElementType X, List L);



void error(char *message){
	printf("%s\n", message);
	exit(1);
}


int main(void){
    List list = MakeEmpty(list);

	FILE *fp = fopen("input.txt", "r");

	char ch, buf;
	char buffer[24];
	int x,y;
	
	while(fscanf(fp,"%c %d %d",&ch,&x,&y)!=EOF){
		switch(ch){
			case 'i':
				{
					if(y==-1){
						Insert(x,list,list);
						printf("Inserted Key %d at Header.\n", x);
					}
					else
					{
					    if(Find(y,list) == NULL)
					    {
					        printf("could not find Position!\n");
					    }
					    else
					    {
					        Insert(x,list,Find(y,list));
					        printf("Inserted key %d at position behind %d.\n",x,y);
					    }
					}
					break;
				}
			case 'f':
				{
                    Position tmp = FindPrevious(x,list);
                    if(list->next == Find(x,list))
                        printf("Key of the previous node of %d is Header.\n", x);
                    else if(Find(x,list)==NULL)
                        printf("%d not found.\n", x);
                    else
					    printf("Key of the previous node of %d is %d.\n",x,tmp->element);
					break;
				}
			case 'd':
				{
					Delete(x,list);
					break;
				}
			case 'p':
				{
					Display(list);
					break;
				}
    			default:
    			    break;
		    }
	    }
	DeleteList(list);
	fclose(fp);
}

List MakeEmpty(List L){
	L = (List)malloc(sizeof(struct Node));
	L->element = 30;
	L->next = NULL;
	return L;
}//used to reset head pointer

int IsEmpty(List L){
	return L->next == NULL;
}//checks if List is empty

int IsLast(Position P, List L){
	Position cur = L;
	while(cur->next != NULL){
		cur = cur->next;
	}
	return P == cur;
}

void Delete(ElementType X, List L){
	Position P,TmpCell;
	P=FindPrevious(X,L);
	if(!IsLast(P,L)){
		TmpCell = P->next;
		P->next = TmpCell->next;
		free(TmpCell);
		printf("%d Deleted.\n",X);
	}
	else
	    printf("element %d not found.\n",X);
}

Position FindPrevious(ElementType X, List L){
	Position P;
	P=L;
	while(P->next != NULL && P->next->element!=X)
		P=P->next;
	return P;
}

Position Find(ElementType X, List L){
	Position P;
	P=L->next;
	while(P != NULL && P->element!=X)
		P=P->next;
	return P;
}

void Insert(ElementType X, List L, Position P){
	Position TmpCell;
	TmpCell = (Position)malloc(sizeof(struct Node));
	if(TmpCell == NULL)
		error("malloc err");
	TmpCell->element = X;
	TmpCell->next = P->next;
	P->next = TmpCell;
}

void DeleteList(List L){
	Position P = NULL;
	Position Tmp = NULL;
	P = L->next; /* Header assumed */
	L->next = NULL;
	while(P!=NULL)
	{
		Tmp = P->next;
		free(P);
		P = Tmp;
	}
}

void Display(List L){
	
	Position P;
	P = L->next;
	while(P!=NULL){
		printf("%d ->", P->element);
		P=P->next;
	}
	printf("\n");
}



