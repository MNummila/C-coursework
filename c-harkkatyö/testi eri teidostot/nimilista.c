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

Nimet *tiedostonluku(Nimet *pA){
	char tiedostonimi[50];
	char rivi[50], *kohta1, *kohta2;
	int laskuri = 0;
	int luku;
	int kB;
	int kB2; 

	Nimet *ptrUusi, *ptr;

	printf("Anna luettavan tiedoston nimi: ");
	scanf("%s",&tiedostonimi);

	FILE* tiedosto;
	if((tiedosto = fopen(tiedostonimi,"r")) == NULL){
		perror("Tiedoston avaus epäonnistui.");
		exit(1);
	}
	if(pA != NULL){
		printf("Poistetaan aiemmat tiedot ja luetaan uudet.\n");
	}
	pA = tyhjenna(pA);
	printf("Luetaan tiedosto %s.\n",tiedostonimi);

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
	return pA;
}

void tulostus(Nimet *pA){
	int i = 0;
	Nimet *ptr = pA;
	if (pA == NULL){
		printf("\n");
	}
	else{
		while(ptr != NULL){
			printf("%s , %d\n",ptr->nimi, ptr->maara);
			ptr = ptr->pNext;
			i++;
		}
	printf("\n");
	}
}
/*****************************************************************************/
/* eof */
