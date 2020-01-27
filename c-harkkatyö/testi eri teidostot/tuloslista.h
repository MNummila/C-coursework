/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Mikko Nummila
 * Opiskelijanumero: 0506303
 * Päivämäärä: 3.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:-
 */
/*****************************************************************************/

typedef struct tulokset{
	char settinimi[30];
	long nimimaara;
	int minpituus;
	int maxpituus;
	int keskiarvo;
	int muistikB;
	double muistipros;
	struct tulokset *pSeur;
	}Tulokset;

Tulokset *tuloslistanteko(Tulokset *pAlku, Nimet *pA);
void tulostentulostus(Tulokset *pA);
void tallennatiedostoon(Tulokset *pA);
Tulokset *tyhjennaT(Tulokset *pA);

/*****************************************************************************/
/* eof */
