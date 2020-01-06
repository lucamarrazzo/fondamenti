#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RIGA (12)

struct partita{
    char riga[3][MAX_RIGA];
    int nv;
};

struct partita *leggi_file(FILE *f,int *n){
    char buf[MAX_RIGA];
    struct partita *partite,*tmp_partite;
    int dim=4;
    int i=0;

    partite=malloc(dim * sizeof(*partite));
    if (!partite)
        return NULL;

    *n = 0;
    while(fgets(buf,sizeof(buf),f)){
        if(buf[0]=='-' && buf[1]=='-' && buf[2]=='-'){
            (*n)++;
            i=0;
        }else{
            strcpy(partite[*n].riga[i], buf);
            i++;
        }
        if((*n)>= dim){
            dim*=2;
            tmp_partite=realloc(partite, dim* sizeof(*partite));
            if(tmp_partite==NULL)return NULL;
            partite=tmp_partite;

        }
    }
    (*n)++;
    partite=realloc(partite, (*n) * sizeof(*partite));
    return partite;
}