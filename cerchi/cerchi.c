#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//DEFINIZIONE MACRO
#define MAX_CAR    (127)
#define NESSUNA    (0)
#define INTERSECA  (1)
#define CONTIENE   (2)
#define COINCIDE   (3)
#define SQR(x) ((x)*(x))
char *nome_relazione[] = { "", "INTERSECA", "CONTIENE", "COINCIDE" };

//DICHIARAZIONE STRUTTURA
struct cerchio
{
    char nome[MAX_CAR+1];
    int x, y;
    unsigned int r;

};


//FUNZIONE DI APERTURA E LETTURA FILE
struct cerchio *carica_elenco(FILE *f, int *n){
    char buf[1000];
    struct cerchio *elenco, *redim_elenco;
    int dim=MAX_CAR;

    elenco=malloc(dim * sizeof(*elenco));
    if(!elenco)
        return NULL;

    (*n)=0;
    while(fgets(buf,sizeof(buf),f)){
        sscanf(buf,"%s %d %d %d",
                elenco[*n].nome,
                &elenco[*n].x,
                &elenco[*n].y,
                &elenco[*n].r);
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

//FUNZIONE STAMPA CONTENUTO FILE
void stampa_cerchi(struct cerchio *elenco,int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %d %d %d\n", elenco[i].nome, elenco[i].x, elenco[i].y, elenco[i].r);
    }
}

//FUNZIONE COMPARA CERCHI PER ORDINAMENTO
int cmp_cerchi(const void *p1,const void *p2){
    const struct cerchio *c1=p1, *c2=p2;

    if(c1->r < c2->r) return -1;
    if(c1->r > c2->r) return 1;
    return 0;

}

//FUNZIONE RELAZIONI TRA CERCHI
int relazione(struct cerchio *c1, struct cerchio *c2){
    int rel=NESSUNA;
    int sd;                                //distanza tra cerchi

    sd=sqrt(SQR(c1->x - c2->x) + SQR(c1->y - c2->y));
    if(sd<=(c1->r + c2->r)){
        if ( c1->x == c2->x && c1->y == c2->y && c1->r == c2->r ){
            rel = COINCIDE;
    } else if ( sd >= abs(c1->r - c2->r) ) {
            rel = INTERSECA;
    }else if ( c1->r > c2->r) {
            rel = CONTIENE;
        }
    }
    return rel;
}

void stampa_relazioni(struct cerchio *elenco, int n)
{
    int i, j, rel;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            if (i != j) {
                rel = relazione(elenco+i, elenco+j);
                if ( rel != NESSUNA )
                    printf("%s %s %s\n", (elenco+i)->nome, nome_relazione[rel], (elenco+j)->nome);
            }
        }
    }
}


//PROTOTIPI FUNZIONI
struct cerchio *carica_elenco(FILE *f, int *n);
void stampa_cerchi(struct cerchio *elenco,int n);
int cmp_cerchi(const void *p1,const void *p2);
int relazione(struct cerchio *c1, struct cerchio *c2);
void stampa_relazioni(struct cerchio *elenco, int n);



//INIZIO PROGRAMMA PRINCIPALE
int main(int argc, const char *argv[]){
    FILE *f;
    int n;
    struct cerchio *elenco;


    if(argc<2){
        puts("Nessun file specificato da linea di comando");
        return 1;
    }
    if((f=fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Errore nell'apertura del file.\n");
        return 1;
    }

    elenco=carica_elenco(f, &n);
    printf("\n [CERCHI]\n");
    stampa_cerchi(elenco, n);
    printf("\n[ORDINAMENTO]");
	qsort(elenco, n, sizeof(*elenco), cmp_cerchi);
    stampa_cerchi(elenco, n);
    printf("\n[RELAZIONI]");
    stampa_relazioni(elenco, n);
}