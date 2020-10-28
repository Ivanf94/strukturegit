#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200

struct _Osoba;
typedef struct _Osoba* Pozicija;
typedef struct _Osoba {
	int godinaRodenja;
	char ime[MAX];
	char prezime[MAX];
	Pozicija next;
}Osoba;

int unosP(Pozicija,Pozicija);
int ispis(Pozicija);
int unosK(Pozicija, Pozicija);
Pozicija trazi(Pozicija, char*);
Pozicija noviStudent(char*, char*, int);
int brisi(Pozicija, char*);
Pozicija traziPrethodni(Pozicija, char*);

int main(void) {
	char Ime[MAX] = { 0 };
	char Prezime[MAX] = { 0 };
	int god = 0;
	Osoba Head;
	Head.next = NULL;
	Pozicija tmp = NULL;
	char s;
	
	while (1) {
		puts("");
		puts("Za unos novog studenta na pocetak stisnite: a");
		puts("za unos na kraj stisnite b");
		puts("Za ispis: c");
		puts("Pronadi el. po prezimenu: d");
		puts("Brisi el.: e");
		puts("Kraj programa : f");
		scanf(" %c", &s);
		puts("");
		switch (s) {
		case 'a':
			puts("Unesite ime:");
				scanf(" %s", Ime);
			puts("Unesite prezime:");
				scanf(" %s", Prezime);
			puts("Unesite godinu rodenja:");
				scanf(" %d", &god);

			tmp = noviStudent(Ime, Prezime, god);
			unosP(&Head, tmp);
			break;
		case 'b':
			puts("Unesite ime:");
				scanf(" %s", Ime);
			puts("Unesite prezime:");
				scanf(" %s", Prezime);
			puts("Unesite godinu rodenja:");
				scanf(" %d", &god);
			tmp = noviStudent(Ime, Prezime, god);
			unosK(&Head, tmp);
			break;
		case 'c':
			puts("Ispis liste:");
			ispis(Head.next);
			break;
		case 'd':
			puts("Unesite prezime:\n");
				scanf(" %s", Prezime);
			printf("Element s prezimenom %s je na adresi %d\n",Prezime,trazi(Head.next, Prezime));
			break;
		case 'e':
			puts("Unesite prezime koje zelite izbrisati:\n");
				scanf(" %s", Prezime);
			brisi(&Head, Prezime);
			break;
		case 'f':
			return 0;
			break;
		}
	}
	
	return 0;
}

Pozicija noviStudent(char*Ime, char*Prezime, int god) {
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL)
		puts("GRESKA");

	strcpy(q->ime, Ime);
	strcpy(q->prezime, Prezime);
	q->godinaRodenja = god;

	return q;
}

int unosP(Pozicija P,Pozicija q){

	q->next = P->next;
	P->next = q;

	return 1;
}

int ispis(Pozicija P) {
	while (P != NULL) {
		printf("%s %s %d\n", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}
	return 2;
}

int unosK(Pozicija P, Pozicija q) {
	while (P->next != NULL)
		P = P->next;
	unosP(P, q);

	return 3;
}
Pozicija trazi(Pozicija P, char*Prezime) {
	while (P != NULL && strcmp(P->prezime, Prezime))
		P = P->next;
	if (P == NULL)
		puts("\nPrezime nije pronadeno.\n");
	return P;
}
Pozicija traziPrethodni(Pozicija P, char*Prezime) {
	while (P->next != NULL && strcmp(P->next->prezime, Prezime))
		P = P->next;
	if (P->next == NULL) {
		puts("\nPrezime nije pronadeno.\n");
		return NULL;
	}

	return P;
}

int brisi(Pozicija P, char* Prezime) {

	Pozicija q = NULL;

	P=traziPrethodni(P, Prezime);
	if (P == NULL)
		return 4;

	q = P->next;
	P->next= P->next->next;
	free(q);

	return 5;
}
