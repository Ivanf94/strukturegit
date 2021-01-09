#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 256

struct _tree;
typedef struct _tree *Position;
typedef struct _tree {
	char name[MAX];
	Position sibling;
	Position child;
	Position parent;
}tree;

Position DosSelection(Position current, char*command, Position Root);
Position makeDir(Position current, char*name);
Position createDir(char*name);
Position findDir(Position current, char*name);
int printDir(Position current);
Position changeDir(Position, char*);
Position backDir(Position);
void deleteTree(Position);

int main() {
	char command[10] = {0};
	Position current = NULL;
	tree Root;
	Root.child = NULL;
	Root.sibling = NULL;
	Root.parent = NULL;
	current = &Root;
	puts("Root name:");
	scanf("%[^\n]s", Root.name);
	getchar();
	while (NULL != current) {
		puts("Unesite naredbu:");
		scanf("%[^\n]s", command);

		current = DosSelection(current, command, &Root);
	}

	return 0;
}

Position DosSelection(Position current, char*command, Position Root) {
	char name[MAX] = { 0 };
	if (strcmp(command, "md") == 0) {
	getchar();
		puts("Unesite ime direktorija:");
		scanf("%[^\n]s", name);

		current = makeDir(current, name);
	
	}
	else if (strcmp(command, "dir") == 0) {
		printDir(current);
		
	}
	else if (strcmp(command, "cd") == 0) {
		getchar();
		puts("Unesite ime direktorija:");
		scanf("%[^\n]s", name);
		current = changeDir(current, name);
		

	}
	else if (strcmp(command, "cd..") == 0) {
		current = backDir(current);
		

	}
	else if (strcmp(command, "exit") == 0) {
		puts("Direktorij izbrisan");
		deleteTree(current->child);
		return NULL;
	}
	getchar();
		return current;
}

Position createDir(char*name) {
	Position dir = NULL;

	dir = (Position)malloc(sizeof(tree));
	if (!dir) {
		puts("Allocation failed");
		return NULL;
	}

	strcpy(dir->name, name);
	dir->child = NULL;
	dir->parent = NULL;
	dir->sibling = NULL;

	return dir;
}

Position makeDir(Position current, char*name) {
	Position temp = NULL;
	Position child = NULL;
	Position above = current;

	if (findDir(current, name) != NULL) {
		puts("Direktorij s postojecim nazivom");
		return current;
	}

	temp = createDir(name);
	if (NULL == temp)
		return current; 

	child = current->child;
	if (NULL == child) {
		child = temp;
		child->parent = above;
		current->child = child;
		return current;
	}

	while (child->sibling != NULL && strcmp(child->sibling->name, name) < 0)
		child = child->sibling;

	temp->sibling = child->sibling;
	temp->parent = above;
	child->sibling = temp;
	return current;
}

Position findDir(Position current, char*name) {
	Position child = current->child;

	if (NULL == child) {
		return NULL;
	}

	while (child != NULL && strcmp(child->name, name) != 0)
		child = child->sibling;

	return child;
}
int printDir(Position current) {
	Position child = current->child;
	if (NULL == child) {
		puts("Direktorij je prazan");
		return NULL;
	}
	while (child != NULL) {
		printf("%s\n", child->name);
		child = child->sibling;
	}
	return 1;
}

Position changeDir(Position current, char*name) {
	
	if (NULL == findDir(current, name))
		return current;

	else
		current = findDir(current, name);
	return current;
}

Position backDir(Position current) {
	if (current->parent == NULL) {
		puts("Trenutni direktorij nema prethodnih direktorija");
		return current;
	}

	return current->parent;
}

void deleteTree(Position current) {
	if (NULL == current)
		return;
	deleteTree(current->sibling);
	deleteTree(current->child);
	free(current);
}