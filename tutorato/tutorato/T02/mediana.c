#include <stdio.h>
#include <stdlib.h>
int main(){
    
    int a,b,c;
    int mediana;
    char s[80];
    //input dei valori
    printf("inserire il primo numero \n");
    fgets(s,sizeof(s),stdin);
    a=atoi(s);
    printf("inserire il secondo numero \n");
    fgets(s,sizeof(s),stdin);
    b=atoi(s);
    printf("inserire il terzo numero \n");
    fgets(s,sizeof(s),stdin);
    c=atoi(s);
    
    if(a<=b && a<=c ){
        if(b<c)
            mediana=b;
        else
            mediana=c;
    }else if(b<=c && b<=a ){
        if (a<c)
            mediana=a;
        else
            mediana=c;
    }else{
        if (a<b)
        mediana=a;
        else
        mediana=b;
    }
    
    printf("[MEDIANA]\n");
    printf("%d \n",mediana);
    
    return 0;
    
    
}