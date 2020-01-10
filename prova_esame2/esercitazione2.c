#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RIGA (12)

struct partita{
    char riga[3][MAX_RIGA];
    int nv;
};

struct partita *leggi_file(FILE *f,int *n);
void stampa_partite(struct partita *partite, int n);
int non_validi(struct partita *partite, int n);
void xeo(struct partita *partite, int n);
int corrette(struct partita *partite, int n);
int tris_riga(struct partita *p, int gioc);
int tris_colonna(struct partita *p, int gioc);
int tris_diag_1(struct partita *p, int gioc);
int tris_diag_2(struct partita *p, int gioc);
int vittorie_x(struct partita *partite, int n);
int confronto(const void *p1, const void *p2);
void stampa_righe_ordinate(struct partita *partite, int n);

int main(int argc, const char *argv[]){
    FILE *f;
    int n,nv,c,v;
    struct partita *partite;

    if (argc < 2) {
        puts("Nessun file specificato da linea di comando.");
        return 1;
    }
    if ((f=fopen(argv[1], "r")) == NULL) {
        puts("Errore nell'apertura del file.");
        return 1;
    }
    // richiamo le funzioni del programma
    partite = leggi_file(f, &n);
    c=corrette(partite,n);
    v=vittorie_x(partite, n);
    nv=non_validi(partite, n);
    printf("\n[PARTITE]\n%d\n", n);
    //stampa_partite(partite, n);
    printf("\n[NON-VALIDI]\n%d\n", nv);
    printf("\n[XEO]\n");
    xeo(partite,n);
    printf("\n[CORRETTE]\n %d\n",c);
    printf("\n[VITTORIE-X]\n %d\n",v);
    puts("\n[ORDINAMENTO]");
	printf("\n[ORDINAMENTO]\n");
    stampa_righe_ordinate(partite, n);
    free(partite);
    fclose(f);
}


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

void stampa_partite(struct partita *partite, int n){
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < 3; j++) {
            printf("%s", partite[i].riga[j]);
        }
        puts("---");
    }
}

int non_validi(struct partita *partite, int n){
    int i,j,k,nv=0,lung;
    char car;

    for(i=0;i<n;i++){
        partite[i].nv=0;
        for(j=0;j<3;j++){
            lung = strlen(partite[i].riga[j]) - 1;
            for(k=0;k<lung;k++){
                // verifico se si tratta di un carattere non valido
                car = partite[i].riga[j][k];
                if((car!='x')&&(car!='.')&&(car!='o')){
                    nv++;
                    partite[i].nv++;
                }
            }
        }
    }
    return nv;
}

void xeo(struct partita *partite, int n){
    int i,j,k,len;
    int sx=0, so=0;

    for(i=0;i<n;i++){
        for(j=0;j<3;j++){
            len=strlen(partite[i].riga[j])-1;
            for(k=0;k<len;k++){
                if(partite[i].riga[j][k]=='x')sx++;
                if(partite[i].riga[j][k]=='o')so++;

            }
        }
    }
    printf("%d\n%d\n",sx/n, so/n);
}

int corrette(struct partita *partite, int n){
    int i, c=0;
    for(i=0;i<n;i++){
        if(partite[i].nv==0)
        c++;
    }
    return c;
}

int tris_riga(struct partita *p, int gioc){
    int i,riga,count;
    for(riga=0;riga<3;riga++){
        count=0;
        for(i=0;i<3;i++){
            if(p->riga[riga][i]==gioc)
                count++;
            if(count==3)
                return 1;
        }
    }
    return 0;
}

int tris_colonna(struct partita *p, int gioc){
    int i,colonna,count;
    for(colonna=0;colonna<3;colonna++){
        count=0;
        for(i=0;i<3;i++){
            if(p->riga[i][colonna]==gioc)
                count++;
            if(count==3)
            return 1;
        }
    }
    return 0;
}

int tris_diag_1(struct partita *p, int gioc){
    int i, count;
    for(i=0;i<3;i++){
        if(p->riga[i][i]==gioc)
            count++;
        if(count==3)return 1;
    }
    return 0;
}

int tris_diag_2(struct partita *p, int gioc){
    int i, count;

    for(i=0;i<3;i++){
        if(p->riga[i][2-i]==gioc)
            count++;
        if(count==3)return 1;
    }
    return 0;

}

int vittorie_x(struct partita *partite, int n){
    int i,vittorie=0;
    for(i=0;i<n;i++){
        if(partite[i].nv!=0)continue;
        if (tris_riga(&partite[i], 'x')||
            tris_colonna(&partite[i], 'x')||
            tris_diag_1(&partite[i], 'x')||
            tris_diag_2(&partite[i], 'x')){
                vittorie++;
        }
    }
    return vittorie;
}

int confronto(const void *p1, const void *p2)
{
    const char **s1 = p1, **s2 = p2;
    return strcmp(*s1, *s2);
}

void stampa_righe_ordinate(struct partita *partite, int n)
{
    char **righe;
    int i, j, tot;

    // crea un vettore di puntatori a stringhe per l'ordinamento
    righe = malloc(3 * n * sizeof(*righe));
    tot = 0;
    // riempie il vettore di stringhe
    for (i = 0; i < n; ++i) {
        for (j = 0; j < 3; ++j) {
            // con strdup si crea spazio in memoria per la stringa
            righe[tot] = (char *)(&(partite[i].riga[j]));
            tot++;
        }
    }
    // ordinamento tramite qsort del vettore di puntatori
    qsort(righe, tot, sizeof(*righe), confronto);
    // stampa delle stringhe ordinate
    for (i = 0; i < tot; ++i) {
        printf("%s", righe[i]);
    }
    // libera la memoria allocata per il vettore
    free(righe);
}