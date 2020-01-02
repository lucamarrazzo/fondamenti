#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CAR (20)

typedef char parola[MAX_CAR+1]; 




parola *leggi_file(FILE *infile, int n);
int conta_caratteri(char *parola, char *caratteri_da_conteggiare)
int palindromo(char *parola);
int conta_palindromi(parola *elenco, int n);
int lettera_da_filtrare(char carattere);
char *filtra_parola(char *parola);
void stampa_parole_filtrate_in_intervallo(parola *elenco, int a, int b);
void stampa_filtrate(parola *elenco, int n);


int main(int argc, const char *argv[]){
    
    FILE *infile;
    int n;
    parola *elenco;
        
    if (argc != 2)
        return 1;
        
    infile=fopen(argv[1],"r");




}



//funzione lettura file
parola *leggi_file(FILE *infile, int n){
     
     char buf[60];
     int dim=4;
     parola *elenco, *redim_elenco;
     (*n)=0;
     
     elenco=malloc(dim * sizeof(*elenco));
     if(elenco==NULL){
         (*n)=0;
         return NULL;
     }
     
     while(fgets(buf,sizeof(buf),infile)){
         sscanf(buf,"%s %s",elenco[(*n)], elenco[(*n)+1]);
         (*n)+=2;
         
         if((*n)>=dim){
             dim*=2;
             redim_elenco=realloc(elenco, dim * sizeof(*elenco));
             if(redim_elenco==NULL) return NULL;
             elenco=redim_elenco;
         }
     }
     elenco=realloc(elenco, (*n) * sizeof(*elenco));
     return elenco;
}


int conta_caratteri(char *parola, char* caratteri_da_conteggiare){
    
    int i,j,len,count=0;
    int num_caratteri=strlen(caratteri_da_conteggiare);
    
    len=strlen(parola);
    for(i=0;i<len;i++){
        for(j=0;j<num_caratteri;j++){
            if(parola[i]==caratteri da conteggiare[j])
            count++;
        }
    }
    return count;
}


int max_vocali(parola *elenco, int n){
    
    int i,num_voc, max=0;
    for(i=0;i<n;i++){
        num_voc=conta_caratteri(elenco[i],"aeiou");
        if (num_voc > max)
			max = num_voc;
    }
    return max;
}


int palindromo(char *parola){
    
    int i, len;
    
    len=strlen(parola);
    for(i=0;i<len/2;i++){
        if(parola[i]!=parola[len-i-1])
            return 0;
        
    }
    return 1;    
}


int conta_palindromi(parola *elenco,int n){
    int i, count=0;
    
    for(i=0;i<n;i++){
        if(palindromo(elenco[i]))
            count++;
    }
    return count;
}


int lettera_da_filtrare(char carattere){
    
    char lettere[]={"abcde"};
    int i;
    int len=sizeof(lettere-1);
    
    for(i=0;i<len;i++){
        if(carattere==lettere[i])
            return 1;
    }
    return 0;
}


char *filtra_parola(char *parola){
    
    char *parola_filtrata = malloc(MAX_CAR * sizeof(char));
	int i, len, indice_lettera = 0;

	len = strlen(parola);
	
	for(i=0;i<len;i++){
	    if(!lettera_da_filtrata(parola[i])){
	        parola_filtrata[indice_lettera]=parola[i];
	        indice_lettera++;
	    }
	}
	/* Aggiunta dello zero di terminazione finale */
	parola_filtrata[indice_lettera] = '\0';
	return parola_filtrata;
}


void stampa_parole_filtrate_in_intervallo(parola *elenco, int a, int b){
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


void stampa_filtrate(parola *elenco, int n){
	if (n <= 8) {
		/* Stampa tutte le parole */
		stampa_parole_filtrate_in_intervallo(elenco, 0, n);
	} else {
		/* Stampa le prime e le ultime 4 parole */
		stampa_parole_filtrate_in_intervallo(elenco, 0, 4);
		stampa_parole_filtrate_in_intervallo(elenco, n - 4, n);
	}
}









