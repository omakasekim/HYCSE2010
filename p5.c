#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct Tree_node{
	int key;
	struct Tree_node *left;
	struct Tree_node *right;
}Tree_node;

Tree_node* CreateNode(int key);
void Preorder(Tree_node* node);
void Inorder(Tree_node* node);
void Postorder(Tree_node* node);

int main(void){
	Tree_node *t1, *t2, *t3, *t4, *t5, *t6, *t7, *t8, *t9, *t10, *t11, *t12;
	t1 = CreateNode(0);
	t2 = CreateNode(1);
	t3 = CreateNode(2);
	t4 = CreateNode(3);
	t5 = CreateNode(4);
	t6 = CreateNode(5);
	t7 = CreateNode(6);
	t8 = CreateNode(7);
	t9 = CreateNode(8);
	t10 = CreateNode(9);
	t11 = CreateNode(10);
	t12 = CreateNode(11);

	t1->left = t2;
	t1->right = t3;
	t2->left = t4;
	t2->right = t5;
	t3->left = t6;
	t3->right = t7;
	t4->left = t8;
	t4->right = t9;
	t5->left = t10;
	t5->right = t11;
	t6->left = t12;
	t6->right = NULL;
	t7->left = NULL;
	t8->right = NULL;

	//
	printf("Preorder: ");
	Preorder(t1);
	printf("\n");
	printf("Inorder: ");
	Inorder(t1);
	printf("\n");
	printf("Postorder: ");
	Postorder(t1);
	getchar();
	return 0;

}


Tree_node* CreateNode(int key){
	Tree_node* node = (Tree_node*)malloc(sizeof(Tree_node*));
	node->key = key;
	node->left = node->right = NULL;
	return (node);
}

void Preorder(Tree_node* node){
	if(node == NULL)
		return;

	printf("%d ",node->key);
	Preorder(node->left);
	Preorder(node->right);
}

void Inorder(Tree_node* node){
	if(node == NULL)
		return;

	Inorder(node->left);
	printf("%d ", node->key);
	Inorder(node->right);
}

void Postorder(Tree_node* node){
	if(node == NULL)
		return;
	
	Postorder(node->left);
	Postorder(node->right);
	printf("%d ",node->key);
}

