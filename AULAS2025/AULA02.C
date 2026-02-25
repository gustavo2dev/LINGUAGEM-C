#include <stdio.h>
 //Caixa de Loja
int main(){

    int valorDigitado;
    int soma = 0;

    printf("Digite um número para somar: (Digite 0 para parar)");

    do
    {
        printf("Digite um número: ");
        scanf("%i", &valorDigitado);

        soma += valorDigitado;
        

    } while (valorDigitado != 0);
    
    printf("A soma dos valore digitados são %i", soma);

    return 0;
}