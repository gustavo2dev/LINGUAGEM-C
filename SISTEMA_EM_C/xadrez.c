#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 8

char tabuleiro[TAM][TAM];
int dificuldade; // 1 facil 2 medio 3 dificil

void iniciarTabuleiro() {

    char inicio[TAM][TAM] = {
        {'r','n','b','q','k','b','n','r'},
        {'p','p','p','p','p','p','p','p'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'.','.','.','.','.','.','.','.'},
        {'P','P','P','P','P','P','P','P'},
        {'R','N','B','Q','K','B','N','R'}
    };

    for(int i=0;i<TAM;i++)
        for(int j=0;j<TAM;j++)
            tabuleiro[i][j] = inicio[i][j];
}

void mostrarTabuleiro() {

    printf("\n   0 1 2 3 4 5 6 7\n");

    for(int i=0;i<TAM;i++) {

        printf("%d  ",i);

        for(int j=0;j<TAM;j++) {
            printf("%c ", tabuleiro[i][j]);
        }

        printf("\n");
    }
}

int movimentoValido(int x1,int y1,int x2,int y2,int jogador) {

    if(x2 < 0 || x2 >= 8 || y2 < 0 || y2 >= 8)
        return 0;

    char p = tabuleiro[x1][y1];

    if(p == '.')
        return 0;

    if(jogador == 1 && !(p >= 'A' && p <= 'Z'))
        return 0;

    if(jogador == 2 && !(p >= 'a' && p <= 'z'))
        return 0;

    return 1;
}

void moverPeca(int x1,int y1,int x2,int y2) {

    tabuleiro[x2][y2] = tabuleiro[x1][y1];
    tabuleiro[x1][y1] = '.';

}

int valorPeca(char p){

    if(p=='P'||p=='p') return 1;
    if(p=='N'||p=='n') return 3;
    if(p=='B'||p=='b') return 3;
    if(p=='R'||p=='r') return 5;
    if(p=='Q'||p=='q') return 9;

    return 0;
}

void jogadaFacil(){

    int x1,y1,x2,y2;

    while(1){

        x1 = rand()%8;
        y1 = rand()%8;

        if(tabuleiro[x1][y1] >= 'a' && tabuleiro[x1][y1] <= 'z'){

            x2 = x1 + (rand()%3 -1);
            y2 = y1 + (rand()%3 -1);

            if(movimentoValido(x1,y1,x2,y2,2)){

                moverPeca(x1,y1,x2,y2);

                printf("\nComputador jogou (facil)\n");
                break;
            }
        }
    }
}

void jogadaMedia(){

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(tabuleiro[i][j] >= 'a' && tabuleiro[i][j] <= 'z'){

                for(int dx=-1;dx<=1;dx++){
                    for(int dy=-1;dy<=1;dy++){

                        int x=i+dx;
                        int y=j+dy;

                        if(x>=0 && x<8 && y>=0 && y<8){

                            if(tabuleiro[x][y] >= 'A' && tabuleiro[x][y] <= 'Z'){

                                if(movimentoValido(i,j,x,y,2)){

                                    moverPeca(i,j,x,y);
                                    printf("\nComputador capturou uma peça (medio)\n");
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    jogadaFacil();
}

void jogadaDificil(){

    int melhorValor=0;
    int bx1,by1,bx2,by2;

    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){

            if(tabuleiro[i][j] >= 'a' && tabuleiro[i][j] <= 'z'){

                for(int dx=-1;dx<=1;dx++){
                    for(int dy=-1;dy<=1;dy++){

                        int x=i+dx;
                        int y=j+dy;

                        if(x>=0 && x<8 && y>=0 && y<8){

                            if(tabuleiro[x][y] >= 'A' && tabuleiro[x][y] <= 'Z'){

                                int valor = valorPeca(tabuleiro[x][y]);

                                if(valor > melhorValor){

                                    if(movimentoValido(i,j,x,y,2)){

                                        melhorValor = valor;

                                        bx1=i;
                                        by1=j;
                                        bx2=x;
                                        by2=y;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if(melhorValor>0){

        moverPeca(bx1,by1,bx2,by2);

        printf("\nComputador fez melhor captura (dificil)\n");

    }else{

        jogadaMedia();
    }

}

void jogadaComputador(){

    if(dificuldade==1)
        jogadaFacil();

    if(dificuldade==2)
        jogadaMedia();

    if(dificuldade==3)
        jogadaDificil();
}

int main(){

    int x1,y1,x2,y2;

    srand(time(NULL));

    iniciarTabuleiro();

    printf("Escolha dificuldade\n");
    printf("1 Facil\n2 Medio\n3 Dificil\n");

    scanf("%d",&dificuldade);

    while(1){

        mostrarTabuleiro();

        printf("\nSeu movimento\n");

        printf("Origem (linha coluna): ");
        scanf("%d %d",&x1,&y1);

        printf("Destino (linha coluna): ");
        scanf("%d %d",&x2,&y2);

        if(movimentoValido(x1,y1,x2,y2,1)){

            moverPeca(x1,y1,x2,y2);

        }else{

            printf("Movimento invalido\n");
            continue;
        }

        jogadaComputador();
    }
}