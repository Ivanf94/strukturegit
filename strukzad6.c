#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct _Cvor* Pozicija;

typedef struct _Cvor {
	int el;
	Pozicija next;
}Cvor;

int pushStog(Pozicija,int);
Pozicija pushRed(Pozicija, Pozicija, int);
int pop(Pozicija);
int ispis(Pozicija);
int randbroj();

int main() {
	int min, max;
	int x, y;
	Pozicija Last = NULL;
	Cvor Stog, Red;
	Stog.next = NULL;
	Red.next = NULL;

	pushStog(&Stog, randbroj());
	pushStog(&Stog, randbroj());
	pushStog(&Stog, randbroj());
	ispis(Stog.next);
	x = pop(&Stog);
	printf("%d\n", x);
	ispis(Stog.next);

	Last = pushRed(&Red, Last, randbroj());
	Last = pushRed(&Red, Last, randbroj());
	Last = pushRed(&Red, Last, randbroj());
	ispis(Red.next);
	y = pop(&Red);
	y = pop(&Red);
	y = pop(&Red);
	printf("%d\n", y);
	ispis(Red.next);
	Last = pushRed(&Red, Last, randbroj());
	Last = pushRed(&Red, Last, randbroj());
	ispis(Red.next);

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
Pozicija pushRed(Pozicija P,Pozicija Last, int x) {
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Cvor));
	if (!q) {
		puts("Memorija nije rezervirana");
		return NULL;
	}

	if (P->next == NULL) {
		q->el = x;
		q->next = P->next;
		P->next = q;
		Last = q;
		return Last;
	}

	q->el = x;
	q->next = Last->next;
	Last->next = q;

	return q;
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

int randbroj() {
	int min, max;
	puts("Unesite min za random broj:");
	scanf("%d", &min);
	puts("Unesite max za random broj:");
	scanf("%d", &max);
	srand((unsigned)time(NULL));

	return (rand() % (max - min + 1)) + min;
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


 