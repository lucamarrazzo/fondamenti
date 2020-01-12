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
    double prezzo;

};

int durata(h1, m1, h2, m2){
    int min1=(h1*60)+m1;
    int min2=(h2*60)+m2;
    return min2-min1;
}

double calcola_tariffa(int tempo){

    if(tempo<=20)return 3.5;
    if(tempo<=30)return 4.0;
    if(tempo<=45)return 4.5;
    if(tempo<=60)return 5.5;
    return 7.0;
}

struct ingresso *leggi_file(FILE *f,int *n){
    int h1, m1, h2, m2;
    char buf[1000];
    struct ingresso *elenco,*redim_elenco;
    int dim=8;

    (*n)=0;
    elenco=malloc(dim * sizeof(*elenco));
    if(elenco==NULL)return NULL;

    while(fgets(buf,sizeof(buf),f)){
        sscanf(buf,"\n %d/%d/%d %d %d:%d %d:%d",
        &elenco[*n].data.giorno, &elenco[*n].data.mese, &elenco[*n].data.anno,
        &elenco[*n].nbadge,&h1,&m1,&h2,&m2);

        elenco[*n].permanenza=durata(h1, m1, h2, m2);
        elenco[*n].prezzo=calcola_tariffa(elenco[*n].permanenza);
        (*n)++;

        if((*n)>=dim){
            dim*=2;
            redim_elenco=realloc(elenco,dim * sizeof(*elenco));
            if(redim_elenco==NULL)return NULL;
            elenco=redim_elenco;
        }
    }
    elenco=realloc(elenco, (*n) * sizeof(*elenco));
    return elenco;

}

void stampa_ultimi_inverso(struct ingresso *elenco, int n, int n_da_stampare){
    int i;

    if(n<n_da_stampare){
        n_da_stampare=n;
    }
    for(i=0;i<n_da_stampare;i++){
        printf("%d\n",elenco[n-i-1].nbadge);
    }
}
void calcola_incassi_mensili(struct ingresso *elenco, int n, double *incassi){
    int i;

    for(i=0;i<n;i++){
        incassi[elenco[i].data.mese-1]+=elenco[i].prezzo;
    }

}

void stampa_incassi_mensili(struct ingresso *elenco, int n){
    double incasso_mensile[12] = { 0.0 };
    calcola_incassi_mensili(elenco, n, incasso_mensile);

    printf("Aprile %.2lf\n",incasso_mensile[3]);
    printf("Maggio %.2lf\n",incasso_mensile[4]);
    printf("Giugno %.2lf\n",incasso_mensile[5]);
    printf("Luglio %.2lf\n",incasso_mensile[6]);
    printf("Agosto %.2lf\n",incasso_mensile[7]);
    printf("Settembre %.2lf\n",incasso_mensile[8]);
}

double incasso_totale(struct ingresso *elenco, int n){
    int i;
    double tot;
    for(i=0;i<n;i++){
        tot+=elenco[i].prezzo;
    }
    return tot;
}



int main(int argc,const char *argv[]){
    FILE *f;
    int n;
    int n_da_stampare=10;
    double tot;
    struct ingresso *elenco;

    if(argc<2){
        puts("Nessun file specificato da linea di comando\n");
        return 1;
    }
    f=fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stderr,"Errore nella lettura del file\n");
        return 1;
    }

    elenco=leggi_file(f, &n);

    tot=incasso_totale(elenco, n);
    printf("[INGRESSI]\n %d\n", n);
    printf("[INVERSIONE]\n");
    stampa_ultimi_inverso(elenco, n,  n_da_stampare);
    printf("[INCASSO_MENSILE]\n");
    stampa_incassi_mensili(elenco, n);
    printf("[INCASSO_TOTALE]\n %.2lf\n", tot);




    free(f);
    fclose(f);
}