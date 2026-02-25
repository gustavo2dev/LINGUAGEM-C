#include <stdio.h>

int main(){

    int i;
    float valor1[4], valor2[4], sub1[4];

    for (i = 0; i < 4; i++){

        printf("Digite um número da posição: [%i]\n", i);
        scanf("%f", &valor1[i]);

        printf("Digite um número da posição: [%i]\n", i);
        scanf("%f", &valor2[i]);

        sub1[i] = valor1[i] - valor2[i];

    }

    for ( i = 0; i < 4; i++){
     printf("O resultado da subtração dos vetores é: %.3f \n", sub1[i]);   
    }

    return 0;
}