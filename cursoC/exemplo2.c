#include <stdio.h>
#include <stdlib.h> // biblioteca onde fica o abs()

int main() {

    int numero;

    printf("Digite um numero (positivo ou negativo): ");
    scanf("%d", &numero);

    // abs() retorna o valor absoluto do numero
    int resultado = abs(numero);

    printf("O valor absoluto de %d em: %d\n", numero, resultado);

    return 0;
}
