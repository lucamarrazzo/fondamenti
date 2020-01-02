#include <stdio.h>
#include <stdlib.h>

#define MAX_ID_LUNG 10



struct misura {
    int aa, MM, gg;             // data
    int hh, mm, ss, ms;         // orario
    char id[MAX_ID_LUNG + 1];   // identificativo del dispositivo
    float temp;                 // temperatura
    int umid;                   // umidità
    float vel;                  // velocità del vento
};

int leggi_file(FILE *ptr,struct misura *vettore,int n);
void identificativi(struct misura *vettore,int n);

int main(int argc, const char *argv[]){
    
    FILE *infile;
    struct misura *vettore;
    int n=4,f;
    
    if (argc != 2)
        return 1;
   
   /* apre il file in lettura */
    infile = fopen(argv[1], "r");
    /* termina in caso di errore */
    if (infile == NULL) {
        fprintf(stderr, "# Errore apertura file\n");
        return 1;
    }
    vettore=malloc(n*(sizeof(struct misura)));
    f=leggi_file(infile,vettore,n);
    identificativi(vettore,f);
    fclose(infile);
    
    
    
    
    
}

int leggi_file(FILE *ptr,struct misura *vettore,int n){
    
    char s[1000];
    int i=0;
    
    while(fgets(s,sizeof(s),ptr)){
        sscanf(s,"%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
                &(vettore[i].aa), &(vettore[i].MM), &(vettore[i].gg),
                &(vettore[i].hh), &(vettore[i].mm), &(vettore[i].ss), &(vettore[i].ms),
                (vettore[i].id), &(vettore[i].temp), &(vettore[i].umid), &(vettore[i].vel));
                
        i++;
        if(n==i){
            n=n*2;
            vettore=realloc(vettore,n);
        }
    }
    return i;
}

void identificativi(struct misura *vettore,int n){
    
    int i;
    printf("[IDENTIFICATIVI]");
    for(i=n;i>=0;i--){
        printf("%s\n",&(vettore[i].id[i]));
    }
    
    
    
}