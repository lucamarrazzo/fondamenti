#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int trova_ultimo_separatore(const char *percorso);
void basename(const char *percorso, char *b);
void dirname(const char *percorso, char *b);



int main(int argc, char *argv[]){
    
    
    char percorso[1024];
    char b[1024];
    strcpy(percorso,argv[1]);    
    
    printf("[BASENAME]\n");
    
    basename(percorso,b);
    printf("%s\n",b);
        
}


int trova_ultimo_separatore(const char *percorso){
    
    int pos=strlen(percorso)-1;
    while(pos>=0 && percorso[pos]!='/'){
        pos--;
    }
    return pos;    
}

void basename(const char *percorso, char *b){
    
    int pos=trova_ultimo_separatore(percorso);
    strcpy(b,percorso+pos+1);
    
}

void dirname(const char *percorso, char *b) {
    int i;
    int n = trova_ultimo_separatore(percorso);

    /* Scrittura del terminatore tenendo anche conto del caso n == -1 */
    if (n >= 0) {
        /* Copia in b i primi n caratteri del percorso */
        for (i = 0; i < n; i++)
            b[i] = percorso[i];
        b[n] = '\0';
    } else
        b[0] = '\0';
}

