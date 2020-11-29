#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#define IS_FULL(ptr) (!(ptr))
#define MAX_POLYNOMIAL_SIZE 100
#define COMPARE(x,y) (((x)<(y)) ? -1:((x)==(y)) ? 0:1)
#define FALSE 0
#define TRUE 1

typedef struct _poly_node *poly_pointer;
typedef struct _poly_node
{
	int coef;
	int expon;
	poly_pointer link;
}poly_node;

poly_pointer firstPolyHead, secondPolynomial, resultPolynomial;

poly_pointer PolynomialRead();
void PolynomialWrite(poly_pointer polynomial);
poly_pointer mult(poly_pointer first, poly_pointer second);
int divide(poly_pointer first, poly_pointer second, poly_pointer quotient, poly_pointer remainder);
void eval(poly_pointer polynomial, double f);
void attach(int coefficient, int exponent, poly_pointer *ptr);
poly_pointer cpadd(poly_pointer first, poly_pointer second);
poly_pointer nodeCreate(char* polyarray);
poly_pointer sub(poly_pointer first, poly_pointer second);
void cerase(poly_pointer *ptr);

void print_menu();
void sread();
void swrite();
void sadd();
void ssubstract();
void smulti();
void seval();
void serase();
void sread();
void sdiv();

int main(void)
{
	int MenuNumber;
	while(1)
	{
		print_menu();
		scanf("%d", &MenuNumber);
		fflush(stdin);

		switch(MenuNumber)
		{
			case 1:
				sread();
				break;
			case 2:
				swrite();
				break;
			case 3:
				sadd();
				break;
			case 4:
				ssubstract();
				break;
			case 5:
				smulti();
				break;
			case 6:
				seval();
				break;
			case 7:
				serase();
				break;
			case 8:
				sdiv();
				break;
			case 9:
				return 0;
			default:
				printf("invalid input\n");
				break;
		}
	}
}

void print_menu()
{
	printf("---------------------------\n");
	printf("\tM\tE\tN\tU\t\n");
	printf("1. Polynomial Read\n");
	printf("2. Polynomial Write\n");
	printf("3. Polynomial Addition\n");
	printf("4. Polynomial  Substraction\n");
	printf("5. Polynomial Multiplication\n");
	printf("6. Polynomial Evaluation\n");
	printf("7. Polynomial Erase\n");
	printf("8. Polynomial Division\n");
	printf("9. Exit\n");
	printf("---------------------------\n");
	printf("Select a menu\n");
	printf("Menu : ");
}

void swrite()
{
	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("----------Polynomial output----------\n");
		printf("1>> ");
		PolynomialWrite(firstPolyHead);

		printf("2>> ");
		PolynomialWrite(secondPolynomial);
	}
	else
		printf("Insert a polynomial\n");

}

void sadd()
{
	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("-----addition of first and second polynomial -----\n");
		PolynomialWrite(firstPolyHead);
		printf("          +\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = cpadd(firstPolyHead, secondPolynomial);

		printf("Result\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("Insert a polynomial\n");

}

void ssubstract()
{
	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("-----Substraction of second polynomial from the first-----\n");
		PolynomialWrite(firstPolyHead);
		printf("          -\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = sub(firstPolyHead, secondPolynomial);
		printf("Result\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("Insert a polynomial\n");

}
void smulti()
{
	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("-----Multiplication of first and second polynomial-----\n");
		PolynomialWrite(firstPolyHead);
		printf("          *\n");
		PolynomialWrite(secondPolynomial);

		resultPolynomial = mult(firstPolyHead, secondPolynomial);
		printf("Result\n");
		PolynomialWrite(resultPolynomial);
		cerase(&resultPolynomial);
	}
	else
		printf("Insert a polynomial\n");
}

void sdiv()
{
	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("-----Division of first and second polynomial-----\n");
		PolynomialWrite(firstPolyHead);
		printf("          /\n");
		PolynomialWrite(secondPolynomial);

		poly_pointer q = (poly_pointer)malloc(sizeof(poly_node));
		poly_pointer r = (poly_pointer)malloc(sizeof(poly_node));
		q = r = NULL;
		printf("Result: %d\n", divide(firstPolyHead, secondPolynomial, q, r));
	}
	else
		printf("Insert a polynomial\n");
}


void seval()
{
	double a;

	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("-----Evaluation of Polynomial with respect to an Interger-----\n");
		printf("Insert value of X\n");
		printf("Interger: ");
		scanf("%lf", &a);

		PolynomialWrite(firstPolyHead);
		printf("Eval of above Polynomial ");
		eval(firstPolyHead, a);
		PolynomialWrite(secondPolynomial);
		printf("Eval of above polynomial ");
		eval(secondPolynomial, a);
	}
	else
		printf("Insert a polynomial\n");
}

void serase()
{
	if(firstPolyHead!=NULL && secondPolynomial!=NULL)
	{
		printf("-----Remove all Polynomial-----\n");
		cerase(&firstPolyHead);
		cerase(&secondPolynomial);
	}
	else
		printf("No polynomial to remove!\n");
}

void sread()
{
	printf("Insert a polynomial in the form: 10x^3 + 5x^2 + 3x + 1\n");
	printf("----------First Polynomial----------\n");
	fflush(stdin);
	firstPolyHead = PolynomialRead();
	
	printf("----------Second Polynomial----------\n");
	fflush(stdin);
	secondPolynomial = PolynomialRead();
}






poly_pointer PolynomialRead()
{
	char c;
	int i=0;
	int j=0;

	char Poly[MAX_POLYNOMIAL_SIZE] = {'\0',};
	char poly[MAX_POLYNOMIAL_SIZE] = {'\0',};

	poly_pointer prePolynomial, Head = NULL, Tail = NULL;

	Head = (poly_pointer)malloc(sizeof(poly_node));
	if(IS_FULL(Head))
	{
		printf("Memory is full\n");
		exit(1);
	}

	Head->expon = -1;
	Head->link = Head;
	Tail = Head;

	printf("Polynomial: ");
	while((c=getchar())!='\n')
	{
		if(c==EOF)
		{
			printf("Program terminated\n");
			break;
		}
		if(c!=' ')
			Poly[i++] = c;
	}
	strcat(Poly, "\0");
	printf("\n");

	poly[0] = '\0';

	i=0;

	do{
		if(Poly[i] == '-' || Poly[i] == '+' || Poly[i] == '\0')
		{
			if(poly[0] != '\0')
			{
				poly[j] = '\0';
				prePolynomial = nodeCreate(poly);
				Tail->link = prePolynomial;
				Tail = Tail->link;
				Tail->link = Head;

				for(;j>0;j--)
					poly[j] = '\0';
			}
			poly[j] = Poly[i];
		}
		else
			poly[j] = Poly[i];
		j++;
	} while (Poly[i++]!='\0');

	fflush(stdin);
	return Head;
}

poly_pointer nodeCreate(char* polyarray)
{
	char poly[20] = {'\0'};
	int i,j;
	int check = 0;
	int transCoef = 0;
	int transExpon = 0;

	poly_pointer polynode;
	polynode = (poly_pointer)malloc(sizeof(poly_node));

	for(i=0, j=0; polyarray[i]!='\0';i++)
	{
		if(!(polyarray[i] == 'x' || polyarray[i] == 'X'))
		{
			poly[j] = polyarray[i];
			j++;
		}
		else if(polyarray[i] == 'x' || polyarray[i] == 'X')
		{
			check = 1;
			if(poly[0] == '\0')
				polynode->coef = 1;
			else
			{
				if(polyarray[i-1]=='+' || polyarray[i-1] =='-')
				{
					poly[j] ='1';
					j++;
				}
				poly[j] = '\0';
				
				transCoef = atoi(poly);
				polynode->coef = transCoef;
			}

			if(polyarray[i+1] =='^')
			{
				for(;j>0;j--)
					poly[j]='\0';
				i+=2;
				j=0;

				while(polyarray[i]!='\0')
				{
					poly[j++] = polyarray[i++];
				}
				poly[j] = '\0';
				transExpon = atoi(poly);
				polynode->expon = transExpon;
			}
			else
			{
				polynode->expon = 1;
			}
			break;
		}
	}

	if(poly!=NULL && check == 0)
	{
		poly[j] = '\0';
		transCoef = atoi(poly);
		polynode->coef = transCoef;
		polynode->expon = 0;
	}
	polynode->link = NULL;
	return polynode;
}

void PolynomialWrite(poly_pointer polynomial)
{
	poly_pointer Link;
	printf("equation : ");
	Link = polynomial->link;
	for(;Link->expon != -1; Link = Link->link)
	{
		if(Link->coef >= 0)
			printf("+%dx^%d ", Link->coef, Link->expon);
		else
			printf("%dx^%d ", Link->coef, Link->expon);
	}
	printf("\n");
}


poly_pointer cpadd(poly_pointer first, poly_pointer second)
{
	poly_pointer starta;
	poly_pointer d=NULL;
	poly_pointer lastd;
	int sum, done = FALSE;
	starta = first;

	first = first->link;
	second = second->link;

	d = (poly_pointer)malloc(sizeof(poly_node));
	if(IS_FULL(d))
	{
		printf("memory is full\n");
		exit(1);
	}

	d->expon = -1;
	lastd = d;
	do{
		switch(COMPARE(first->expon, second->expon))
		{
			case -1:
				attach(second->coef, second->expon, &lastd);
				second = second->link;
				break;
			case 0:
				if(starta == first)
				{
					done = TRUE;
				}
				else
				{
					sum = first->coef + second->coef;
					if(sum)
						attach(sum, first->expon, &lastd);
					first = first->link;
					second = second->link;
				}
				break;
			case 1:
				attach(first->coef, first->expon, &lastd);
				first = first->link;
		}
	}while(!done);
	lastd->link = d;
	return d;
}

void attach(int coefficient, int exponent, poly_pointer *ptr)
{
	poly_pointer temp;
	temp = (poly_pointer)malloc(sizeof(poly_node));
	if(IS_FULL(temp))
	{
		printf("memory is full\n");
		exit(1);
	}
	temp->coef = coefficient;
	temp->expon = exponent;
	(*ptr)->link = temp;
	*ptr = temp;
}


poly_pointer sub(poly_pointer first, poly_pointer second)
{
	poly_pointer starta, d, lastd;
	int subresult, done = FALSE;
	starta = first;

	first = first->link;
	second = second->link;

	d =(poly_pointer)malloc(sizeof(poly_node));
	if(IS_FULL(d))
	{
		printf("Memory is full\n");
		exit(1);
	}

	d->expon = -1;
	lastd = d;
	
	do{
		switch(COMPARE(first->expon, second->expon))
		{
			case -1:
				second->coef = (-1)*second->coef;
				attach(second->coef, second->expon, &lastd);
				second = second->link;
				break;
			case 0:
				if(starta == first)
					done = TRUE;
				else
				{
					subresult = first->coef - second->coef;
					if(subresult)
						attach(subresult, first->expon, &lastd);
					first = first->link;
					second = second->link;
				}
				break;
			case 1:
				attach(first->coef, first->expon, &lastd);
				first = first->link;
		}
	}while(!done);
	lastd->link = d;
	return d;
}


poly_pointer mult(poly_pointer first, poly_pointer second)
{
	poly_pointer startfirst, startsecond, temp;
	poly_pointer resulta, resultc, lasta, lastc;

	startfirst = first->link;
	startsecond = second->link;

	resulta = (poly_pointer)malloc(sizeof(poly_node));

	if(IS_FULL(resulta))
	{
		printf("memory is full\n");
		exit(1);
	}
	resulta->coef = -1;
	resulta->expon = -1;
	lasta = resulta;
	lasta->link = resulta;

	resultc = (poly_pointer)malloc(sizeof(poly_node));
	if(IS_FULL(resultc))
	{
		printf("memory is full\n");
		exit(1);
	}
	resultc->coef = -1;
	resultc->expon = -1;
	lastc =  resultc;
	lastc->link = resultc;

	for(;startsecond->expon != -1; startsecond = startsecond->link)
	{
		for(;startfirst->expon!=-1;startfirst = startfirst->link)
		{
			temp = (poly_pointer)malloc(sizeof(poly_node));
			if(IS_FULL(temp))
			{
				printf("memory is full\n");
				exit(1);
			}
			temp->coef = startfirst->coef * startsecond->coef;
			temp->expon = startfirst->expon + startsecond->expon;
			temp->link = lasta->link;
			lasta->link = temp;
			lasta = temp;

			resultc= cpadd(resultc,resulta);
			resulta->link = lasta->link;
			free(lasta);
			lasta = resulta;
		}
		startfirst = startfirst->link;
	}
	return resultc;
}

void eval(poly_pointer polynomial, double f)
{
	int expon;
	double sum = 0;
	double multsum = 1;
	poly_pointer Link;

	Link = polynomial->link;
	for(;Link->expon != -1;Link = Link->link)
	{
		for(expon = Link->expon;expon>0;expon--)
			multsum = multsum*f;
		if(Link->expon != 0)
			sum = sum + (Link->coef * multsum);
		else
			sum = sum + Link->coef;
		multsum = 1;
	}
	printf("result of evaluating %0.5f : %0.5f\n", f, sum);
}

void cerase(poly_pointer *ptr)
{
	poly_pointer temp, last;

	temp = (*ptr)->link;
	while(temp!=*ptr)
	{
		last = temp->link;
		free(temp);
		temp = last;
	}
	free(*ptr);
}


int divide(poly_pointer first, poly_pointer second, poly_pointer quotient, poly_pointer remainder)
{
	int exp, coef;

	quotient = second->link;
	remainder = first->link;

	while(quotient->expon <= remainder->expon){

	exp = remainder->expon - quotient->expon;
	coef = remainder->coef - quotient->coef;
	attach(coef,exp,&quotient);

	remainder = sub(first,mult(second,quotient));
	quotient = quotient->link;
	if(remainder->coef == 0)return 1;
	}
return 0;
}



