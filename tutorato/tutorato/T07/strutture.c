#include <stdio.h>
#include <stdlib.h>

#define MAXN 10


struct punto_t{                 //struttura punti x,y
    double x;
    double y;
}

struct punto_t leggi_punto(void);
void stampa_punto(struct punto_t p);

//inizio programma principale    
int main(int argc, char *argv[])
{
  struct punto_t vett[MAXN];    //vettore da passare alla funzione di lettura
  int n;                        //numero da inserire
  char s[80];
    
  printf("inserire un numero: \n");
  fgets(s,sizeof (s),stdin);
  n=atoi(s);
  if (n>10){
    n=10;  
  }
  int i=0;
  while(i<n){
      
     vett[i]=leggi_punto();
     i++;
  } 
  for(i=0;i<n;i++){
      stampa_punto(p);
  }
      
  
  return 0;
}





struct punto_t leggi_punto(void){
    char linea[1024];
    struct punto_t p;
    
    fgets(linea, sizeof(linea), stdin);
    sscanf(linea, "%lf %lf", &p.x, &p.y);
    return p;
}

void stampa_punto(struct punto_t p){
    
    printf("(%.3lf, %.3lf)\n", p.x, p.y); 
    
}
