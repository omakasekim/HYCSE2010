#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 50
#define IS_FULL(ptr) (!(ptr))
#define COMPARE(x,y) (((x)<(y)) ? -1:((x)==(y)) ? 0:1)
#define FALSE 0
#define TRUE 1



typedef enum
{
	head,
	entry
}tagfield;
typedef struct matrix_node *matrix_pointer;

typedef struct entry_node
{
	int row;
	int col;
	int value;
}entry_node;

typedef struct matrix_node
{
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union
	{
		matrix_pointer next;
		entry_node entry;
	}u;
}matrix_node;

matrix_pointer hdnode[MAX_SIZE];

matrix_pointer mread(void);
matrix_pointer new_node(void);
void mwrite(matrix_pointer node);
void merase(matrix_pointer *node);
matrix_pointer madd(matrix_pointer m1, matrix_pointer m2);
matrix_pointer mtranspose(matrix_pointer node);
matrix_pointer mmult(matrix_pointer m1, matrix_pointer m2);
void printf_menu();


void main()
{
	int MenuNumber;
	matrix_pointer matrix1 = NULL, matrix2 = NULL, matrix3 = NULL;
	
	while(1)
	{
		printf_menu();
		scanf("%d", &MenuNumber);
		fflush(stdin);

		if(MenuNumber == 1)
		{
			printf("---------------\n");
			printf("Insert first matrix\n");
			matrix1 = mread();

			printf("\n");
			printf("Insert second matrix\n");
			matrix2 = mread();
		}

		if(MenuNumber == 2)
		{
			if(matrix1 != NULL && matrix2 != NULL)
			{
				printf("---------------\n");
				printf("Writing first matrix\n");
				mwrite(matrix1);
				printf("\n");

				printf("Writing second matrix\n");
				mwrite(matrix2);
			}
			else
				printf("Insert a matrix\n");
		}
		if(MenuNumber == 3)
		{
			if(matrix1 != NULL && matrix2 != NULL)
			{
				printf("---------------\n");
				printf("Removing matrices\n");
				merase(&matrix1);
				merase(&matrix2);
			}
			else
				printf("There is no matrix to remove\n");
		}
		if(MenuNumber == 4)
		{
			if(matrix1 != NULL && matrix2 != NULL)
			{
				printf("---------------\n");
				printf("Addition of two matrices\n");

				matrix3 = madd(matrix1, matrix2);

				if(matrix3 != NULL)
				{
					mwrite(matrix3);
					merase(&matrix3);
				}
			}
			else
				printf("Insert a matrix\n");
		}
		if(MenuNumber == 5)
		{
			if(matrix1 != NULL && matrix2 != NULL)
			{
				printf("---------------\n");
				printf("Multiplication of two matrices\n");

				matrix3 = mmult(matrix1, matrix2);

				if(matrix3 != NULL)
				{
					mwrite(matrix3);
					merase(&matrix3);
				}
			}
			else
				printf("Insert a matrix\n");
		}
		if(MenuNumber == 6)
		{
			if(matrix1 != NULL && matrix2 != NULL)
			{
				printf("---------------\n");
				printf("Transposing matrix\n");

				matrix3 = mtranspose(matrix1);

				mwrite(matrix3);
				merase(&matrix3);

				matrix3 = mtranspose(matrix2);
				mwrite(matrix3);
				merase(&matrix3);
			}
			else
				printf("Insert a matrix\n");
		}
		if(MenuNumber == 7)
			exit(0);
	}
}




void printf_menu()
{
	printf("---------------------------\n");
	printf("\tM\tE\tN\tU\t\n");
	printf("1. Matrix Read\n");
	printf("2. Matrix Write\n");
	printf("3. Matrix Erase\n");
	printf("4. Matrix Add\n");
	printf("5. Matrix Multiply\n");
	printf("6. Matrix Transpose\n");
	printf("7. Program Termination\n");
	printf("---------------------------\n");
	printf("Select a menu\n");
	printf("Menu: ");
}

matrix_pointer mread(void)
{
	int num_rows, num_cols, num_terms, num_heads, i;
	int row, col, value, current_row;
	matrix_pointer temp, last, node;

	printf("Enter the number of rows, columns and number of non-zero terms: ");
	scanf("%d%d%d", &num_rows, &num_cols, &num_terms);
	num_heads = (num_cols > num_rows) ? num_cols:num_rows;

	node = new_node();
	node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if(!num_heads)
		node->right = node;
	else
	{
		for(i=0;i<num_heads;i++)
		{
			temp = new_node();
			hdnode[i] = temp;
			hdnode[i]->tag = head;
			hdnode[i]->right = temp;
			hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = hdnode[0];

		for(i=0;i<num_terms;i++)
		{
			printf("Enter row, column and value: ");
			scanf("%d%d%d", &row, &col, &value);
			if(row>current_row)
			{
				last->right = hdnode[current_row];
				current_row = row;
				last = hdnode[row];
			}

			temp = new_node();
			temp->tag = entry;
			temp->u.entry.row = row;
			temp->u.entry.col = col;
			temp->u.entry.value = value;
			last->right = temp;
			last = temp;

			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}

		last->right = hdnode[current_row];

		for(i=0;i<num_cols;i++)
			hdnode[i]->u.next->down = hdnode[i];

		for(i=0;i<num_heads-1;i++)
			hdnode[i]->u.next = hdnode[i+1];
		hdnode[num_heads-1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}




matrix_pointer new_node(void)
{
	matrix_pointer temp;
	temp = (matrix_pointer)malloc(sizeof(matrix_node));
	if(IS_FULL(temp))
	{
		printf("memory is full\n");
		exit(1);
	}
	return temp;
}

void mwrite(matrix_pointer node)
{
	int i;
	matrix_pointer temp, head = node->right;

	printf("\n num_rows = %d, num_cols = %d\n", node->u.entry.row, node->u.entry.col);
	printf("The matrix by row, column, and value: \n\n");
	for(i=0;i<node->u.entry.row;i++)
	{
		for(temp = head->right; temp!=head; temp = temp->right)
			printf("%5d%5d%5d\n",temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
		head = head->u.next;
	}
}

void merase(matrix_pointer *node)
{
	matrix_pointer x, y, head = (*node)->right;
	int i;
	
	for(i=0; i<(*node)->u.entry.row;i++)
	{
		y = head->right;
		while(y!=head)
		{
			x = y;
			y = y->right;
			free(x);
		}
		x = head;
		head = head->u.next;
		free(x);
	}

	y = head;
	while(y!=*node)
	{
		x = y;
		y = y->u.next;
		free(x);
	}
	free(*node);
	*node = NULL;
}


matrix_pointer madd(matrix_pointer m1, matrix_pointer m2)
{
	int i, m3_heads, current_row;
	matrix_pointer temp1, temp2, temp3, m3 = NULL;
	matrix_pointer head1, head2, node, temp;
	matrix_pointer m3_hdnode[MAX_SIZE], last;

	head1 = m1->right;
	head2 = m2->right;

	if(m1->u.entry.col != m2->u.entry.col || m1->u.entry.row != m2->u.entry.row)
	{
		printf("size of the matrices are different: cannot add.\n");
		return NULL;
	}

	m3 = new_node();
	m3->tag = entry;
	m3->u.entry.row = m1->u.entry.row;
	m3->u.entry.col = m1->u.entry.col;
	m3_heads = (m3->u.entry.col > m3->u.entry.row) ? m3->u.entry.col : m3->u.entry.row;

	if(!m3_heads)
		m3->right = m3;
	else
	{
		for(i=0;i<m3_heads;i++)
		{
			temp3 = new_node();
			m3_hdnode[i] = temp3;
			m3_hdnode[i]->tag = head;
			m3_hdnode[i]->right = temp3;
			m3_hdnode[i]->u.next = temp3;
		}

		current_row = 0;
		last = m3_hdnode[0];

		temp1 = m1->right;
		temp2 = m2->right;

		while(!(temp1 == m1 && temp2 == m2))
		{
			if(temp1->tag == head)
			{
				if(temp1->right == temp1)
				{
					temp1 = temp1->u.next;
					continue;
				}
				temp1 = temp1->right;
			}
			if(temp2->tag == head)
			{
				if(temp2->right == temp2)
				{
					temp2 = temp2->u.next;
					continue;
				}
				temp2 = temp2->right;
			}

			switch(COMPARE(temp1->u.entry.row, temp2->u.entry.row))
			{
				case -1:
					temp = temp1;
					temp1 = temp1->right;
					break;
				case 0:
					switch(COMPARE(temp1->u.entry.col, temp2->u.entry.col))
					{
						case -1:
							temp = temp1;
							temp1 = temp1->right;
							break;
						case 0:
							temp = NULL;
							if(temp1->u.entry.row > current_row)
							{
								last->right = m3_hdnode[current_row];
								current_row = temp1->u.entry.row;
								last = m3_hdnode[temp1->u.entry.row];
							}

							node = new_node();
							node->tag = entry;
							node->u.entry.row = temp1->u.entry.row;
							node->u.entry.col = temp1->u.entry.col;
							node->u.entry.value = temp1->u.entry.value + temp2->u.entry.value;
							last->right = node;
							last = node;

							m3_hdnode[temp1->u.entry.col]->u.next->down = node;
							m3_hdnode[temp1->u.entry.col]->u.next = node;

							temp1 = temp1->right;
							temp2 = temp2->right;
							break;

						case 1:
							temp = temp2;
							temp2 = temp2->right;
							break;
					}
					break;

				case 1:
					temp = temp2;
					temp2 = temp2->right;
					break;
			}

			if(temp != NULL)
			{
				if(temp->u.entry.row > current_row)
				{
					last->right = m3_hdnode[current_row];
					current_row = temp->u.entry.row;
					last = m3_hdnode[temp->u.entry.row];
				}

				node = new_node();
				node->tag = entry;
				node->u.entry.row = temp->u.entry.row;
				node->u.entry.col = temp->u.entry.col;
				node->u.entry.value = temp->u.entry.value;
				last->right = node;
				last = node;

				m3_hdnode[temp->u.entry.col]->u.next->down = node;
				m3_hdnode[temp->u.entry.col]->u.next = node;
			}

			if(temp1->tag == head)
				temp1 = temp1->u.next;
			if(temp2->tag == head)
				temp2 = temp2->u.next;
		}

		last->right = m3_hdnode[current_row];

		for(i=0;i<m3->u.entry.col;i++)
			m3_hdnode[i]->u.next->down = m3_hdnode[i];

		for(i=0;i<m3_heads-1;i++)
			m3_hdnode[i]->u.next = m3_hdnode[i+1];
		m3_hdnode[m3_heads-1]->u.next = m3;
		m3->right = m3_hdnode[0];
	}
	return m3;
}

matrix_pointer mtranspose(matrix_pointer node)
{
	int num_heads, num_cols, num_rows, i, j, current_row;
	int row, col, value;
	matrix_pointer transpose_node, temp, last;
	matrix_pointer trans_hdnode[MAX_SIZE];
	matrix_pointer node_head = node->right, node_temp;

	num_cols = node->u.entry.row;
	num_rows = node->u.entry.col;
	num_heads = (num_cols > num_rows) ? num_cols : num_rows;

	transpose_node = new_node();
	transpose_node->tag = entry;
	transpose_node->u.entry.row = num_rows;
	transpose_node->u.entry.col = num_cols;

	if(!num_heads)
		transpose_node->right = transpose_node;
	else
	{
		for(i=0;i<num_heads;i++)
		{
			temp = new_node();
			trans_hdnode[i] = temp;
			trans_hdnode[i]->tag = head;
			trans_hdnode[i]->right = temp;
			trans_hdnode[i]->u.next = temp;
		}
		current_row = 0;
		last = trans_hdnode[0];

		for(j=0;j<node->u.entry.row;j++)
		{
			for(node_temp = node_head->right; node_temp != node_head; node_temp = node_temp->right)
			{
				row = node_temp->u.entry.col;
				col = node_temp->u.entry.row;
				value = node_temp->u.entry.value;
				if(row > current_row)
				{
					last->right = trans_hdnode[current_row];
					current_row = row;
					last = trans_hdnode[row];
				}

				temp = new_node();
				temp->tag = entry;
				temp->u.entry.row = row;
				temp->u.entry.col = col;
				temp->u.entry.value = value;
				last->right = temp;
				last = temp;

				trans_hdnode[col]->u.next->down = temp;
				trans_hdnode[col]->u.next = temp;
			}
			node_head = node_head->u.next;
		}

		last->right = trans_hdnode[current_row];
		for(i=0;i<num_cols;i++)
			trans_hdnode[i]->u.next->down = trans_hdnode[i];
		for(i=0;i<num_heads-1;i++)
			trans_hdnode[i]->u.next = trans_hdnode[i+1];
		trans_hdnode[num_heads-1]->u.next = transpose_node;
		transpose_node->right = trans_hdnode[0];
	}
	return transpose_node;
}

matrix_pointer mmult(matrix_pointer m1, matrix_pointer m2)
{
	int num_rows, num_cols, num_heads, i, j;
	int row, col, value, current_row;
	int done = FALSE;

	matrix_pointer temp, last, mult_node = NULL, find_node;
	matrix_pointer mult_hdnode[MAX_SIZE];
	matrix_pointer m1_head, m2_head, m1_temp, m2_temp;

	if(m1->u.entry.col == m2->u.entry.row)
	{
		m1_head = m1->right;
		m2_head = m2->right;
		
		num_rows = m1->u.entry.row;
		num_cols = m2->u.entry.col;
		num_heads = (num_cols > num_rows) ? num_cols : num_rows;

		mult_node = new_node();
		mult_node->tag = entry;
		mult_node->u.entry.row = num_rows;
		mult_node->u.entry.col = num_cols;

		if(!num_heads)
			mult_node->right = mult_node;
		else
		{
			for(i=0;i<num_heads;i++)
			{
				temp = new_node();
				mult_hdnode[i] = temp;
				mult_hdnode[i]->tag = head;
				mult_hdnode[i]->right = temp;
				mult_hdnode[i]->u.next = temp;
			}
			current_row = 0;
			last = mult_hdnode[0];

			for(i = 0; i<m1->u.entry.row;i++)
			{
				row = 0, col = 0, value = 0;

				for(j = 0; j<m2->u.entry.col;)
				{
					if(j == 0 && done == FALSE)
					{
						m1_temp = m1_head->right;
						m2_temp = m2_head->down;
					}

					if(m2_temp->tag == head || m2_temp->down == m2_temp)
					{
						done = FALSE;
						m2_head = m2_head->u.next;
						m2_temp = m2_head->down;

						m1_temp = m1_head->right;
						row = 0, col = 0, value = 0;
						j++;
					}

					if(m1_temp->tag == head)
					{
						if(m1_temp->right == m1_temp)
						{
							done = FALSE;
							break;
						}

						if(m2_head->u.next != m2)
						{
							m1_temp = m1_head->right;
							row = 0, col = 0, value = 0;
							m2_head = m2_head->u.next;
							m2_temp = m2_head->down;
							done = FALSE;
							j++;
						}
						else
							j++;
					}

					if( j>= m2->u.entry.col)
						break;

					switch(COMPARE(m1_temp->u.entry.col, m2_temp->u.entry.row))
					{
						case -1:
							m1_temp = m1_temp->right;
							done = TRUE;
							continue;
						case 0:
							done = TRUE;
							if(value != 0)
							{
								row = m1_temp->u.entry.row;
								col = m2_temp->u.entry.col;
								find_node = mult_hdnode[row]->right;
								while(1)
								{
									if(find_node->u.entry.col == col)
									{
										find_node->u.entry.value = find_node->u.entry.value + value;
										break;
									}
									else
										find_node = find_node->right;

									if(find_node->tag == head)
										break;
								}
								m1_temp = m1_temp->right;
								m2_temp = m2_temp->down;
							}
							else if(value == 0)
							{
								row = m1_temp->u.entry.row;
								col = m2_temp->u.entry.col;
								value = m1_temp->u.entry.value * m2_temp->u.entry.value;
								if(row > current_row)
								{
									last->right = mult_hdnode[current_row];
									current_row = row;
									last = mult_hdnode[row];
								}
								temp = new_node();
								temp->tag = entry;
								temp->u.entry.row = row;
								temp->u.entry.col = col;
								temp->u.entry.value = value;
								last->right = temp;
								last = temp;

								mult_hdnode[col]->u.next->down = temp;
								mult_hdnode[col]->u.next = temp;
								m1_temp = m1_temp->right;
								m2_temp = m2_temp->down;
							}
							continue;
						case 1:
							done = TRUE;
							m2_temp = m2_temp->down;
							continue;
					}
				}
				m1_head = m1_head->u.next;
				m2_head = m2->right;
				done = FALSE;
			}

			last->right = mult_hdnode[current_row];
			for(i =0; i<num_cols;i++)
				mult_hdnode[i]->u.next->down = mult_hdnode[i];

			for(i=0;i<num_heads-1;i++)
				mult_hdnode[i]->u.next = mult_hdnode[i+1];
			mult_hdnode[num_heads-1]->u.next = mult_node;
			mult_node->right = mult_hdnode[0];
		}
	}
	else
	{
		printf("cannot mmult\n");
		return NULL;
	}
	return mult_node;
}


	





