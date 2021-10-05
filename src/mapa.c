#include"mapa.h"

#define N 910

char mapa[N][N];

void inicia_mapa(){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            mapa[i][j]=' ';
        }
    }
   /* printf("%d\n",N);
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%c",mapa[i][j]);
        }
        printf("\n");
    }
    */
}

void carrinhoSozinho(){
    
    int distanciaFrontal = 0;
    int distanciaLateral=0;
    int distanciaTraseira=0;


    
}