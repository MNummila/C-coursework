/*****************************************************************************/
/* CT60A0220 C-ohjelmoinnin ja testauksen periaatteet 
 * Tekijä: Mikko Nummila
 * Opiskelijanumero: 0506303
 * Päivämäärä: 3.3.2018
 * Yhteistyö ja lähteet, nimi ja yhteistyön muoto:-
 */
/*****************************************************************************/

typedef struct nimia{
	char nimi[30];
	int maara;
	struct nimia *pNext;
	}Nimet;

Nimet *tyhjenna(Nimet *pA);
Nimet *tiedostonluku(Nimet *pA);
void tulostus(Nimet *pA);

/*****************************************************************************/
/* eof */
