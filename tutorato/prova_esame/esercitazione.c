#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CAR (20)    //massimo numero di caratteri per parola

typedef char parola[MAX_CAR+1];

/*PROTOTIPI DELLE FUNZIONI */
parola *leggi_file(FILE *f, int *n);
int max_vocali(parola *elenco, int n);
int conta_caratteri(char *parola, char *caratteri da conteggiare);

int main(int argc, const char *argv[])
{

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

int max_vocali(parola *elenco, int n){
    int i,num_voc,max=0;
    for(i=0;i<n;i++){
        num_voc=conta_caratteri(elenco[i],'aeiou');
        if(num_voc>max){
            max=num_voc;
        }
    }
}

int conta_caratteri(char *parola, char *caratteri_da_conteggiare){
    int i,j,len,count=0;
    int num_caratteri=strnlen(caratteri_da_conteggiare);
    
}