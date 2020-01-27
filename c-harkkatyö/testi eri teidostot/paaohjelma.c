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
#include "nimilista.h"
#include "tuloslista.h"

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
				printf("Tuloslista tyhjennetty.\n");
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
/*****************************************************************************/
/* eof */
