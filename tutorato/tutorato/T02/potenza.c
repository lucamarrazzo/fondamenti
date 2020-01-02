#include <stdio.h>
#include <stdlib.h>

int main(){
    
    double a;
    int b;
    double risultato;
    char s[80];
    
    //input dei valori
    printf("inserire la base della potenza: \n");
    fgets(s,sizeof(s),stdin);
    a=atof(s);
    printf("inserire l'esponente della potenza: \n");
    fgets(s,sizeof(s),stdin);
    b=atoi(s);
    
    if ((a == 0 && b == 0)||(b < 0) ) {
        printf("[POTENZA]\n");
        printf("non calcolabile\n");
    } else {      
        risultato = 1;
        while(b>0){
            if (b%2==1){
            risultato=risultato*a;
        }
            a=a*a;
            b/=2;
            
        }
        printf("[POTENZA]\n");
        printf("%f\n", risultato);
}
return 0;
}