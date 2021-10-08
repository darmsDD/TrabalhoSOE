#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>
#include<signal.h>

int pos[] = {200,200};
int direcao = 1;
int mapa[400][400];
int traj[500][500];
int parado=1;

double sensorFrontal[] = {
        1200,1200,1200,1200,1200,
        5,6.2,5.5,5.3,5.7,6
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

void sig_int(int signal){
    for(int i=0;i<400;i++){
        for(int j=0;j<400;j++){
           
            if(mapa[i][j]==1){
                //printf("i =%d j = %d",i,j);
                printf("1");
            } else if(traj[i][j]==1){
                printf("|");
            }  else if(traj[i][j]==2){
                printf(">");
            }  else{
                printf(" ");
            }
        }
        printf("a\n");
    }
    exit(0);

}

void preencheMapa(int i){
    if(sensorFrontal[i]<1200){
        int l = pos[0] + round(sensorFrontal[i]);
        printf("%d(pos) + %lf(sensorFrontal[i]) = %d(l)\n",pos[0],sensorFrontal[i],l);
        mapa[l][pos[1]] = 1;
        mapa[l][pos[1]+1] = 1;
        mapa[l][pos[1]+2] = 1;
        mapa[l][pos[1]-1] = 1;

        
    }
    if(sensorLateral1[i]<1200){
            int c = pos[1] + round(sensorLateral1[i]);
            printf("%d(pos) + %lf(sensorLateral1[i]) = %d(l)\n",pos[1],sensorLateral1[i],c);
            mapa[pos[0]][c] = 1;
            mapa[pos[0]+1][c] = 1;
            mapa[pos[0]+2][c] = 1;
            mapa[pos[0]-1][c] = 1;
    }

}

void * func(void *args){
   
    for(int i=0;i<11;i++){

        int cond=0;
        preencheMapa(i);
        printf("sensorFrontal = %lf\n",sensorFrontal[i]);
        for(int k=0;k<5;k++){
            if(mapa[pos[0]+k][pos[1]] == 1){cond=1;}
        }
        if(sensorFrontal[i]<=5 || cond){
                printf("freio\n");
                //pos[0]-=5;
                direcao = (direcao==1)?2:1;
                //kill(getpid(),SIGINT);
                i=-1;
                continue;
        }

        parado=1;
        sleep(1);
        while(parado);
    }


}


int main(){

 
    signal(SIGINT,sig_int);
    pthread_t t1,t2,t3,t4;
    
    int vel = 10;
    pthread_create(&t1,NULL,&func,sensorFrontal);
    sleep(1);

    while(1){
        
        int l = pos[0];
        int c = pos[1];
        if(direcao==2){
            for(int i=0;i<5;i++){
                traj[l][c+i] = 2;
                //printf("l = %d c+i = %d\n",l,c+i);
            }
            pos[1]+=5;
        } else if(direcao==1){
            for(int i=0;i<5;i++){
                traj[l+i][c] = 1;
            }
            pos[0]+=5;
        }

        parado=0;
        while(parado==0);
    }


    return 0;
}