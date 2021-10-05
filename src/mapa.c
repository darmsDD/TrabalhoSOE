#include"mapa.h"

#define N 10000

void mapa(){

    char mapa[N][N];

    memset(&mapa,0,sizeof(mapa));


    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%d",mapa[i][j]);
        }
        printf("\n");
    }


}