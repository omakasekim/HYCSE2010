#include <stdio.h>

void swap(int **a, int **b);

int main()
{
	int A=10, B=20;
	int *pA, *pB;

	pA = &A;
	pB = &B;

	printf("Before A = %d\n", *pA);
	printf("Before B = %d\n", *pB);

	swap(&pA, &pB);

	printf("After A = %d\n", *pA);
	printf("After B = %d\n", *pB);
}

void swap(int **a, int **b)
{
	int *temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

