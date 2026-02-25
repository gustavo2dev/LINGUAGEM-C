#include <stdio.h>

int main(){

    int i;
    int valor1[4], valor2[4], par1[4], parResul[4];

    for (i = 0; i < 4; i++){

        printf("Digite um número da posição: [%i]\n", i);
        scanf("%d", &valor1[i]);

        printf("Digite um número da posição: [%i]\n", i);
        scanf("%d", &valor2[i]);

        par1[i] = valor1[i] % 2;

        if(par1[i] = 0){
            parResul[i] = par1[i];
        }
    }

    for(i = 0; i < 4; i++){
        printf("Os valores pares armazenados são: ");
        printf("%i \n", parResul[i]);
    }

    return 0;
}