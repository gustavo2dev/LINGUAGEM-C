#include <stdio.h>

int main(){

    int num;
    
    printf("Digite seu número para saber se é ímpar ou par");
    scanf("%i", &num);

    if(num == 2){
        printf("Este é um número par !!!");
    }
    else{
        printf("Seu número é ímpar !!!!!");
    }

    return 0;
}