#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MESI_X_ANNO (12)
//STRUTTURE
struct data{
    int giorno, mese, anno;
};

struct ingresso{
    struct data data;
    int nbadge;
    int permanenza;
    double prezzo;
};

//VETTORE DI STRINGHE CON TUTTI I MESI DELL'ANNO
char *NOMI_MESI[] = {
    "Gennaio", "Febbraio", "Marzo",
    "Aprile", "Maggio", "Giugno",
    "Luglio", "Agosto", "Settembre",
    "Ottobre", "Novembre", "Dicembre"
};


//PROTOTIPI DELLE FUNZIONI
struct ingresso *leggi_file(FILE *f, int *n);
void stampa_inversa(struct ingresso *elenco, int n, int n_da_stampare);
int durata(int h1, int m1, int h2, int m2);
double calcola_prezzo(int tempo);
void calcolca_incasso_mensile(struct ingresso *elenco, int n, double *incassi);
void stampa_incasso_mensile(struct ingresso *elenco, int n);
double incasso_totale(struct ingresso *elenco, int n);
int calcola_mese_max_ingressi(struct ingresso *elenco, int n);



//PROGRAMMA PRINCIPALE
int main(int argc, const char *argv[]){
    FILE *f;
    int n, n_da_stampare=10;
    struct ingresso *elenco;

    if(argc<2){
        puts("Nessun file specificato da linea di comando.\n");
        return 1;
    }
    if((f=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file. \n");
        return 1;
    }

    elenco=leggi_file(f,&n);

    printf("\n [INGRESSI] \n %d\n",n);
    printf("\n [INVERSIONE] \n");
    stampa_inversa(elenco,n, n_da_stampare);
    printf("\n [INCASSO_MENSILE] \n");
    stampa_incasso_mensile(elenco, n);
    printf("\n [INCASSO_TOTALE] \n %.2lf \n", incasso_totale(elenco, n));

    return 0;
}



//FUNZIONE DI LETTURA ED ESTRAZIONE FILE
struct ingresso *leggi_file(FILE *f, int *n){
    char buf[1000];
    struct ingresso *elenco,*redim_elenco;
    int dim=4;
    int h1, m1, h2, m2;

    elenco=malloc(dim * sizeof(*elenco));
    if(elenco==NULL)return NULL;

    while(fgets(buf, sizeof(buf), f)){
        sscanf(buf,"%d/%d/%d %d %d:%d %d:%d",
                &elenco[*n].data.giorno, &elenco[*n].data.mese, &elenco[*n].data.anno,
                &elenco[*n].nbadge, &h1, &m1, &h2, &m2);

        //con due funzioni esterne trovo la durata e di conseguenza il prezzo
        elenco[*n].permanenza=durata(h1, m1, h2, m2);
        elenco[*n].prezzo=calcola_prezzo(elenco[*n].permanenza);
        (*n)++;

        //riallocazione memoria se il numero di elementi letti (*n) supera la dimensione (dim) iniziale
        if((*n)>=dim){
            dim*=2;
            redim_elenco=realloc(elenco, dim * sizeof(*elenco));
            if(redim_elenco==NULL)return NULL;
            elenco=redim_elenco;
        }
    }
    elenco=realloc(elenco,(*n) * sizeof(*elenco));
    return elenco;
}

//FUNZIONE DI STAMPA ULTIMI 10 ELEMENTI INVERSA
void stampa_inversa(struct ingresso *elenco, int n, int n_da_stampare){
    int i;
    if(n<n_da_stampare)
        n_da_stampare=n;
    for(i=0;i<n_da_stampare;i++){
        printf("%d\n",elenco[n-i-1].nbadge);
    }
}

//FUNZIONE CALCOLA DURATA IN MINUTI
int durata(int h1, int m1, int h2, int m2){
    int min1=(h1 *60)+m1;
    int min2=(h2*60)+m2;

    return min2-min1;
}

//FUNZIONE CALCOLA PREZZO IN BASE ALLA DURATA
double calcola_prezzo(int tempo){
    if(tempo<=20)return 3.5;
    if(tempo<=30)return 4.0;
    if(tempo<=45)return 4.5;
    if(tempo<=60)return 5.5;
    return 7.0;
}

//FUNZIONE CALCOLA INCASSO MENSILE
void calcolca_incasso_mensile(struct ingresso *elenco, int n, double *incassi){
    int i;
    for(i=0;i<n;i++){
        incassi[elenco[i].data.mese-1]+=elenco[i].prezzo;
    }
}

//STAMPA INCASSO MENSILE
void stampa_incasso_mensile(struct ingresso *elenco, int n){
    double incasso_mensile[MESI_X_ANNO]={0.0};
    calcolca_incasso_mensile(elenco, n, incasso_mensile);
    int i;
    int mesi_lavorativi=8;
    for(i=3;i<mesi_lavorativi+1;i++){
    printf("%s %.2lf \n",NOMI_MESI[i], incasso_mensile[i]);
    }
}

//CALCOLCA INCASSO TOTALE NELL'ANNO
double incasso_totale(struct ingresso *elenco, int n){
    int i;
    double tot;
    for(i=0;i<n;i++){
        tot+=elenco[i].prezzo;
    }
    return tot;
}

int calcola_mese_max_ingressi(struct ingresso *elenco, int n){
    
}