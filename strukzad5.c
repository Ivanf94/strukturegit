#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

typedef struct _Lista*Pozicija;
typedef struct _Lista {
	int el;
	Pozicija next;
}Lista;

int ucitajEl(char*,Pozicija);
int sortiraniUnos(Pozicija, Pozicija);
int ispis(Pozicija);
int unija(Pozicija, Pozicija, Pozicija);
int presjek(Pozicija, Pozicija, Pozicija);
Pozicija noviEl();

int main() {
	Lista Head1, Head2, Head3, Head4;
	Head1.next = Head2.next = Head3.next = Head4.next = NULL;
	ucitajEl("lista1.txt", &Head1);
	ucitajEl("lista2.txt", &Head2);
	ispis(Head1.next);
	ispis(Head2.next);
	unija(&Head3, &Head1, &Head2);
	ispis(Head3.next);
	presjek(&Head4, &Head1, &Head2);
	ispis(Head4.next);
	return 0;
}

Pozicija noviEl() {
	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(Lista));
	if (q == NULL) {
		puts("Memorija nije rezervirana");
		return NULL;
	}
	return q;
}

int ucitajEl(char*dat, Pozicija P) {
	FILE*fp = NULL;
	fp = fopen(dat, "r");
	if (!fp) {
		puts("Datoteka nije otvorena");
		return NULL;
	}

	while(!feof(fp)) {
		Pozicija q = NULL;
		q = noviEl();
		if (q == NULL)
			return NULL;

		fscanf(fp, "%d ", &(q->el));
		sortiraniUnos(P, q);
	}
	return 1;
}

int sortiraniUnos(Pozicija P, Pozicija q) {
	while (P->next != NULL && P->next->el < q->el)
		P = P->next;

		q->next = P->next;
		P->next = q;

	return 2;
}

int ispis(Pozicija P) {
	if (P == NULL) {
		puts("Lista je prazna");
		return NULL;
	}
	while (P != NULL) {
		printf("%d ", P->el);
		P = P->next;
	}
	printf("\n");
	return 3;
}

int unija(Pozicija P, Pozicija L1, Pozicija L2) {
	if (L1 == NULL && L2 == NULL) {
		puts("Liste su prazne");
		return NULL;
	}
	Pozicija q = NULL;
	L1 = L1->next;
	L2 = L2->next;

	while (L1 != NULL && L2 != NULL) {
		if (L1->el < L2->el) {
			q = noviEl();
			if (q == NULL)
				return NULL;
			q->el = L1->el;
			sortiraniUnos(P, q);
			L1 = L1->next;
		}
		else if (L1->el > L2->el) {
			q = noviEl();
			if (q == NULL)
				return NULL;
			q->el = L2->el;
			sortiraniUnos(P, q);
			L2 = L2->next;
		}
		else {
			q = noviEl();
			if (q == NULL)
				return NULL;
			q->el = L1->el;
			sortiraniUnos(P, q);
			L1 = L1->next;
			L2 = L2->next;
		}
	}

	if (L1 != NULL && L2 == NULL) {
		while (L1 != NULL) {
			q = noviEl();
			if (q == NULL)
				return NULL;
			q->el = L1->el;
			sortiraniUnos(P, q);
			L1 = L1->next;
		}
	}
	else {
		while (L2 != NULL) {
			q = noviEl();
			if (q == NULL)
				return NULL;
			q->el = L2->el;
			sortiraniUnos(P, q);
			L2 = L2->next;
		}
	}
	return 4;
}
int presjek(Pozicija P, Pozicija L1, Pozicija L2) {
	if (L1 == NULL && L2 == NULL) {
		puts("Liste su prazne");
		return NULL;
	}
	Pozicija q = NULL;
	L1 = L1->next;
	L2 = L2->next;

	while (L1 != NULL && L2 != NULL) {
		if (L1->el < L2->el)
			L1 = L1->next;

		else if (L1->el > L2->el)
			L2 = L2->next;

		else {
			q = noviEl();
			if (q == NULL)
				return NULL;
			q->el = L1->el;
			sortiraniUnos(P, q);
			L1 = L1->next;
			L2 = L2->next;
		}
	}
	return 5;
}

