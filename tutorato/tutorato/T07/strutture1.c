#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAXN 10 

struct punto_t{
    
    double x;
    double y;
};

struct punto_t origine = {0, 0};


struct punto_t leggi_punto(void);
void stampa_punto(struct punto_t p);
double distanza(struct punto_t p1, struct punto_t p2);


int main(void){
    
    char s[80];
    struct punto_t vett[MAXN];
    int n;
    double d;
    printf("inserire un numero \n");
    fgets(s,sizeof(s),stdin);
    n=atoi(s);
    if(n>10 ){
        n=10;
    }
    /*lettura punti*/
    int i=0;
    while(i<n){
        vett[i]=leggi_punto();
        i++;
    }
    /*stampa punti */
    printf("[PUNTI] \n");
    for(i=0;i<n;i++){
        stampa_punto(vett[i]);
    }
    /*distanza dall'origine */
   printf("[DISTANZE] \n");
    for(i=0;i<n;i++){
        d=distanza(origine,vett[i]);
        printf("%.3lf \n",d);
    }
    
}


struct punto_t leggi_punto(void){
    
    char linea[1024];
    struct punto_t p;
    
    printf("inserire le coordinate\n");
    fgets(linea, sizeof(linea), stdin);
    sscanf(linea, "%lf %lf", &p.x, &p.y);
    
    return p;
    
}

void stampa_punto(struct punto_t p){
    
    printf("(%.3lf, %.3lf)\n", p.x, p.y);
}

double distanza(struct punto_t p1, struct punto_t p2){
    
    return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
    
}
