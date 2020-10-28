#include<stdio.h>
#include<stdlib.h>


typedef struct {
	char ime[20];
	char prezime[30];
	int bodovi;
}student;

//funkcija koja prebrojava studente
int CountRows( char* dat) {

	int brstd = 0;
	char niz[100];

	FILE* fp = NULL;

	fp = fopen(dat, "r");
	if (fp ==NULL)
	{
		printf("Datoteka nije otvorena\n");
		return -1;
	}
	
	while(fgets(niz, sizeof(niz), fp) !=NULL)
			brstd++;


	fclose(fp);
	return brstd;
}

//funkcija za ispis podataka o studentima
int ispis(int n, student* st, char* dat){

	int i;
	char c='%';
	double relativan = 0.0;
	double maxbr = 100;
	FILE* fp=NULL;
	
	fp = fopen(dat, "r");
	if (fp ==NULL)
	{
		printf("Datoteka nije otvorena-ispis\n");
		return -2;
	}
	puts("Ime   Prezime   Apsolutni bodovi   Relativni bodovi");
	for (i = 0; i < n; i++) {
		fscanf( fp ,"%s %s %d", st[i].ime, st[i].prezime, &st[i].bodovi );

		relativan = st[i].bodovi / maxbr * 100;

		printf( "%s\t%s\t%d\t\t%f%c\n", st[i].ime, st[i].prezime, st[i].bodovi, relativan , c );
		relativan=0.0;
	}
	
	fclose(fp);
	return 1;
}

int main() {

	int n;
	
	student* st = NULL;
	
	n = CountRows("strukturepopis.txt");

	st = (student*)malloc(n * sizeof(student));

	ispis(n,st,"strukturepopis.txt");

	free(st);
	return 0;
}