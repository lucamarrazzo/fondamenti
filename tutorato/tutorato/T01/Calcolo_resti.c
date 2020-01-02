#include <stdio.h>

int main(){
    
    int importo;
    int b50,b20,b10,b5,b2,b1;
    int resto;

    
    printf("inserire l'importo");
    scanf("%d",&importo);
    

    b50=importo/50;
    resto= importo%50;
    b20=resto/20;
    resto=resto%20;
    b10=resto/10;
    resto=resto%10;
    b5=resto/5;
    resto=resto%5;
    b2=resto/2;
    b1=resto%2;
    
    
    printf("Importo totale : %d euro \n", importo);
    printf("banconote da 50 euro:%d \n", b50);
    printf("banconote da 20 euro:%d \n", b20 );
    printf("banconote da 10 euro:%d \n", b10);
    printf("banconote da 5 euro:%d \n", b5);
    printf("monete da 2 euro:%d \n", b2);
    printf("monete da 1 euro:%d \n", b1);
    
    return 0;
        
}