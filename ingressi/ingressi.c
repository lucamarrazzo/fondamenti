#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct data{
    int giorno, mese, anno;
};

struct ingresso{
    struct data data;
    int nbadge;
    int permanenza;
    int prezzo;

};

int durata(h1, m1, h2, m2){
    int min1=(h1*60)+m1;
    int min2=(h2*60)+m2;
    return min2-min1;
}

int calcola_tariffa(int tempo);

struct ingresso *leggi_file(FILE *f,int *n){
    int h1, m1, h2, m2;
    char buf[1000];
    struct ingresso *elenco,*redim_elenco;
    int dim=4;

    (*n)=0;
    elenco=malloc(dim * sizeof(*elenco));
    if(elenco==NULL)return NULL;

    while(fgets(buf,sizeof(buf),f)){
        sscanf(buf,"\n %d/%d/%d %d %d:%d %d:%d",
        &elenco[*n].data.giorno, &elenco[*n].data.mese, &elenco[*n].data.anno,
        &elenco[*n].nbadge,&h1,&m1,&h2,&m2);

        elenco[*n].permanenza=durata(h1, m1, h2, m2);
        (*n)++;

        if((*n)>=dim){
            dim*=2;
            redim_elenco=realloc(elenco,dim * sizeof(*elenco));
            if(redim_elenco==NULL)return NULL;
            elenco=redim_elenco;
        }
    }


}


int main(int argc,const char *argv[]){

}