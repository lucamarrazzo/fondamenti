#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MESI_X_ANNO (12)
#define GIORNI_X_MESE (31)

char *NOMI_MESI[] = {
    "Gennaio", "Febbraio", "Marzo",
    "Aprile", "Maggio", "Giugno",
    "Luglio", "Agosto", "Settembre",
    "Ottobre", "Novembre", "Dicembre"
};

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
    double incasso_mensile[MESI_X_ANNO] = { 0.0 };
    calcola_incassi_mensili(elenco, n, incasso_mensile);

    printf("%s %.2lf\n",NOMI_MESI[3], incasso_mensile[3]);
    printf("%s %.2lf\n",NOMI_MESI[4],incasso_mensile[4]);
    printf("%s %.2lf\n",NOMI_MESI[5],incasso_mensile[5]);
    printf("%s %.2lf\n",NOMI_MESI[6],incasso_mensile[6]);
    printf("%s %.2lf\n",NOMI_MESI[7],incasso_mensile[7]);
    printf("%s %.2lf\n",NOMI_MESI[8],incasso_mensile[8]);
}

double incasso_totale(struct ingresso *elenco, int n){
    int i;
    double tot;
    for(i=0;i<n;i++){
        tot+=elenco[i].prezzo;
    }
    return tot;
}

int calcola_mese_max_ingressi(struct ingresso *elenco, int n){
    int i;
    int ingressi[MESI_X_ANNO]={0};
    int max,mese_max;

    for(i=0;i<n;i++){
        ingressi[elenco[i].data.mese - 1]++;
    }
     for (i = 0; i < MESI_X_ANNO; i++) {
        if (ingressi[i] > max) {
            max = ingressi[i];
            mese_max = i;
        }

    }
    return mese_max;
}
struct data calcola_giorno_max_ingressi(struct ingresso *elenco, int size)
{
    int i, g, m;
    /* per registrare gli ingressi di tutti i giorni dell'anno
     * per semplicita` e generalita` considero tutti e 12 i mesi */
    int ingressi[MESI_X_ANNO][GIORNI_X_MESE] = { {0} };
    int max = 0;
    int g_max, m_max;   /* indici del giorno e mese di massimo ingresso */
    struct data data;

    for (i = 0; i < size; i++) {
        data = elenco[i].data;
        ingressi[data.mese - 1][data.giorno - 1]++;
    }

    max = 0;
    for (m = 0; m < MESI_X_ANNO; m++) {
        for (g = 0; g < GIORNI_X_MESE; g++) {
            if (ingressi[m][g] > max) {
                max = ingressi[m][g];
                m_max = m;
                g_max = g;
            }
        }
    }
    data.anno = elenco[0].data.anno;   /* tutte le date dello stesso anno */
    data.mese = m_max + 1;
    data.giorno = g_max + 1;
    return data;
}




int main(int argc,const char *argv[]){
    FILE *f;
    int n;
    int n_da_stampare=10;
    double tot;
    int mese_max;
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
    mese_max=calcola_mese_max_ingressi(elenco, n);
    printf("[INGRESSI]\n %d\n", n);
    printf("\n[INVERSIONE]\n");
    stampa_ultimi_inverso(elenco, n,  n_da_stampare);
    printf("\n[INCASSO_MENSILE]\n");
    stampa_incassi_mensili(elenco, n);
    printf("\n[INCASSO_TOTALE]\n %.2lf\n", tot);
    printf("\n[MESE_MAX_INGRESSI]\n");
    printf("%s\n", NOMI_MESI[mese_max]);
    printf("\n[GIORNO_MAX_INGRESSI]\n");
    printf("%02d/%02d/%02d\n", calcola_giorno_max_ingressi(elenco, n));
}