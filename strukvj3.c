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

int unosP(Pozicija, Pozicija);
int ispis(Pozicija);
int unosK(Pozicija, Pozicija);
Pozicija trazi(Pozicija, char*);
Pozicija noviStudent(void);
int brisi(Pozicija, char*);
Pozicija traziPrethodni(Pozicija, char*);
int dodajIza(Pozicija, Pozicija, char*);
int dodajIspred(Pozicija, Pozicija, char*);
int sortiraniUnos(Pozicija);
int upisLista(Pozicija);
int citajLista(void);
int main(void) {
	
	char traziPrezime[MAX] = { 0 };
	Osoba Head;
	Head.next = NULL;
	Pozicija tmp = NULL;
	char s;

	while (1) {
		puts("");
		puts("Za unos novog studenta na pocetak stisnite: a");
		puts("za unos na kraj stisnite b:");
		puts("Za ispis: c");
		puts("Pronadi el. po prezimenu: d");
		puts("Brisi el.: e");
		puts("Za unos iza nekog el.: f");
		puts("Za unos ispred nekog el.: g");
		puts("Za sortirani unos: h");
		puts("Za upis u datoteku: i");
		puts("Za iscitavanje datoteke: j");
		puts("Kraj programa : k");
		scanf(" %c", &s);
		puts("");
		switch (s) {
		case 'a':
			tmp = noviStudent();
			unosP(&Head, tmp);
			break;
		case 'b':
			tmp = noviStudent();
			unosK(&Head, tmp);
			break;
		case 'c':
			puts("Ispis liste:");
			ispis(Head.next);
			break;
		case 'd':
			puts("Unesite prezime:\n");
			scanf(" %s", traziPrezime);
			printf("Element s prezimenom %s je na adresi %d\n", traziPrezime, trazi(Head.next, traziPrezime));
			break;
		case 'e':
			puts("Unesite prezime koje zelite izbrisati:\n");
			scanf(" %s", traziPrezime);
			brisi(&Head, traziPrezime);
			break;
		case 'f':
			printf("Iza kojeg elementa zelite unijeti ovaj element? Unesite prezime:");
			scanf(" %s", &traziPrezime);
			tmp = noviStudent();
			dodajIza(&Head, tmp, traziPrezime);
			break;
		case 'g':
			printf("Ispred kojeg elementa zelite unijeti ovaj element? Unesite prezime:");
			scanf(" %s", &traziPrezime);
			tmp = noviStudent();
			dodajIspred(&Head, tmp, traziPrezime);
			break;
		case 'h':
			puts("Pozvan je sortirani unos:");
				sortiraniUnos(&Head);
			break;
		case 'i':
			puts("Pozvan je upis u datoteku:");
			upisLista(Head.next);
			break;
		case 'j':
			puts("Pozvan je ispis datoteke:");
			citajLista();
			break;
		case 'k':
			return 0;
			break;
		}
	}

	return 0;
}

Pozicija noviStudent(void) {
	Pozicija q = NULL;

	q = (Pozicija)malloc(sizeof(Osoba));
	if (q == NULL) {
		puts("GRESKA");
		return NULL;
	}

	puts("Unesite ime:");
	scanf(" %s", q->ime);
	puts("Unesite prezime:");
	scanf(" %s", q->prezime);
	puts("Unesite godinu rodenja:");
	scanf(" %d", &(q->godinaRodenja));

	return q;
}

int unosP(Pozicija P, Pozicija q) {

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
	while (P != NULL && strcmp(P->prezime, Prezime) != 0)
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

	P = traziPrethodni(P, Prezime);
	if (P == NULL)
		return -5;

	q = P->next;
	P->next = P->next->next;
	free(q);

	return 5;
}

int dodajIza(Pozicija P, Pozicija q, char* traziPrezime) {

	P = trazi(P, traziPrezime);
	if (P == NULL)
		return -6;

	unosP(P, q);

	return 6;
}

int dodajIspred(Pozicija P, Pozicija q, char* traziPrezime) {

	P = traziPrethodni(P, traziPrezime);
	if (P == NULL)
		return -7;
		
	unosP(P, q);

	return 7;
}

int sortiraniUnos(Pozicija P) {

	Pozicija q = NULL;

	q = noviStudent();
	if (q == NULL) {
		puts("Nije rezervirana memorija.");
			return -8;
	}
	while (P->next != NULL && strcmp(q->prezime, P->next->prezime) > 0)
		P = P->next;

	unosP(P, q);

	return 8;
}

int upisLista(Pozicija P) {
	FILE* fp = NULL;

	fp = fopen("lista.txt", "w");
	if (!fp) {
		puts("Lista nije otvorena");
		return -9;
	}

	while (P != NULL)
	{
		fprintf(fp, "%s\t%s\t%d\n", P->ime, P->prezime, P->godinaRodenja);
		P = P->next;
	}

	fclose(fp);
	return 9;
}

int citajLista(void) {

	FILE* fp2 = NULL;
	char str[200] = { 0 };

	fp2 = fopen("lista.txt", "r");
		if(fp2 == NULL){
			puts("Lista nije pronadena.");
			return -10;
		}
			
		while (fgets(str, sizeof(str), fp2) != NULL)
			printf("%s\n", str);

		fclose(fp2);
	return 10;
}