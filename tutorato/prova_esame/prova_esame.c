#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CAR (20)    //massimo numero di caratteri per parola

typedef char parola[MAX_CAR+1];



parola *leggi_file(FILE *f,int *n);
void stampa_parole(parola *elenco, int n);
int conta_caratteri(char *parola, char *caratteri_da_conteggiare);
int max_vocali(parola *elenco , int n);
int palindromo(char *parola);
int conta_palindromi(parola *elenco, int n);



int main(int argc,const char *argv[])
{
    FILE *infile;
    int n;
    parola *elenco;
    
    infile=fopen(argv[1],"r");
    
    if (argc != 2)
        return 1;
    if (infile == NULL) {
        fprintf(stderr, "# Errore apertura file\n");
        return 1;
    }
    
    elenco=leggi_file(infile,&n);
    /* Numero massimo di vocali */
	printf("\n[MAX-VOCALI]\n%d\n", max_vocali(elenco, n));
	/* Nimero di palindromi */
	printf("\n[PALINDROMI]\n%d\n", conta_palindromi(elenco, n));
    
    
    
    
    fclose(infile);
    
}

parola *leggi_file(FILE *f,int *n){
    
    /* dichiarazione variabili per lettura da file(buf),
    dimensione iniziale vettore(dim),
    puntatori a parola per riallocare il vettore elenco*/
    char buf[60];
    int dim=4;
    parola *elenco,*redim_elenco;    
    (*n)=0;
    /*allocazione in memoria di elenco*/
    elenco=malloc(dim * sizeof(*elenco));            
    if (elenco == NULL) {
		(*n) = 0;
		return NULL;
		}
		
		
    while(fgets(buf,sizeof(buf),f)){
        
        sscanf(buf,"%s %s",elenco[(*n)] ,elenco[(*n)+1] );
       (*n)+=2;
        
        /*controllo se il contatore *n ha superato dim, se si aumento la dimensione di dim */
        if((*n)>=dim){
            dim*=2;
            /*rialloco la dimensione di redim_elenco*/
            redim_elenco=realloc(elenco, dim * sizeof(*elenco));
            if(redim_elenco==NULL)return NULL;
            elenco=redim_elenco;
            
        }        
    }
    
    elenco=realloc(elenco, (*n) * sizeof(*elenco));
    return elenco;    
}


void stampa_parole(parola *elenco, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		puts(elenco[i]);
	}
}


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

int max_vocali(parola *elenco , int n){
    int i,num_voc,max=0;
    for (i = 0; i < n; i++) {
		num_voc = conta_caratteri(elenco[i], "aeiou");
		if (num_voc > max)
			max = num_voc;
	}
	return max;
    
    
}

int palindromo(char *parola){
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

int conta_palindromi(parola *elenco, int n)
{
	int i, count = 0;

	for (i = 0; i < n; i++) {
		if (palindromo(elenco[i]))
			count++;
	}
	return count;
}