#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR (20)   // Massimo numero di caratteri per ciascuna parola

// Tipo di dato per memorizzare una singola parola
typedef char parola[MAX_CAR + 1];

/*
 * Lettura del file.
 *
 * Anche se le parole sono due per riga, le si può leggere in
 * un vettore di singole parole, poiché tutte le richieste
 * prevedono di trattare le parole in sequenza,
 * indipendentemente dal fatto che siano due per riga.
 */
parola *leggi_file(FILE *f, int *n)
{
	int i = 0;
	int dim = 4;
	char buf[60];
	parola *elenco, *elenco_redim;

	elenco = malloc(dim * sizeof(*elenco));
	if (elenco == NULL) {
		(*n) = 0;
		return NULL;
	}
	while (fgets(buf, sizeof(buf), f) != NULL) {
		sscanf(buf, "%s %s", elenco[i], elenco[i + 1]);
		i += 2;    // incremento di 2 avendo letto 2 parole
		if (i >= dim) {
			dim *= 2;
			elenco_redim = realloc(elenco, dim * sizeof(*elenco));
			if (elenco_redim == NULL) {
				return NULL;
			}
			elenco = elenco_redim;
		}
	}
	(*n) = i;
	elenco = realloc(elenco, i * sizeof(*elenco));
	return elenco;
}

void stampa_parole(parola *elenco, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		puts(elenco[i]);
	}
}

/*
 * Conteggia i caratteri presenti all'interno della parola "parola" che
 * sono elencati nella stringa "caratteri_da_conteggiare".
 *
 * I caratteri che si desiderano conteggiare sono passati come stringa
 * di caratteri, in modo che il conteggio si possa facilmente
 * adattare all'insieme di caratteri desiderato semplicemente
 * modificando il contenuto del vettore al momento della chiamata
 * della funzione.
 */
int conta_caratteri(char *parola, char *caratteri_da_conteggiare)
{
	int i, j, len, count = 0;
	int num_caratteri = strlen(caratteri_da_conteggiare);

	len = strlen(parola);
	// il ciclo viene svolto per tutti i caratteri della stringa
	for (i = 0; i < len; i++) {
		// ogni carattere viene confrontato con ciascuno di quelli
		// contenuti nel vettore di caratteri da conteggiare
		for (j = 0; j < num_caratteri; j++) {
			if (parola[i] == caratteri_da_conteggiare[j])
				count++;
		}
	}
	return count;
}

/* Trova il numero massimo di vocali tra tutte le parole. */
int max_vocali(parola *elenco, int n)
{
	int i, num_voc, max = 0;
	for (i = 0; i < n; i++) {
		num_voc = conta_caratteri(elenco[i], "aeiou");
		if (num_voc > max)
			max = num_voc;
	}
	return max;
}

/*
 * Determina se la parola "parola" è palindroma o meno.
 *
 * Retiruisce 1 se è palindroma, oppure 0 se non lo è.
 */
int palindromo(char *parola)
{
	int i, len;

	len = strlen(parola);
	/* Il ciclo viene eseguito per un numero di caratteri pari
	 * alla metà della lunghezza della stringa. */
	for (i = 0; i < len / 2; i++) {
		/* L'i-esimo carattere viene confrontato con il
		 * corrispondente a partire dalla fine della stringa.
		 * Se sono diversi, la funzione termina restituendo
		 * FALSO (valore 0). */
		if (parola[i] != parola[len - i - 1])
			return 0;
	}
	return 1;
}

/* Conta il numero di parole palindrome nell'elenco. */
int conta_palindromi(parola *elenco, int n)
{
	int i, count = 0;

	for (i = 0; i < n; i++) {
		if (palindromo(elenco[i]))
			count++;
	}
	return count;
}

/* Restituisce 1 se il carattere è da filtrare, altrimenti 0. */
int lettera_da_filtrare(char carattere)
{
	char lettere[] = { "abcde" };
	int len = sizeof(lettere - 1);
	int i;

	for (i = 0; i < len; i++) {
		if (carattere == lettere[i])
			return 1;
	}
	return 0;
}

/* 
 * Restituisce la parola filtrata, dalla quale sono state rimosse
 * le lettere da filtrare.
 *
 * La stringa restituita viene allocata all'interno della funzione.
 * Il chiamante ha il compito di liberare la memoria.
 */
char *filtra_parola(char *parola)
{
	char *parola_filtrata = malloc(MAX_CAR * sizeof(char));
	int i, len, indice_lettera = 0;

	len = strlen(parola);
	for (i = 0; i < len; i++) {
		/* La lettera vine aggiunta solo se NON è da filtrare */
		if (!lettera_da_filtrare(parola[i])) {
			parola_filtrata[indice_lettera] = parola[i];
			indice_lettera++;
		}
	}
	/* Aggiunta dello zero di terminazione finale */
	parola_filtrata[indice_lettera] = '\0';
	return parola_filtrata;
}

/* 
 * Stampa le parole filtrate nell'intervallo [a, b).
 * Stampa solo se la parola ha lunghezza maggiore di zero.
 */
void stampa_parole_filtrate_in_intervallo(parola *elenco, int a, int b)
{
	char *p;
	int i;
	for (i = a; i < b; i++) {
		p = filtra_parola(elenco[i]);
		if (strlen(p) > 0) {
			puts(p);
			free(p);
		}
	}
}

/* 
 * Stampa le prime 4 e le ultime 4 parole filtrate.
 * Se le parole sono meno di 8 in totale, le stampa tutte.
 */
void stampa_filtrate(parola *elenco, int n)
{
	if (n <= 8) {
		/* Stampa tutte le parole */
		stampa_parole_filtrate_in_intervallo(elenco, 0, n);
	} else {
		/* Stampa le prime e le ultime 4 parole */
		stampa_parole_filtrate_in_intervallo(elenco, 0, 4);
		stampa_parole_filtrate_in_intervallo(elenco, n - 4, n);
	}
}

/* 
 * Determina se nell'elenco è presente un duplicato.
 *
 * Restituisce 1 in caso di presenza di duplicati, altrimenti 0.
 */
int duplicati_presenti(parola *elenco, int n)
{
	int i, j;

	/* Se ci sono 0 o 1 parole, non ci sono duplicati */
	if (n <= 1)
		return 0;
	/* Ciclo su tutte le parole dalla prima alla penultima */
	for (i = 0; i < n - 1; i++) {
		/* Ogni parola viene confrontata con tutte le successive */
		for (j = i + 1; j < n; j++) {
			if (strcmp(elenco[i], elenco[j]) == 0)
				/* Duplicato trovato: termina immediatamente */
				return 1;
		}
	}
	/* Se si arriva fino qui, non sono stati trovati duplicati */
	return 0;
}

/* 
 * Funzione di confronto tra stringhe.
 */
int cmp_parole(const void *p1, const void *p2)
{
	const char *u1 = p1;
	const char *u2 = p2;
	return strcmp(u1, u2);
}

int main(int argc, char *argv[])
{
	FILE *f;
	parola *elenco;
	int n;

	if (!(f = fopen(argv[1], "r"))) {
		puts("Uso: ./a.out file_di_dati");
		return 1;
	}
	elenco = leggi_file(f, &n);
	/* Numero massimo di vocali */
	printf("\n[MAX-VOCALI]\n%d\n", max_vocali(elenco, n));
	/* Nimero di palindromi */
	printf("\n[PALINDROMI]\n%d\n", conta_palindromi(elenco, n));
	/* Filtro dei caratteri */
	puts("\n[FILTRO]");
	stampa_filtrate(elenco, n);
	/* Duplicati */
	puts("\n[DUPLICATI]");
	if (duplicati_presenti(elenco, n))
		puts("SI");
	else
		puts("NO");
	/* Ordinamento */
	puts("\n[ORDINAMENTO]");
	qsort(elenco, n, sizeof(*elenco), cmp_parole);
	stampa_parole(elenco, n);

	free(elenco);
	fclose(f);

	return 0;
}
