#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print(int list[], int n);
void heapify(int arr[], int n, int i);
void heapsort(int arr[], int n);
void swap(int *a, int *b);

void swap(int *a, int *b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print(int list[], int n)
{
	int i;
	for(i=0; i<n; i++)
		printf("%d ", list[i]);
	printf("\n");
}

void heapify(int arr[], int n, int i)
{
	int largest = i;
	int left = 2*i+1;
	int right = 2*i+2;

	if(left < n && arr[left] > arr[largest])
		largest = left;
	if(right < n && arr[right] > arr[largest])
		largest = right;
	
	if(largest != i){
		swap(&arr[i], &arr[largest]);
		heapify(arr, n, largest);

	}
}

void heapSort(int arr[], int n)
{
	for(int i = n / 2 - 1 ; i >= 0; i--)
		heapify(arr, n, i);

	for(int i = n - 1; i >= 0; i--){
		swap(&arr[0], &arr[i]);

		heapify(arr, i, 0);
	}
}

int main()
{
	int heaparr[10] = {};
	int x = sizeof(heaparr)/ sizeof(heaparr[0]);

	FILE *fp = fopen("input.txt", "r");

	int za, zb, zc, zd, ze, zf, zg, zh, zi, zj;
	//could use strtok loop but inefficient;
	fscanf(fp, "%d %d %d %d %d %d %d %d %d %d", &za, &zb, &zc, &zd, &ze, &zf, &zg, &zh, &zi, &zj);

			heaparr[0] = za;
			heaparr[1] = zb;
			heaparr[2] = zc;
			heaparr[3] = zd;
			heaparr[4] = ze;
			heaparr[5] = zf;
			heaparr[6] = zg;
			heaparr[7] = zh;
			heaparr[8] = zi;
			heaparr[9] = zj;

			heapSort(heaparr, x);
			printf("Heapsort: ");
			print(heaparr, 10);

			fclose(fp);

			return 0;
			}

