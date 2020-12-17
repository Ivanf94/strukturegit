#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

typedef struct _Cvor* Pozicija;

typedef struct _Cvor {
	int el;
	Pozicija next;
}Cvor;

int pushStog(Pozicija, int);
int pop(Pozicija);
int ispis(Pozicija);
int citaj(char*, Pozicija);

int main() {
	int min, max;
	int x, y;
	Pozicija Last = NULL;
	Cvor Stog, Red;
	Stog.next = NULL;
	Red.next = NULL;

	citaj("postfix.txt", &Stog);
	ispis(Stog.next);
	return 0;
}

int pushStog(Pozicija P, int x) {
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Cvor));
	if (!q) {
		puts("Memorija nije rezervirana");
		return NULL;
	}
	q->el = x;
	q->next = P->next;
	P->next = q;

	return 1;
}

int ispis(Pozicija P) {
	if (NULL == P) {
		puts("Lista je prazna");
		return NULL;
	}
	while (P != NULL) {
		printf("%d ", P->el);
		P = P->next;
	}
	puts("");

	return 2;
}

int pop(Pozicija P) {
	if (NULL == P->next) {
		puts("Prazna lista-pop");
		return NULL;
	}
	int x = 0;
	Pozicija temp = P->next;
	x = temp->el;

	P->next = temp->next;

	free(temp);
	return x;
}

int citaj(char*dat, Pozicija P) {

	FILE *fp = NULL;

	fp = fopen(dat, "r");
	if (!fp) {
		puts("Datoteka nije otvorena");
		return NULL;
	}

	char*buffer = NULL;
	int val = 0;
	int broj = 0;
	int counter = 0;
	int x = 0, y = 0;
	char c = '0';

	buffer = (char*)malloc(1000 * sizeof(char));
	if (!buffer) {
		puts("Memorija nije rezervirana");
		return NULL;
	}

	fgets(buffer, 1000, fp);

	while (*buffer != '\0') {

		val = sscanf(buffer, " %d%n", &broj, &counter);
		if (val == 1)
			pushStog(P, broj);
		else {
			val = sscanf(buffer, " %c%n", &c, &counter);
			y = pop(P);
			x = pop(P);

			switch (c) {
			case'+': pushStog(P, x + y);
				break;
			case'-': pushStog(P, x - y);
				break;
			case'*': pushStog(P, x * y);
				break;
			case'/': pushStog(P, x / y);
				break;
			default:
				break;
			}
		}

		buffer += counter;
	}

	return 3;
}