#include <stdio.h>

int fibonacci(int num);

int main(void){
	int num;

	printf("n = ");
	scanf("%d", &num);

	for(int i = 0; i<=num; i++){
		printf("p%d = %d\n", i, fibonacci(i));
	}

	return 0;
}

int fibonacci(int num){
	switch(num){
	case 0:
		return 0;
	case 1:
		return 1;
	default:
		return(fibonacci(num-1) + fibonacci(num-2));
	}

}
