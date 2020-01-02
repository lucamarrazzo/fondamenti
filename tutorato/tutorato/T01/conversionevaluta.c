#include <stdio.h>
#include <stdlib.h>
int main()
{
   /* dichiarazione variabili */
  double euro;                            // valore da convertire
  double euro_dollaro = 1.18213;          // tasso di cambio
  double dollari;                         // variabile per memorizzare il risultato

  /* conversione da euro a dollari */
  char s[80];
    
  printf("inserire il valore in euro: \n");
  fgets(s,sizeof (s),stdin);
  euro=atof(s);                                //inserimento da tastiera degli euro 
  dollari = euro * euro_dollaro;              //calcolo dollari

  /* stampa risultati */
  printf("Importo in euro : %.2f\n", euro);
  printf("Importo in dollari : %.2f\n", dollari);
return 0;
}

