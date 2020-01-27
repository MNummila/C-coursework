/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Mikko Nummila
 * Opiskelijanumero: 0506303
 * Päivämäärä: 3.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:-
 */
/*****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "nimilista.h"
#include "tuloslista.h"

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
		fprintf(tiedosto,"\n%s      %li      %d     %d  %d %d kB / %.0f%%",
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
	int nimipituus = 0;
	float koko = 0;
	float koko2 = 0;
	char datannimi[30];
	float vast = 0;
	float vast2 = 0;

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
		koko = koko + (sizeof(Nimet) - (30-nimipituus-1));
		koko2 = koko2 + sizeof(Nimet);
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
	ptrUusiT->keskiarvo = (KAlaskuri / laskuri);
	ptrUusiT->muistikB = koko2;
	vast = koko / koko2 * 100;
	vast2 = ceil(vast);
	ptrUusiT->muistipros = vast2;
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
	printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");
	printf("%s      %li      %d     %d  %d %d kB / %.0f%%\n", ptrUusiT->settinimi,
	ptrUusiT->nimimaara, ptrUusiT->minpituus, ptrUusiT->maxpituus, ptrUusiT->keskiarvo,
	ptrUusiT->muistikB / 1000, ptrUusiT->muistipros);
	return pAlku;
}

Tulokset *tyhjennaT(Tulokset *pA){
	Tulokset *ptr = pA;
	while (ptr != NULL){
		pA = ptr->pSeur;
		free(ptr);
		ptr = pA;
	}
	return pA;
}

void tulostentulostus(Tulokset *pA){
	int i = 0;
	Tulokset *ptr = pA;
	if (pA == NULL){
		printf("\n");
	}
	else{
		printf("Datasetti Nimiä MinPit MaxPit KA Muistinkäyttö\n");		
		while(ptr != NULL){
			printf("%s      %li      %d     %d  %d %d kB / %.0f%%\n",
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
