#include <stdio.h>

int main() {
    int numero, maior, menor;
    int primeiro = 1; // Para identificar o primeiro número digitado

    do {
        printf("Digite um número (0 para parar): ");
        scanf("%d", &numero);

        if (numero != 0) {
            if (primeiro) {
                maior = numero;
                menor = numero;
                primeiro = 0;
            } else {
                if (numero > maior) {
                    maior = numero;
                }
                if (numero < menor) {
                    menor = numero;
                }
            }
        }

    } while (numero != 0);

    if (! primeiro) {
        printf("\nMaior número digitado: %d", maior);
        printf("\nMenor número digitado: %d\n", menor);
    } else {
        printf("\nNenhum número foi digitado.\n");
    }

    return 0;
}
