#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _tree;
typedef struct _tree*Position;
typedef struct _tree {
	int el;
Position left;
Position right;
}tree;

Position input(Position,int);
Position find(int,Position);
Position findMin(Position);
Position findMax(Position);
int inorder(Position);
int preorder(Position);
int postorder(Position);
Position deleteAll(Position);
int deleteEl(Position, int);

int main() {
	Position root=NULL;
	Position newEl = NULL;
	Position temp = NULL;
	int c=0,x;

	puts("Input-1\nfind-2\nfindMin-3\nfindMax-4\ninorder-5\npreorder-6\npostorder-7\ndeleteAll-8\ndeleteEl-9\nexit program-10\n");
	while (1) {
	puts("Choose an option:");
	scanf("%d", &c);
		switch (c) {
		case 1:
			puts("Type in an element:");
			scanf(" %d", &x);
			root = input(root, x);
			break;
		case 2:
			puts("Type in an element:");
			scanf(" %d", &x);
			temp = find(x, root);
			break;
		case 3:
			temp = findMin(root);
			printf("Min. el is %d\n", temp->el);
			break;
		case 4:
			temp = findMax(root);
			printf("Max. el is %d\n", temp->el);
			break;
		case 5:
			puts("Inorder:");
			inorder(root);
			puts("");
			break;
		case 6:
			puts("Preorder:");
			preorder(root);
			puts("");
			break;
		case 7:
			puts("Postorder:");
			postorder(root);
			puts("");
			break;
		case 8:
			root=deleteAll(root);
			puts("All elements are deleted");
			break;
		case 9:
			puts("Type in an element:");
			scanf(" %d", &x);
			deleteEl(root, x);
			printf("Element %d is deleted", x);
			break;
		case 10:
			return 0;
			
		}
	}
}

Position input(Position P, int x) {

	if (NULL == P) {
		P = (Position)malloc(sizeof(tree));
		if (NULL == P)
		{
			puts("Allocation failed");
			return NULL;
		}
		else
		{
			P->el = x;
			P->left = NULL;
			P->right = NULL;
		}
	}
	else if (x < P->el)
		P->left=input(P->left,x);
	else if (x > P->el)
		P->right=input(P->right,x);

	return P;
}

Position find(int x ,Position P) {
	if (NULL == P) {
		puts("Element not found");
		return NULL;
	}
	else if (x < P->el)
		return find(x, P->left);
	else if (x > P->el)
		return find(x, P->right);
	return P;
}

Position findMin(Position P) {
	if (NULL == P) {
		puts("Empty tree");
		return NULL;
	}
	else if (P->left != NULL)
		return findMin(P->left);

	return P;
}

Position findMax(Position P) {
	if (NULL == P) {
		puts("Empty tree");
		return NULL;
	}
	else if (P->right != NULL)
		return findMax(P->right);

	return P;
}
int inorder(Position P) {
	if (NULL == P) {
		return NULL;
	}
	inorder(P->left);
	printf("%d ", P->el);
	inorder(P->right);
	
}

int preorder(Position P) {
	if (NULL == P) {
		return NULL;
	}
	printf("%d ", P->el);
	inorder(P->left);
	inorder(P->right);
	
}

int postorder(Position P) {
	if (NULL == P) {
		return NULL;
	}
	inorder(P->left);
	inorder(P->right);
	printf("%d ", P->el);
	
}
Position deleteAll(Position P) {
	if (P != NULL) {
		deleteAll(P->left);
		deleteAll(P->right);
		free(P);
	}
		return NULL;
}

int deleteEl(Position P, int x) {
	Position temp;

	if (NULL == P)
		puts("Element does not exist");
	else if (x < P->el)
		P->left = deleteEl(P->left, x);
	else if (x > P->el)
		P->right = deleteEl(P->right, x);
	else if (P->left != NULL && P->right != NULL) {
			temp = findMax(P->right);
			P->el = temp->el;
			P->right = deleteEl(P->right, P->el);
		}
		
	else {
			temp = P;
			if (NULL == P->left)
				P = P->right;
			else
				P = P->left;
			free(temp);
		}
	
	return P;
}