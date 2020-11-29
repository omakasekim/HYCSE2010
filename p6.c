#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Tree{
	int key;
	struct Tree *left;
	struct Tree *right;
}Tree;

Tree* createNode(int item);
Tree* insertNode(Tree *root, int key);
Tree* deleteNode(Tree *root, int key);
Tree* findNode(Tree *root, int key);
Tree* minValNode(Tree *root);
void printInorder(Tree *root);
void printPreorder(Tree *root);
void printPostorder(Tree *root);
void Error(char* message){
	printf("%s\n", message);
}


void main(){

	FILE *fp = fopen("input.txt", "r");
	char ch,buf;
	char buffer[24];
	char *array[2];
	int x;

	struct Tree* tree = (Tree*)malloc(sizeof(struct Tree));
	fscanf(fp,"%c %d", &ch, &x);
	tree->key = x;
	tree->left = tree->right = NULL;
	fgets(buffer, sizeof(buffer), fp);

	while(fgets(buffer,sizeof(buffer),fp)!=NULL){
	    
	    if(strlen(buffer)<=3){
	        ch = 'p';
	        buf = buffer[1]; 
	    }
	   else{
	       sscanf(buffer,"%c %d", &ch, &x);
	   }
	    
		switch(ch){
			case 'i':
				{
					insertNode(tree, x);
					break;
				}

			case 'd':
				{
					deleteNode(tree, x);
					break;
				}

			case 'f':
				{
					findNode(tree, x);
					break;
				}

			case 'p':
				{
				    printf("\n");
					switch(buf){
						case 'i':
							printInorder(tree);
							printf("\n");
							break;
						case 'r':
							printPreorder(tree);
							printf("\n");
							
							break;
						case 'o':
							printPostorder(tree);
							printf("\n");
							break;
						default:
							break;
					}
					break;

				}
			default:
				break;
		}
	}
	fclose(fp);
}

Tree* createNode(int item){
    Tree* temp = (Tree*)malloc(sizeof(struct Tree));
	temp->key = item;
	temp->left = temp->right = NULL;
	
	return temp;
}


Tree* insertNode(Tree *root, int key){
	
	if(root == NULL) return createNode(key);
	
	if(key < root->key)
	    root->left = insertNode(root->left, key);
	else
	    root->right = insertNode(root->right, key);
	    
    return root;
}

Tree* deleteNode(Tree *root, int key){

	if(root == NULL){
		Error("key not found");
		return root;
	}

	if(key < root->key)
		root->left = deleteNode(root->left, key);

	else if(key > root->key)
		root->right = deleteNode(root->right, key);

	else
	{
		if(root->left == NULL)
		{
			struct Tree *temp = root->right;
			free(root);
			return temp;
		}
		
		else if(root->right == NULL)
		{
		    struct Tree *temp = root->left;
		    free(root);
		    return temp;
		}

		struct Tree *temp = minValNode(root->right);

		root->key = temp->key;

		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}

Tree* findNode(Tree *root, int key){
    if(root==NULL){
        printf("%d is not in the tree.\n", key);
    }
    
    if(root != NULL){
        
    	if(root->key == key){
        		printf("%d is in the tree\n", key);
    		    return root;
    	}
    
    	else if(key > root->key)
    		return findNode(root->right, key);
    
    	else if(key < root->key)
    	    return findNode(root->left, key);
    	    
        
    }
}

Tree* minValNode(Tree *root){
	struct Tree *current = root;

	while(current && current->left != NULL)
		current = current->left;

	return current;
}


void printInorder(Tree *root){
	if(root!=NULL){
	    printInorder(root->left);
	    printf("%d ", root->key);
	    printInorder(root->right);
	}
}

void printPreorder(Tree *root){
	if(root!=NULL){
	printf("%d ", root->key);
	printPreorder(root->left);
	printPreorder(root->right);
	}
}

void printPostorder(Tree *root){
	if(root!=NULL){
	printPostorder(root->left);
	printPostorder(root->right);
	printf("%d ", root->key);
	}
}

