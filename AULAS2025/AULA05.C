#include <stdio.h>

int main() {
    int idade, contador = 0;
    float soma = 0;

    do {
        printf("Digite uma idade (negativa para parar): ");
        scanf("%d", &idade);

        if (idade >= 0) {
            soma += idade;
            contador++;
        }

    } while (idade >= 0);

    if (contador > 0) {
        printf("\nTotal de pessoas cadastradas: %d", contador);
        printf("\nMédia das idades: %.2f\n", soma / contador);
    } else {
        printf("\nNenhuma idade válida foi cadastrada.\n");
    }

    return 0;
}
