#include <stdio.h>
#include <string.h>

int main(){
    char nome[50], nomeInvertido[50];

    printf("Digite um nome para inverter: ");
    scanf("%s", nome);

    int n = strlen(nome);

    for (int i = n - 1, j = 0; i >= 0; i--, j++)
    {
        nomeInvertido[j] = nome[i];
    }
    nomeInvertido[n] = '\0';

    printf("Nome original: %s\n", nome);
    printf("Nome invertido: %s\n", nomeInvertido);

    return 0;
}