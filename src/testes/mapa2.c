#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include<unistd.h>
#include<signal.h>

int pos[] = {200,200};
int direcao = 1;
int mapa[500][500];
FILE *arquivo_mapa;

void preenche_mapa(int direc){

    int l = pos[0];
    int c = pos[1];
    int p = 0;

    if(direc==2){
        mapa[l][c] = 2;
        fprintf(arquivo_mapa,">");
    }  else if(direc==1){
        mapa[l][c] = 3;
        p=0;
        printf("%d %d\n",c-1,400-c-1);
        fprintf(arquivo_mapa,"%*c%*c\n",c-1,'|',400-c-1,'a');
    }  else if(direc==-1){
        mapa[l][c] = 3;
        fprintf(arquivo_mapa,"%*c%*c\n",199,'|',200,'a');
    }
    pos[p]++;



}


int main(){
    
  
    arquivo_mapa = fopen("mapa", "w");


    for(int i=0;i<200;i++){
        for(int j=0;j<400;j++){
            //fprintf(arquivo_mapa,(j==0 || i==0 || j==399)?"a":" ");
            fprintf(arquivo_mapa," ");
        }
        fprintf(arquivo_mapa,"\n");
    }

    for(int i=0;i<10;i++){
        preenche_mapa(1);
        //sleep(1);

    }
    // printf("  ");
    
    // fseek(arquivo_mapa,-200,SEEK_CUR);
    // fprintf(arquivo_mapa,"|");
    // for(int i=1;i<10;i++){
    //     fseek(arquivo_mapa,-402,SEEK_CUR);
    //     fprintf(arquivo_mapa,"|");
    //     sleep(3);

    // }



    fprintf(arquivo_mapa,"----------------------------------------------------------\n--------------------------------------------\n");
    
    for(int i=0;i<400;i++){
        for(int j=0;j<400;j++){
            if(mapa[i][j]==3){
                fprintf(arquivo_mapa,"V");
            } else{
                fprintf(arquivo_mapa," ");
            }
        }
        fprintf(arquivo_mapa,"\n");
    }
    fclose(arquivo_mapa);

    return 0;
}