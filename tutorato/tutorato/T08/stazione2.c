#include <stdio.h>
#include <stdlib.h>



void elabora_file(FILE * f);
int notturno(int h);

int main(int argc, const char *argv[])
{
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
    elabora_file(infile);
    fclose(infile);

    return 0;
}


void elabora_file(FILE *f)
{
    char buf[1000];
    int n;                 // numero di righe lette
    int nconv;             // numero di elementi convertiti
    float max_temp;        // temperatura massima
    int aa, MM, gg;        // data
    int hh, mm, ss, ms;    // orario
    char id[11];           // identificativo del dispositivo
    float temp;            // temperatura
    int umid;              // umidità
    float vel;             // velocità del vento

    puts("[NOTTURNO]");
    n = 0;
    max_temp = -300.0;
    /* ogni ciclo legge una riga dal file */
    while (fgets(buf, sizeof(buf), f)) {
        /* conversione dei dati contenuti nella riga letta */
        nconv = sscanf(buf, "%d-%d-%d %d:%d:%d.%d %s %f %d%% %f",
            &aa, &MM, &gg,
            &hh, &mm, &ss, &ms,
            id, &temp, &umid, &vel);

        /* i dati completi sono 11;
         * se sono di meno è una riga vuota
         */
        if (nconv != 11) continue;
        /* tiene traccia della temperatura massima */
        if (temp > max_temp) max_temp = temp;
        /* stampa la riga corrente se in fascia notturna */
        if (notturno(hh)) printf("%s", buf);
        /* incrementa il numero di righe lette correttamente */
        n++;
    }
    /* stampa i risultati */
    printf("\n[MAX-TEMP]\n%.1f\n", max_temp);
    printf("\n[RIGHE]\n%d\n", n);
}
int notturno(int h)
{
    if ((h >= 22) || (h <= 5)) return 1;
    return 0;
}
  
  
  







