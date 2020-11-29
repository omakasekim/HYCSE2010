#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct HeapStruct {
	int Capacity;
	int Size;
	ElementType *Elements;
}HeapStruct;

void swap(int *a, int *b);
HeapStruct* CreateHeap(int heapsize);
void Insert(HeapStruct *Heap, ElementType value);
ElementType DeleteMin(HeapStruct *Heap);
void PrintHeap(HeapStruct *Heap);
void HeapifyBottomTop(HeapStruct *Heap, int index);
void HeapifyTopBottom(HeapStruct *Heap, int parent);

void main(){
    FILE *fp = fopen("input.txt", "r");
    char ch;
    char buffer[24];
    int x;
    
    struct HeapStruct root;
    struct HeapStruct *heap = &root;
    
    while(fscanf(fp, "%c %d", &ch, &x)!=EOF){
        switch(ch){
            case 'n':
            {
                heap = CreateHeap(x);
                break;
            }
            case 'i':
            {
                Insert(heap, x);
                break;
            }
            case 'd':
            {
                DeleteMin(heap);
                break;
            }
            case 'p':
            {
                PrintHeap(heap);
                break;
            }
            default:
            {
                break;
            }
        }
    }
    fclose(fp);
}

void swap(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

HeapStruct* CreateHeap(int heapsize)
{
	HeapStruct *h = (HeapStruct*)malloc(sizeof(HeapStruct));

	if(h==NULL){
		printf("malloc error!\n");
		return 0;
	}

	h->Size=0;
	h->Capacity = heapsize;
	h->Elements = (ElementType*)malloc(heapsize*sizeof(ElementType));

	if(h->Elements == NULL){
		printf("memory error!\n");
		return 0;
	}
	return h;
}

void Insert(HeapStruct *Heap, ElementType value)
{
	if(Heap->Size < Heap->Capacity)
	{
		Heap->Elements[Heap->Size] = value;
		HeapifyBottomTop(Heap, Heap->Size);
		Heap->Size++;
	}
	else
	    printf("Heap is full\n");
}

void HeapifyBottomTop(HeapStruct *Heap, int index)
{
	int temp;
	int parent = (index-1)/2;

	if(Heap->Elements[parent] > Heap->Elements[index])
	{
		temp = Heap->Elements[parent];
		Heap->Elements[parent] = Heap->Elements[index];
		Heap->Elements[index] = temp;
		HeapifyBottomTop(Heap,parent);
	}
}

void HeapifyTopBottom(HeapStruct *Heap, int parent){
	int left = parent*2 +1;
	int right = parent*2 +2;
	int min;
	int temp;

	if(left >= Heap->Size || left <0)
		left = -1;
	if(right >= Heap->Size || right <0)
		right = -1;

	if(left != -1 && Heap->Elements[left] < Heap->Elements[parent])
		min = left;
	else
		min = parent;
	
	if(right != -1 && Heap->Elements[right] < Heap->Elements[min])
		min = right;

	if(min != parent)
	{
		temp = Heap->Elements[min];
		Heap->Elements[min] = Heap->Elements[parent];
		Heap->Elements[parent] = temp;

		HeapifyTopBottom(Heap,min);
	}
}

ElementType DeleteMin(HeapStruct *Heap)
{
	int pop;
	if(Heap->Size == 0)
	{
		printf("Heap is Empty\n");
	}
    else
    {
	    pop = Heap->Elements[0];
	    Heap->Elements[0] = Heap->Elements[Heap->Size-1];
	    Heap->Size--;
	    HeapifyTopBottom(Heap,0);
    }
	return pop;
}

void PrintHeap(HeapStruct *Heap)
{
    int i;
    int level = 1;
    if(Heap->Size == 0){
        printf("Heap is Empty\n");
    }
    else
    {
        printf("_____Print Heap_____\n");
        for(i=0;i<Heap->Size;i++){
            if(i==level){
                printf("\n");
                level *= 2;
            }
            printf("\t%d", Heap->Elements[i]);
        }
        printf("\n===============\n");
    }
}
