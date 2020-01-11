#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


struct partita
{
    char gioc1[50], gioc2[50];
    int nset;
    int max_set;
    int punteggio[5][2];

};

struct partita *leggi_file(FILE *f, int *n){
    char buf[1000];
    int conv,dim=4;
    struct partita *partite, *redim_partite;

    (*n)=0;
    partite=malloc(dim * sizeof(*partite));
    if(partite==NULL){
        (*n)=0;
        return NULL;
    }

    while(fgets(buf, sizeof(buf),f)){
        conv=sscanf(buf,"%50s %50s %d %d-%d %d-%d %d-%d %d-%d %d-%d",
        partite[*n].gioc1, partite[*n].gioc2, &partite[*n].max_set,
        &partite[*n].punteggio[0][0], &partite[*n].punteggio[0][1],
        &partite[*n].punteggio[1][0], &partite[*n].punteggio[1][1],
        &partite[*n].punteggio[2][0], &partite[*n].punteggio[2][1],
        &partite[*n].punteggio[3][0], &partite[*n].punteggio[3][1],
        &partite[*n].punteggio[4][0], &partite[*n].punteggio[4][1]);

        if(conv<7){
            free(partite);
            return NULL;
        }
        partite[*n].nset=(conv-3)/2;

        (*n)++;


        if((*n)>=dim){
            dim*=2;
            redim_partite=realloc(partite, dim * sizeof(*partite));
            if (redim_partite==NULL) return NULL;
            partite=redim_partite;
        }
    }
    partite=realloc(partite, (*n) * sizeof(*partite));
    return partite;
}

void stampa_partite(struct partita *partite, int n){


        printf("[numero di set giocati]\n %d",partite->nset);

}

int giochi_in_partita(struct partita *partite){
    int i, giochi=0;
    for(i=0;i<partite->nset;i++){
        giochi+=(partite->punteggio[i][0] + partite->punteggio[i][1]);
    }
    return giochi;
}

int indice_partita_max_giochi(struct partita *partite, int n, int *max){
    int i,giochi;
    int id=0;

    *max=giochi_in_partita(partite);
    for(i=1;i<n;i++){
        giochi=giochi_in_partita(partite + i);
        if(giochi>*max){
            id=i;
            *max=giochi;

        }
    }

    return id;
}





int main(int argc, const char *argv[]){
    FILE *f;
    int max, n, indice;
    struct partita *partite;

    if(argc<2){
        puts("Nessun file specificato da linea di comando.");
        return 1;
    }
    f=fopen(argv[1],"r");
    if(f==NULL){
        fprintf(stderr,"Errore nell'apertura del file.");
        return 1;
    }

    partite=leggi_file(f,&n);
    indice=indice_partita_max_giochi(partite, n, &max);

    stampa_partite(partite, n);
    printf("\n [MAX-GIOCHI]\n %50s %50s %d\n", partite[indice].gioc1, partite[indice].gioc2, max);

}