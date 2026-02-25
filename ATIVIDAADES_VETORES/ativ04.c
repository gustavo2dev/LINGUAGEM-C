#include <stdio.h>

int main(){
    
    int vetor1[6];
    int soma = 0;
    int i;

    for (i = 0; i < 6; i++)
    {
        printf("Escreva o valor da posição [%i]:", i);
        scanf("%i", &vetor1[i]);

        soma = soma + vetor1[i];
    }

    printf("\nMédia dos valores são: %d \n", soma / 6);

    printf("Valores do vetor são: ");

    int min = vetor1[0], max = vetor1[0];

    for (i = 0; i < 6; i++)
    {
        printf("%d ", vetor1[i]);

        if (vetor1[i] > max) max = vetor1[i];
        if (vetor1[i] < min) min = vetor1[i];
    }

    printf("\nMaior valor: %d", max);
    printf("\nMenor valor: %d\n", min);
 
    return 0;
}