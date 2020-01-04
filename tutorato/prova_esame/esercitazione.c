#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR (20)    //massimo numero di caratteri per parola

typedef char parola[MAX_CAR+1];

/*PROTOTIPI DELLE FUNZIONI */
parola *leggi_file(FILE *f, int *n);
int max_vocali(parola *elenco, int n);
int conta_caratteri(char *parola, char *caratteri_da_conteggiare);
void stampa_parole(parola *elenco, int n);
int palindromo(char *parola);
int conta_palindromi(parola *elenco,int n);
int lettera_da_filtrare(char carattere);
char *filtra_parola(char *parola);
void stampa_parole_filtrate_in_intervallo(parola *elenco, int a, int b);
void stampa_filtrate(parola *elenco, int n);
int duplicati_presenti(parola *elenco, int n);

int main(int argc, const char *argv[])
{
    FILE *f;
    int n;
    parola *elenco;

    f=fopen(argv[1],"r");
    if (argc != 2)
        return 1;
    if (f == NULL) {
        fprintf(stderr, "# Errore apertura file\n");
        return 1;
    }

    elenco=leggi_file(f,&n);
    printf("\n [STAMPA-PAROLE] \n");
    stampa_parole(elenco, n);
    printf("\n [MAX-VOCALI] %d \n", max_vocali(elenco, n));
    printf("\n [PALINDROMI] %d \n", conta_palindromi(elenco, n));
    puts("\n[FILTRO]");
	stampa_filtrate(elenco, n);
    puts("\n[DUPLICATI]");
	if (duplicati_presenti(elenco, n))
		puts("SI");
	else
		puts("NO");
}


/*FUNZIONE DI LETTURA FILE */
parola *leggi_file(FILE *f, int *n){
    char buf[60];
    int dim=4;
    parola *elenco,*redim_elenco;

    (*n)=0;
    elenco=malloc(dim * sizeof(*elenco));
    if(elenco==NULL){
        (*n)=0;
        return NULL;
    }
    while(fgets(buf,sizeof(buf),f)){
        sscanf(buf,"%s %s", elenco[(*n)], elenco[(*n)+1]);
        (*n)+=2;
        if((*n)>=dim){
            dim*=2;
            redim_elenco=realloc(elenco, dim * sizeof(*elenco));
            if(redim_elenco==NULL)return NULL;
            elenco=redim_elenco;
        }

    }
    elenco=realloc(elenco, (*n) * sizeof(*elenco));
    return elenco;
}

void stampa_parole(parola *elenco, int n){
	int i;
	for (i = 0; i < n; i++) {
		puts(elenco[i]);
	}
}

/*FUNZIONE MAX VOCALI */
int max_vocali(parola *elenco, int n){
    int i,num_voc,max=0;
    for(i=0;i<n;i++){
        num_voc=conta_caratteri(elenco[i],"aeiou");
        if(num_voc>max){
            max=num_voc;
        }
    }
    return max;
}
/*FUNZIONE CHE CONTA IL NUMERO DI CARATTERI SPECIFICATI DA *CARATTERI DA CONTEGGIARE */
int conta_caratteri(char *parola, char *caratteri_da_conteggiare){
    int i,j,len,count=0;
    int num_caratteri=strlen(caratteri_da_conteggiare);

    len=strlen(parola);
    for(i=0;i<len;i++){
        for(j=0;j<num_caratteri;j++){
            if(parola[i]==caratteri_da_conteggiare[j])
            count++;
        }
    }
    return count;
}

int palindromo(char *parola){
    int i,len;
    len=strlen(parola);
    for(i=0;i<len/2;i++){
        if(parola[i]!=parola[len-i-1])
            return 0;
    }
    return 1;
}

int conta_palindromi(parola *elenco, int n){
    int i,count=0;
    for(i=0;i<n;i++){
        if(palindromo(elenco[i])){
            count++;
        }
    }
    return count;
}

int lettera_da_filtrare(char carattere){

    char lettere[] = {"abcde"};
    int i;
    int len=sizeof(lettere-1);

    for(i=0;i<len;i++){
        if(carattere==lettere[i])
        return 1;
    }
    return 0;

}

char *filtra_parola(char *parola){

    char *parola_filtrata=malloc(MAX_CAR * sizeof(char));
    int i,len,indice_lettera=0;

    len=strlen(parola);

    for(i=0;i<len;i++){
        if(!lettera_da_filtrare(parola[i])){
            parola_filtrata[indice_lettera]=parola[i];
            indice_lettera++;
        }
    }
    parola_filtrata[indice_lettera]='\0';
    return parola_filtrata;
}

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

int duplicati_presenti(parola *elenco, int n){
    int i,j;

    if(n<=1){
        return 1;
    }
    for(i=0;i<n-1;i++){
        for(j=i+1;j<n;j++){
            if(strcmp(elenco[i],elenco[j])==0){
                return 1;
            }
        }
    }
    return 0;
}