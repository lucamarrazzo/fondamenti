//Davide Previte, mat. 447403

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_RIGA (12)

//dichiarazione della struttura
struct partita {
    char riga[3][MAX_RIGA];    // matrice utilizzata per salvare le partite
    int nv;            // indica se la partita e' scritta correttamente o meno
};

// lettura del file
struct partita *leggi_file(FILE * fin, int *n)
{
    char buf[MAX_RIGA];
    struct partita *partite, *tmp_partite;
    int dim = 4;
    int i = 0;

    partite = malloc(dim * sizeof(*partite));
    if (!partite)
        return NULL;

    *n = 0;
    while (fgets(buf, sizeof(buf), fin)) {
        // controllo se la riga letta e' un separatore di partite
        if ((buf[0] == '-') && (buf[1] == '-') && (buf[2] == '-')) {
            (*n)++;
            i = 0;
        } else {
            //copio la riga di file nella matrice
            strcpy(partite[*n].riga[i], buf);
            i++;
        }
        if (*n >= dim) {
            dim *= 2;
            tmp_partite = realloc(partite, dim * sizeof(*partite));
            if (!tmp_partite)
                return NULL;
            partite = tmp_partite;
        }
    }
    (*n)++;
    partite = realloc(partite, (*n) * sizeof(*partite));
    return partite;
}

// RICHIESTA 2
int non_validi(struct partita *partite, int n)
{
    int i, j, k, nv = 0, lung;
    char car;

    for (i = 0; i < n; i++) {
        partite[i].nv = 0;
        for (j = 0; j < 3; j++) {
            // lunghezza della riga; il -1 evita di contare il '\n' letto con fgets
            lung = strlen(partite[i].riga[j]) - 1;
            for (k = 0; k < lung; k++) {
                // verifico se si tratta di un carattere non valido
                car = partite[i].riga[j][k];
                if ((car != 'x') && (car != 'o') && (car != '.')) {
                    nv++;    // conto il carattere nel totale di caratteri non validi
                    partite[i].nv++;    // incremento la variabile usata per il controllo nella struct
                }
            }
        }
    }
    // ritorno il numero totale di caratteri non validi
    return nv;
}

// RICHIESTA 3
void xeo(struct partita *partite, int n)
{
    int i, j, k, lung;
    int sx = 0, so = 0;

    for (i = 0; i < n; i++) {
        for (j = 0; j < 3; j++) {
            // analizzo tutti i caratteri di ogni riga eccetto quello di terminazione
            lung = strlen(partite[i].riga[j]) - 1;
            for (k = 0; k < lung; k++) {
                if (partite[i].riga[j][k] == 'x') sx++;
                if (partite[i].riga[j][k] == 'o') so++;
            }
        }
    }
    // stampo il numero totale di simboli divisi per il totale di partite, ottenendo la media
    printf("%d\n%d\n", sx / n, so / n);
}

// RICHIESTA 4
int corrette(struct partita *partite, int n)
{
    int i, c = 0;
    for (i = 0; i < n; i++)
        // la partita e' corretta se la variabile nv e' rimasta uguale a zero.
        // Viene infatti incrementata nella funziona "non_validi" se trova un carattere errato
        if (partite[i].nv == 0) c++;
    return c;
}

// Verifica se il giocatore "gioc" ha fatto tris su una riga.
// Il problema richiede le vittorie di 'x', ma questa funzione e` piu` generale.
int tris_riga(struct partita *p, int gioc)
{
    int riga, i, count;
    for (riga = 0; riga < 3; riga++) {
        count = 0;
        for (i = 0; i < 3; i++)
            if (p->riga[riga][i] == gioc) count++;
        if (count == 3) return 1;
    }
    return 0;
}

// Verifica se il giocatore "gioc" ha fatto tris su una colonna.
// Il problema richiede le vittorie di 'x', ma questa funzione e` piu` generale.
int tris_colonna(struct partita *p, int gioc)
{
    int colonna, i, count;
    for (colonna = 0; colonna < 3; colonna++) {
        count = 0;
        for (i = 0; i < 3; i++)
            if (p->riga[i][colonna] == gioc) count++;
        if (count == 3) return 1;
    }
    return 0;
}

// Verifica se il giocatore "gioc" ha fatto tris sulla diagonale principale.
// Il problema richiede le vittorie di 'x', ma questa funzione e` piu` generale.
int tris_diag_1(struct partita *p, int gioc)
{
    int i, count = 0;
    for (i = 0; i < 3; i++) {
        if (p->riga[i][i] == gioc) count++;
        if (count == 3) return 1;
    }
    return 0;
}

// Verifica se il giocatore "gioc" ha fatto tris sulla diagonale secondaria.
// Il problema richiede le vittorie di 'x', ma questa funzione e` piu` generale.
int tris_diag_2(struct partita *p, int gioc)
{
    int i, count = 0;
    for (i = 0; i < 3; i++) {
        if (p->riga[i][2 - i] == gioc) count++;
        if (count == 3) return 1;
    }
    return 0;
}

// RICHIESTA 5
int vittorie_x(struct partita *partite, int n)
{
    int i, vittorie = 0;
    for (i = 0; i < n; i++) {
        //considero solo le partite valide
        if (partite[i].nv != 0) continue;
        if (tris_riga(&partite[i], 'x') ||
            tris_colonna(&partite[i], 'x') ||
            tris_diag_1(&partite[i], 'x') ||
            tris_diag_2(&partite[i], 'x'))
            vittorie++;
    }
    // ritorno il numero di vittorie totali di "x"
    return vittorie;
}

void stampa_partite(struct partita *partite, int n)
{
    int i, j;

    for (i = 0; i < n; ++i) {
        for (j = 0; j < 3; j++) {
            printf("%s", partite[i].riga[j]);
        }
        puts("---");
    }
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


int main(int argc, char *argv[])
{
    int n, nv, c, v;
    struct partita *partite;
    FILE *fin;

    // controllo la linea di comando
    if (argc < 2) {
        puts("Nessun file specificato da linea di comando.");
        return 1;
    }
    if ((fin = fopen(argv[1], "r")) == NULL) {
        puts("Errore nell'apertura del file.");
        return 1;
    }
    // richiamo le funzioni del programma
    partite = leggi_file(fin, &n);
    //stampa_partite(partite, n);
    nv = non_validi(partite, n);
    c = corrette(partite, n);
    v = vittorie_x(partite, n);

    // stampo i risultati e richiamo le funzioni void
    printf("\n[PARTITE]\n%d\n", n);
    printf("\n[NON-VALIDI]\n%d\n", nv);
    printf("\n[XEO]\n");
    xeo(partite, n);
    printf("\n[CORRETTE]\n%d\n", c);
    printf("\n[VITTORIE-X]\n%d\n", v);
    printf("\n[ORDINAMENTO]\n");
    stampa_righe_ordinate(partite, n);
    free(partite);

    return 0;
}
