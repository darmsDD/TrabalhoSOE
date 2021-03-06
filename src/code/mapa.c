#include"../inc/mapa.h"

int pos[] = {N/2,N/2};
int direcao = 1;
char mapa[N][N];
int parado=1;

char objetos[] = {' ','^','<','v','>','1'};
extern int movimentacao;


void imprime_mapa(){
    //keep_threading = 0;
    FILE * arquivo_mapa;
    arquivo_mapa = fopen("mapa", "w");
    printf("passei aqui\n");
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fprintf(arquivo_mapa,"%c",mapa[i][j]);   
        }
        fprintf(arquivo_mapa,"\n");
    }
   
    printf("passei aqui2\n");
    fclose(arquivo_mapa);
}

void preenche_mapa_obstaculo(int l,int c,int vertical,int sensor){
   
    if(vertical){
        //printf("%d =  %d - %d    vertical = %d\n",l,pos[0], sensor,vertical);
        for(int j=0;j<4;j++){
            mapa[l][c+j] = '1';
        }
    } else{
        //printf("%d =  %d - %d     vertical = %d\n",c,pos[1], sensor,vertical);
        for(int j=0;j<4;j++){
            mapa[l+j][c] = '1';
        }
    }
}


void switch_obstaculos(int direc,int distancia_obstaculo,int desloc_escrita,int tamanho_carrinho){
    int l,c,vertical;
    switch (direc)
    {
        case 1/*para cima*/:
            l = pos[0] - distancia_obstaculo - tamanho_carrinho;
            c = pos[1]-desloc_escrita;
            vertical=1;
            break;
        case 2/*para esquerda*/:
            c = pos[1] - distancia_obstaculo - tamanho_carrinho;
            l = pos[0]-desloc_escrita;
            vertical=0;
            break;
        case 3/*para baixo*/:
            l = pos[0] + distancia_obstaculo + tamanho_carrinho;
            c = pos[1]-desloc_escrita;
            vertical=1;
            break;
        case 4/*para direita*/:
            c = pos[1] + distancia_obstaculo + tamanho_carrinho;
            l = pos[0]-desloc_escrita;
            vertical=0;
            break;
    }
    preenche_mapa_obstaculo(l,c,vertical,distancia_obstaculo);

}


void * obstaculos(void * args){

    struct sensores * sensores_mapa = (struct sensores *)args;
    struct sensores * sensor_frontal_esquerda = sensores_mapa;
    struct sensores * sensor_frontal_direita = sensores_mapa + 1;
    struct sensores * sensorlateral_esquerda = sensores_mapa + 2;
    struct sensores * sensorlateral_direita = sensores_mapa + 3;
    struct sensores * sensor_traseiro = sensores_mapa + 4;

    
    int direc;
    int dist_maxima=30;
    while(*(sensores_mapa->continuaThread)){
        //printf("sensor frontal = %lf\n",sensor_frontal_esquerda->distancia);
        //printf("sensor lateral esquerda = %lf\n",sensorlateral_esquerda->distancia);
        //printf("sensor lateral direita = %lf\n",sensorlateral_esquerda->distancia);
        
        if(sensor_frontal_esquerda->distancia<dist_maxima){
            //printf("total %d = %d - %d\n", (int)round(sensor_frontal_esquerda->distancia) - pos[0], (int)round(sensor_frontal_esquerda->distancia), pos[0]);
            switch_obstaculos(direcao,(int)round(sensor_frontal_esquerda->distancia),3,0);
        } 
        if(sensor_frontal_direita->distancia<dist_maxima){
            //printf("total %d = %d - %d\n", (int)round(sensor_frontal_direita->distancia) - pos[0], (int)round(sensor_frontal_direita->distancia), pos[0]);
            switch_obstaculos(direcao,(int)round(sensor_frontal_direita->distancia),-1,0);
        } 

        if(sensorlateral_esquerda->distancia<dist_maxima){
            direc = direcao%4 +1;
            switch_obstaculos(direc,(int)round(sensorlateral_esquerda->distancia),1,largura_carrinho/2);
        }
        if(sensorlateral_direita->distancia<dist_maxima){
            direc = direcao -1 ;
            if(direc==0){direc=4;}
            switch_obstaculos(direc,(int)round(sensorlateral_direita->distancia),1,largura_carrinho/2);
        }
        /*if(sensor_traseiro->distancia<dist_maxima){
            direc  = (direcao+2)%4;

            switch_obstaculos(direc,(int)round(sensor_traseiro->distancia)+comprimento_carrinho,1);
        }*/

        delayMicroseconds(10000);
    }
    pthread_exit(0);

}

void altera_posicao(int opcao){

    if(opcao == 1){
        if(direcao == 1){
            pos[1]-=5;
        } else if(direcao ==3){
            pos[1]+=5;
        } else if(direcao == 2){
            pos[0]-=5;
        } else if(direcao==4){
            pos[0]+=5;
        }
    } else if(opcao==2){
        if(direcao == 1){
            pos[1] +=5;
        } else if(direcao ==3){
            pos[1]-=5;
        } else if(direcao == 2){
            pos[0] +=5;
        } else if(direcao==4){
            pos[0] -=5;
        }
    } else{
        int dist_giro=15;
         switch (direcao)
        {
        case 1:
            //printf("giro 1\n");
            pos[0]+=dist_giro;
            break;
        case 2:
            //printf("giro 2\n");
            pos[1]+=dist_giro;
            break;
        case 3:
            //printf("giro 3\n");
            pos[0]-=dist_giro;
            break;
        case 4:
            //printf("giro 4\n");
            pos[1]-=dist_giro;
            break;
        default:
            break;
        }
    }


}


void altera_direcao(){

    switch (movimentacao)
    {
    case 1:
        altera_posicao(3);
        direcao = direcao%4 +1;
        break;
    
    case 2:
        altera_posicao(3);
        direcao = direcao - 1 ;
        if(direcao==0){direcao=4;}
        break;
    case 3:
        altera_posicao(1);
        break;
    case 4:
        altera_posicao(2);
        break;
    default:
        break;
    }

}



void * desenha_mapa(void * args){
    
    int * continuaThread = (int *)args;
    
    memset(mapa,' ',sizeof(mapa));
    int l,c,l2,c2;
    while(*(continuaThread)){

        if(movimentacao!=0){
            //printf("porque jesus\n");
            altera_direcao();
            
            movimentacao = 0;
        }
        l = pos[0];
        c = pos[1];
        
        if(direcao==1)/*para cima*/{
            pos[0]--;
        }   else if(direcao==2)/*para esquerda*/{
            pos[1]--;
        } else if(direcao==3) /*para baixo*/{
            pos[0]++;
        }  else if(direcao==4)/*para direita*/{
            pos[1]++;
        }
        
        l2=0,c2=0;
        for(int i=0;i<largura_carrinho/2;i++){
            mapa[l+l2][c+c2] = objetos[direcao];
            (direcao == 1 || direcao ==3)?c2++:l2++;
        }
        l2=0,c2=0;
        for(int i=0;i<largura_carrinho/2;i++){
            mapa[l+l2][c+c2] = objetos[direcao];
            (direcao == 1 || direcao ==3)?c2--:l2--;
        }
        // j++;
        // if(j==20){
        //     printf("aaaaaaaaaa\n");
        //     movimentacao=1;
        // }
        delay(36);
    }

    
    return 0;
}
