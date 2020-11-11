#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _pol;
typedef struct _pol*Pozicija;

typedef struct _pol {
	int koef;
	int exp;
	Pozicija next;
}pol;


int Citaj(Pozicija,char*);					//cita elemente iz datoteke
int unosP(Pozicija, Pozicija);				//unosi elemente u listu
int Sortiraj(Pozicija,Pozicija);			//sortirano unosi elemente u listu
int Ispis(Pozicija);						//ispisuje elemente liste
int zbroji(Pozicija,Pozicija, Pozicija);	//zbraja elemente 2 polinoma
Pozicija Alociraj(void);					//stvara memoriju za novi clan
int Pridruzi(Pozicija, int,int);			//pridruzuje vrijednosti novom clanu(koeficijent i eksponent)
int mnozi(Pozicija, Pozicija, Pozicija);	//mnozi 2 polinoma

int main() {

	pol Head1 , Head2 , Head3, Head4;
	Head1.next = NULL;
	Head2.next = NULL;
	Head3.next = NULL;
	Head4.next = NULL;

	Citaj(&Head1,"pol1.txt");
	Citaj(&Head2,"pol2.txt");
	puts("Prvi polinom:");
	Ispis(Head1.next);
	puts("Drugi polinom:");
	Ispis(Head2.next);
	zbroji(Head1.next, Head2.next, &Head3);
	mnozi(Head1.next, Head2.next, &Head4);
	puts("Zbroj:");
	Ispis(Head3.next);
	puts("Umnozak:");
	Ispis(Head4.next);
	return 0;
}

Pozicija Alociraj(void) {

	Pozicija q = NULL;
	q = (Pozicija)malloc(sizeof(pol));
	if (!q) {
		puts("Nije stvorena memorija");
		return NULL;
	}

	return q;
}

int Citaj(Pozicija P,char*dat) {

	FILE* fp = NULL;
	fp = fopen(dat, "r");
	if (fp == NULL) {
		puts("Datoteka 1 nije otvorena");
		return -1;
	}

	Pozicija q = NULL;

	while (!feof(fp)) {

		q = Alociraj();

		fscanf(fp, "%d %d", &(q->koef), &(q->exp));
		Sortiraj(P, q);
	}

	fclose(fp);
	return 1;
}

int Sortiraj(Pozicija P,Pozicija q) {
	while (P->next != NULL && q->exp > P->next->exp)
		P = P->next;
	unosP(P, q);
	return 2;
}

int unosP(Pozicija P, Pozicija q) {

	q->next = P->next;
	P->next = q;

	return 3;
}

int Ispis(Pozicija P) {
	while (P != NULL) {
		printf(" %d", P->koef, P->exp);
		if (P->exp != 0)
			printf("*x^%d ", P->exp);
		P = P->next;
	}
	puts("");
	return 4;
}


int zbroji(Pozicija P1, Pozicija P2, Pozicija P) { //P je adresa "Head3" elementa
	Pozicija q = NULL;

	if(P1 == NULL && P2 == NULL) {
		puts("Polinomi su prazni");
		return -5;
	}

		while (P1 != NULL && P2 != NULL) {

			if (P1->exp < P2->exp) {
					q = Alociraj();
					Pridruzi(q, P1->koef, P1->exp);
					Sortiraj(P, q);
					P1 = P1->next;
			}

			else if (P1->exp > P2->exp) {
					q = Alociraj();
					Pridruzi(q, P2->koef, P2->exp);
					Sortiraj(P, q);
					P2 = P2->next;
			}

			else{
					if (P1->koef + P2->koef != 0) {
						q = Alociraj();
						Pridruzi(q, P1->koef + P2->koef, P1->exp);
						Sortiraj(P, q);
						P1 = P1->next;
						P2 = P2->next;
					}
					else {
						P1 = P1->next;
						P2 = P2->next;
					}
			}

		}

		if(P1 == NULL && P2 != NULL)
			while (P2 != NULL) {
				q = Alociraj();
				Pridruzi(q, P2->koef, P2->exp);
				Sortiraj(P, q);
				P2 = P2->next;
			}
		else if(P1 != NULL && P2 == NULL){
			while (P1 != NULL) {
				q = Alociraj();
				Pridruzi(q, P1->koef, P1->exp);
				Sortiraj(P, q);
				P1 = P1->next;
			}
		}
		return 5;
}

int mnozi(Pozicija P1, Pozicija P2, Pozicija P) {
	int brojac = 0;

	Pozicija temp = P, temp2 = P2;
	Pozicija q = NULL;

	if (P1 == NULL || P2 == NULL) {   
		puts("Umnozak je 0.");
		return -6;
	}

	while (P1 != NULL)
	{
		while (P2 != NULL) 
		{
			q = Alociraj();
			q->koef = P1->koef*P2->koef; //definiranje novog elementa 
			q->exp = P1->exp + P2->exp;

				if(P->next == NULL)      //prvi unos u listu P (Head4)
					unosP(P, q);
				else 
				{
					while (P->next != NULL) 
					{									//provjera - postoji li vec element u listi "Head4" s istim eksponentom kojeg smo opet definirali
						if (q->exp == P->next->exp) 
						{								//ako postoji pomocu petlje ga pronadi i zbroji im koeficijente(postojeceg i novonastalog)
							P->next->koef += q->koef;	
							brojac++;					//u slucaju ako pronade takve elemente brojac ce se povecati
						}
							P = P->next;			//setanje po listi
					}
					P = temp;					// P=temp vraca pokazivac na pocetak liste "Head4"
					if(brojac == 0)				//ako je brojac ostao jednak NULI znaci da nisu pronadeni takvi elementi, stoga, unesi novi element sortiranim unosom
						Sortiraj(P, q);
				}
			brojac = 0;						
			P2 = P2->next;				//pomakni drugi polinom za jedno mjesto (prvi polinom je na istom mjestu)
		}
		P2 = temp2;					//drugi polinom vrati na pocetak
		P1 = P1->next;				//prvi polinom pomakni za jedno mjesto
	}

	return 6;
}

int Pridruzi(Pozicija P, int x, int y) {
	P->koef = x;
	P->exp = y;
	return 7;
}
