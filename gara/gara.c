#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_CAR (50)
#define POS_A_PUNTI (10)
#define N_PILOTI (20)
#define N_SQUADRE (10)

int punti_per_pos[POS_A_PUNTI]={25, 18, 12, 10, 8, 6, 4, 2, 1};

struct gara{
    char pilota[MAX_CAR+1];
    int punti;
};

struct gara *leggi_file(FILE *f,int *n){
    char buf[1000];
    struct gara *gare,*redim_gare;
    int dim=4;
    (*n)=0;

    gare=malloc(dim * sizeof(*gare));
    if(gare==NULL){
        return NULL;
    }
    while(fgets(buf,sizeof(buf),f)){
        sscanf(buf,"%s %s",gare[*n].pilota, gare[*n+1].pilota);
        (*n)++;
        if((*n)>=dim){
            dim*=2;
            redim_gare=realloc(gare, dim * sizeof(*gare));
            if(redim_gare==NULL)return NULL;
            gare=redim_gare;
        }

    }
    gare=realloc(gare, (*n) *sizeof(*gare));
    return gare;
}