#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define SWAP(x,y,t) ( (t) = (x), (x) = (y), (y) = (t) )
//void mergeSort(int data[], int p, int r);
//void merge(int data[], int p, int q, int r);
void quick_sort(int list[], int left, int right);
void print(int list[], int n);
int partition(int v[], int left, int right);

/*
void mergeSort(int data[], int p, int r)
{
	int q;
	if(p<r)
	{
		q = (p+r)/2;
		mergeSort(data, p, q);
		mergeSort(data, q+1, r);
		merge(data, p, q, r);
	}
}

void merge(int data[], int p, int q, int r)
{
	int i = p, j = q +1, k = p;
	int tmp[8];
	while(i <= q && j <= r)
	{
		if (data[i] <= data[j])
			tmp[k++] = data[i++];
		else
			tmp[k++] = data[j++];
	}
	while(i <= q)
		tmp[k++] = data[i++];
	while(j <= r)
		tmp[k++] = data[j++];
	for(int a = p; a<= r; a++)
		data[a] = tmp[a];
}
*/

void quick_sort(int list[], int left, int right)
{
	if(left<right){

		int q = partition(list, left, right);
		print(list, 9);

		quick_sort(list, left, q-1);
		quick_sort(list, q+1, right);
	}
}

void print(int list[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

int partition(int v[], int left, int right)
{
	int pivot, temp;
	int low, high;

	low = left;
	high = right+1;

	pivot = v[left];

	do{
		do{
			low++;
		}while(low <= right && v[low] < pivot);

		do{
			high--;
		}while(high >= left && v[high] > pivot);

		if(low < high)
			SWAP(v[low], v[high], temp);
	}while(low < high);

	SWAP(v[left], v[high], temp);

	return high;
}

int main(){
	int list[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
		quick_sort(list, 0, 8);
	
return 0;
}

