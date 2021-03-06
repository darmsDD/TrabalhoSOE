#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>


#define tamanho_carrinho 14
#define N 5000
int pos[] = {N/2,N/2};
int direcao = 3;
char mapa[N][N];
int parado=1;
FILE * arquivo_mapa;
char objetos[] = {' ','^','<','v','>','1'};

double sensorFrontal[] = {
        1200,1200,1200,1200,1200,
        30,28.7,25.2,26.2,24,23
};

double sensorLateral1[] = {
    1200,1200,1200,1200,1200,
    30,25,20,15,10,5
};
double sensorLateral2[] = {
    1200,1200,1200,1200,1200,
    1200,1200,1200,1200,1200,1200,1200,1200
};
double sensorTraseiro[] = {
    1200,1200,1200,1200,1200,
    1200,1200,1200,1200,1200,1200,1200,1200
};

void * le_comando(){
    while(1){
        printf("digite 3 para baixo 1 para cima,\n4 para a direita e 2 para esquerda\n");
        scanf("%d",&direcao);
    }
    pthread_exit(0);
}
void imprime_mapa(){
    int tipo;
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            fprintf(arquivo_mapa,"%c",mapa[i][j]);   
        }
        fprintf(arquivo_mapa,"\n");
    }
    fclose(arquivo_mapa);
    exit(0);
}

void preenche_mapa_obstaculo(int l,int c,int vertical,int sensor){
   
    if(vertical){
        printf("%d =  %d - %d\n",l,pos[0], sensor);
        for(int j=0;j<4;j++){
            mapa[l][c+j] = '1';
        }
    } else{
        printf("%d =  %d - %d\n",c,pos[1], sensor);
        for(int j=0;j<4;j++){
            mapa[l+j][c] = '1';
        }
    }
}


void * obstaculos(){

    int l,c,vertical;
    for(int i=0;i<11;i++){
        printf("sensor frontal[%d] = %lf\n",i,sensorFrontal[i]);
        if(sensorFrontal[i]<1200){
            printf("entrei aqui\n");
            switch (direcao)
            {
                case 1/*para cima*/:
                    l = pos[0] - round(sensorFrontal[i]);
                    c = pos[1]-1;
                    vertical=1;
                    break;
                case 2/*para esquerda*/:
                    c = pos[1] - round(sensorFrontal[i]);
                    l = pos[0]-1;
                    vertical=0;
                    break;
                case 3/*para baixo*/:
                    l = pos[0] + round(sensorFrontal[i]);
                    c = pos[1]-1;
                    vertical=1;
                    break;
                case 4/*para direita*/:
                    c = pos[1] + round(sensorFrontal[i]);
                    l = pos[0]-1;
                    vertical=0;
                    break;
            }
            preenche_mapa_obstaculo(l,c,vertical,round(sensorFrontal[i]));

        }
        sleep(1);
    }


}





int main(){

    int vel = 5;
    pthread_t t1,t2;
   
    signal(SIGINT,imprime_mapa);
    arquivo_mapa = fopen("mapa", "w");
    memset(mapa,' ',sizeof(mapa));
    pthread_create(&t1,NULL,&le_comando,NULL);
    pthread_create(&t2,NULL,&obstaculos,NULL);
    sleep(1);
    int l,c,l2,c2;
    while(1){
        
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
        for(int i=0;i<tamanho_carrinho/2;i++){
            mapa[l+l2][c+c2] = objetos[direcao];
            (direcao == 1 || direcao ==3)?c2++:l2++;
        }
        l2=0,c2=0;
        for(int i=0;i<tamanho_carrinho/2;i++){
            mapa[l+l2][c+c2] = objetos[direcao];
            (direcao == 1 || direcao ==3)?c2--:l2--;
        }
        sleep(1);
    }

    
    return 0;
}