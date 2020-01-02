#include <stdio.h>
#include <stdlib.h>

#define Nmax 100
#define Vmax 30
#define Vmin 18
#define Voti 13

void leggi_voti(int vet[],int n);
void stampa_voti(int vet[],int n);
int minimo(int vet[],int n);
void frequenza(int freq[],int vet[],int n);
int freqmax(int freq[]);

int main()
{   
   int vet[Nmax];
   int freq[Voti]={0};
   int n;
   char s[80];
    
   printf("inserire un numero: \n");
   fgets(s,sizeof (s),stdin);
   n=atoi(s);
   
   if(n<=0 || n>100){
       
       printf("[RISULTATO]\n");
       printf("errore\n");
   }else{
 
  leggi_voti(vet,n);
  }
  
  printf("[VALORI]\n");
  stampa_voti(vet,n);    
  
  printf("[MINIMO]\n");
  printf("%d\n", minimo(vet,n));
  
  printf("[FREQUENZE]\n");
  frequenza(freq,vet,n);
  
  printf("[MAXFREQ]\n");
  printf("%d\n",freqmax(freq));
  
  return 0;
}

void leggi_voti(int vet[],int n)
{
    int i=0,v;
    char s[80];
    
    //inserimento voti
  while(i<n){
      
        printf("inserire il voto: \n");
        fgets(s,sizeof (s),stdin);
        v=atoi(s);
  //controllo validita 
        if(v>=Vmin && v<=Vmax){
            vet[i]=v;
            i++;       
        }       
    }
}

void stampa_voti(int vet[],int n){
    
    for (int i = 0; i < n; i++)
    printf("%d\n", vet[i]);
}

int minimo(int vet[],int n){
    
  int min=vet[0];
  for(int i=1;i<n;i++){
      if(min>vet[i])
         min=vet[i];                  
}   
    return min;
       
}

void frequenza(int freq[],int vet[],int n){
    
    for(int i=0;i<n;i++){
         freq[vet[i]-Vmin]++;        
    }
    
    for (int i=0; i<Voti; i++){
        printf("%d\n", freq[i]);
    }
}

int freqmax(int freq[]){
    int max=0;    
    for(int i=1;i<Voti;i++){
        if(freq[i]>freq[max])
        max=i;       
    } 
   
    return max+Vmin;
          
   }



