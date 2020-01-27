/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Mikko Nummila
 * Opiskelijanumero: 0506303
 * Päivämäärä: 26.2.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:-
 */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct nimia{
	char nimi[30];
	long maara;
	struct nimia *pNext;
	}Nimet;

typedef struct tulokset{
	char settinimi[30];
	long nimimaara;
	int minpituus;
	int maxpituus;
	int keskiarvo;
	int muistikB;
	int muistipros;
	struct tulokset *pSeur;
	}Tulokset;

Nimet *tyhjenna(Nimet *pA);
Nimet *tiedostonluku(Nimet *pA);
void tulostus(Nimet *pA);
Tulokset *tuloslistanteko(Tulokset *pAlku, Nimet *pA);
void tulostentulostus(Tulokset *pA);
void tallennatiedostoon(Tulokset *pA);
Tulokset *tyhjennaT(Tulokset *pA);

void tallennatiedostoon(Tulokset *pA){
	char tiedostonnimi[50];
	Tulokset *ptr = pA;
	FILE* tiedosto;
	printf("Anna tallennettavan tulostiedoston nimi: ");
	scanf("%s",&tiedostonnimi);
	if((tiedosto = fopen(tiedostonnimi,"w")) == NULL){
		perror("Tiedoston avaus epäonnistui.");
		exit(1);
	}
	fprintf(tiedosto,"Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö");
	while(ptr != NULL){
		fprintf(tiedosto,"\n%s      %li      %d     %d  %d %d kb / %d",
			ptr->settinimi,ptr->nimimaara,ptr->minpituus,
			ptr->maxpituus,ptr->keskiarvo,ptr->muistikB / 1000,ptr->muistipros);
		ptr = ptr->pSeur;
	}
	printf("Tiedosto tallennettu.\n");
	fclose(tiedosto);
}


Tulokset *tuloslistaan(Tulokset *pAlku, Nimet *pA){
	int laskuri = 0;
	int KAlaskuri = 0;
	int minimi = 100;
	int maksimi = 0;
	int nimipituus;
	int koko = 0;
	int koko2 = 0;
	char datannimi[30];
	char testi[30] = "                             ";
	Tulokset *ptrUusiT, *ptrT;
	Nimet *ptrN;

	printf("Anna analysoitavalle datasetille nimi: ");
	scanf("%s",&datannimi);
	printf("Analysoidaan listassa olevat tiedot.\n");
	/*ANALYSOINTI*/
	ptrN = pA;
	while(ptrN != NULL){
		laskuri++;
		nimipituus = strlen(ptrN->nimi);
		KAlaskuri = KAlaskuri + nimipituus;
		if(minimi > nimipituus){
			minimi = nimipituus;
		}
		if(maksimi < nimipituus){
			maksimi = nimipituus;
		}
/*		koko = koko + (sizeof(testi) - sizeof(ptrN->nimi));
*/		koko2 = koko2 + sizeof(Nimet);
		ptrN = ptrN->pNext;
	}
		/*MUISTIN VARAUS*/
	if ((ptrUusiT=(Tulokset*)malloc(sizeof(Tulokset))) == NULL){
		perror("Muistin varaus epäonnistui.\n");
		exit(0);
	}
		/*TIETOJEN LISÄYS*/
	strcpy(ptrUusiT->settinimi,datannimi);
	ptrUusiT->nimimaara = laskuri;
	ptrUusiT->minpituus = minimi;
	ptrUusiT->maxpituus = maksimi;
	ptrUusiT->keskiarvo = round(KAlaskuri / laskuri);
	ptrUusiT->muistikB = koko2;
	ptrUusiT->muistipros = round(koko / koko2 * 100);
	ptrUusiT->pSeur = NULL;
		/*LISTAAN LISÄYS*/
	if(pAlku == NULL){
		pAlku = ptrUusiT;
	}
	else{
		ptrT = pAlku;
		while(ptrT->pSeur != NULL){
			ptrT = ptrT->pSeur;
		}
		ptrT->pSeur = ptrUusiT;
	}
/*	printf("testikoko %d  ,  prosentti %d\n",sizeof(testi),sizeof(ptrUusiT->settinimi));
*/	printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	printf("%s      %li      %d     %d  %d %d kb / %d\n", ptrUusiT->settinimi,
	ptrUusiT->nimimaara, ptrUusiT->minpituus, ptrUusiT->maxpituus, ptrUusiT->keskiarvo,
	ptrUusiT->muistikB / 1000, ptrUusiT->muistipros);
	return pAlku;
}

Nimet *tiedostonluku(Nimet *pA){
	char tiedostonimi[50];
	char rivi[50], *kohta1, *kohta2;
	int laskuri = 0;
	int luku;
	int kB;
	int kB2;

	Nimet *ptrUusi, *ptr;

	printf("Anna luettavan tiedoston nimi; ");
	scanf("%s",&tiedostonimi);
	printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
	pA = tyhjenna(pA);
	printf("Luetaan tiedosto %s.\n",tiedostonimi);
	FILE* tiedosto;
	if((tiedosto = fopen(tiedostonimi,"r")) == NULL){
		perror("Tiedoston avaus epäonnistui.");
		exit(1);
	}
	while(fgets(rivi, 50, tiedosto) != NULL){
		laskuri++;
		/*MUISTIN VARAUS*/
		if ((ptrUusi=(Nimet*)malloc(sizeof(Nimet))) == NULL){
			perror("Muistin varaus epäonnistui.\n");
			exit(0);
		}
		/*TIETOJEN LISÄYS*/
		kohta1 = strtok(rivi, ";");
		kohta2 = strtok(NULL, "\n");

		strcpy(ptrUusi->nimi, kohta1);
		luku = atoi(kohta2);
		ptrUusi->maara = luku;

		ptrUusi->pNext = NULL;
		/*LISTAAN LISÄYS*/
		if(pA == NULL){
			pA = ptrUusi;
		}
		else{
			ptr = pA;
			while(ptr->pNext != NULL){
				ptr = ptr->pNext;
			}
			ptr->pNext = ptrUusi;
		}
	}
	/*POISTETAAN TURHA 1. RIVI*/
	ptr = pA;
	pA = pA->pNext;
	free(ptr);
	laskuri--;

	printf("Tiedosto %s luettu, %d nimiriviä.\n", tiedostonimi, laskuri);
	fclose(tiedosto);
	return pA;
}

Nimet *tyhjenna(Nimet *pA){
	Nimet *ptr = pA;
	while (ptr != NULL){
		pA = ptr->pNext;
		free(ptr);
		ptr = pA;
	}
	/*printf("Muisti vapautettu.\n");*/
	return pA;
}

Tulokset *tyhjennaT(Tulokset *pA){
	Tulokset *ptr = pA;
	while (ptr != NULL){
		pA = ptr->pSeur;
		free(ptr);
		ptr = pA;
	}
	/*printf("Muisti vapautettu.\n");*/
	return pA;
}

int main(void){
	int valinta = 1;
	Nimet *pA = NULL;
	Tulokset *pAlku = NULL;

	printf("Tämä ohjelma tutkii nimitietoja sisältäviä tiedostoja.\n");
	while(valinta != 0){
		printf("1) Lue nimitiedosto\n");
		printf("2) Tulosta listassa olevat tiedot\n");
		printf("3) Analysoi tiedot\n");
		printf("4) Tulosta kaikki tulostiedot\n");
		printf("5) Tallenna kaikki tulostiedot tiedostoon\n");
		printf("6) Tyhjennä tuloslista\n");
		printf("0) Lopeta\n");
		printf("Anna valintasi: ");
		scanf("%d",&valinta);
		switch(valinta){
			case 1:
				pA = tiedostonluku(pA);
				break;
			case 2:
				tulostus(pA);
				break;
			case 3:
				pAlku = tuloslistaan(pAlku,pA);
				break;
			case 4:
				tulostentulostus(pAlku);
				break;
			case 5:
				tallennatiedostoon(pAlku);
				break;
			case 6:
				pAlku = tyhjennaT(pAlku);
				break;
			case 0:
				break;
		}
	}
	printf("Kiitos ohjelman käytöstä.\n");
	tyhjenna(pA);
	tyhjennaT(pAlku);
	return(0);
}

void tulostus(Nimet *pA){
	int i = 0;
	Nimet *ptr = pA;
	if (pA == NULL){
		/*printf("Lista on tyhjä.\n");*/
		printf("\n");
	}
	else{
		/*printf("Listassa on seuraavat luvut: ");*/
		while(ptr != NULL){
			printf("%s , %li\n",ptr->nimi, ptr->maara);
			ptr = ptr->pNext;
			i++;
		}
	printf("\n");
	}
}

void tulostentulostus(Tulokset *pA){
	int i = 0;
	Tulokset *ptr = pA;
	if (pA == NULL){
		/*printf("Lista on tyhjä.\n");*/
		printf("\n");
	}
	else{
		/*printf("Listassa on seuraavat luvut: ");*/
		while(ptr != NULL){
			printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
			printf("%s      %li      %d     %d  %d %d kb / %d\n",
			ptr->settinimi,ptr->nimimaara,ptr->minpituus,
			ptr->maxpituus,ptr->keskiarvo,ptr->muistikB / 1000,ptr->muistipros);

			ptr = ptr->pSeur;
			i++;
		}
	printf("\n");
	}
}
/*****************************************************************************/
/* eof */

