#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 50

void swap(char *x, char *y){
	char temp;
	temp = *x;
	*x = *y;
	*y = temp;
}

void permute(char *a, int l, int r){
	int i;

	if(l==r)
		printf("%s\n", a);
	else
	{
		for(i =l; i<=r; i++)
		{
			swap((a+l), (a+i));
			permute(a, l+1, r);
			swap((a+l), (a+i));
	
	}
}
}
int main()
{
	char *str =(char*)malloc(50*sizeof(char));
	scanf("%s", str);
	int n = strlen(str);
	permute(str, 0, n-1);
	return 0;
	free(str);
}

