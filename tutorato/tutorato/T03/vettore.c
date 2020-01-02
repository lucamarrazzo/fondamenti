#include <stdio.h>
#include <stdlib.h>

#define Nmax 100
#define Vmax 30
#define Vmin 18
#define Voti 13

int main()
{
   int max,min,v,n,i=0;
   int vet[Nmax];
   int freq[Voti]={0};
   char s[80];
   
   
   printf("inserire un numero: \n");
   fgets(s,sizeof (s),stdin);
   n=atoi(s);
   
   if(n<=0 || n>100){
       printf("[RISULTATO]\n");
       printf("errore");
   }else
   {
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
    printf("[VALORI]\n");
    for (i = 0; i < n; i++)
    printf("%d\n", vet[i]);
   

  //min
  min=vet[0];
  for(i=1;i<n;i++){
      if(min>vet[i])
         min=vet[i];                  
}
    printf("[MINIMO]\n");
    printf("%d\n", min);
    
  //frequenza
  
    for(i=0;i<n;i++){
         freq[vet[i]-Vmin]++;        
    }
    printf("[FREQUENZE]\n");
    for (i=0; i<Voti; i++){
        printf("%d\n", freq[i]);
    }
    
    max=0;    
    for(i=1;i<Voti;i++){
        if(freq[i]>freq[max])
        max=i;       
    } 
    printf("[FREQMAX]\n");
    printf("%d\n", max+Vmin);
          
   }
  return 0;
}
