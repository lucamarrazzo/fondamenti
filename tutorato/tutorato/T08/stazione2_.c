#include <stdio.h>
#include <stdlib.h>

#define ID_MAX 10
#define VettMAX 168

struct misura{
    
    int aa,MM,gg;
    int hh,mm,ss,ms;
    char id[ID_MAX +1];
    float temp;
    int umid;
    float vel;
};

int leggi_file(FILE *f,struct misura *elenco,int *n);
void stampa_riga(struct misura *elenco, int n);
float max_temp(struct misura *elenco, int n);

int main(int argc, const char *argv[])
{
    int n,f;
    struct misura vett[VettMAX];
    FILE *infile;
   
   /* termina se il numero di parametri è errato */
    if (argc != 2)
        return 1;
   
   /* apre il file in lettura */
    infile = fopen(argv[1], "r");
    /* termina in caso di errore */
    if (infile == NULL) {
        fprintf(stderr, "# Errore apertura file\n");
        return 1;
    }
    
    f=leggi_file(infile,&vett[VettMAX],&n);
    
    
    fclose(infile);
   
}



int leggi_file(FILE *f,struct misura *elenco,int n){
    
    char buf[1000];
    int nconv;              //numero di elementi convertiti
    int n,i = 0;
    /* ad ogni iterazione legge una nuova riga */
    while (fgets(buf, sizeof(buf), f)) {
        /* punta all'elemento corrente da memorizzare */
        nconv = sscanf(buf, "%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
                &(elenco[i].aa), &(elenco[i].MM), &(elenco[i].gg),
                &(elenco[i].hh), &(elenco[i].mm), &(elenco[i].ss), &(elenco[i].ms),
                (elenco[i].id), &(elenco[i].temp), &(elenco[i].umid), &(elenco[i].vel));
        /* passa alla riga successiva se non ci sono esattamente 11
         * elementi da convertire */
        if (nconv != 11) continue;
        /* se si arriva qui, la riga è stata letta e memorizzata
         * correttamente; incremento il numero di righe lette */
        i++;
        /* per precauzione controlla che non si leggano più
         * dati di quelli che possono essere ospitati nel vettore;
         * questo non dovrebbe mai succedere se il file è corretto */
        if (i >= VettMAX) break;
    }
    n = i;
}

void stampa_riga(struct misura *elenco, int n){
    
    for(int i=0;i<n;i++)
    printf("%d\n",&(elenco[i].aa));
    
    
}


float max_temp(struct misura *elenco, int n)
{
    float max_temp;
    int i;

    /* esce in caso non vi siano elementi nel vettore */
    if (n <= 0) return -1000;
    /* il massimo viene inizializzato con il primo valore
     * disponibile */
    max_temp = elenco[0].temp;
    /* una iterazione per ogni struttura successiva alla
     * prima, se ce ne sono */
    for (i = 1; i < n; i++) {
        /* se la temperatura corrente è maggiore del
         * massimo attuale, aggiorna il massimo */
        if ((elenco + i)->temp > max_temp)
            max_temp = (elenco + i)->temp;
    }
    return max_temp;
}


