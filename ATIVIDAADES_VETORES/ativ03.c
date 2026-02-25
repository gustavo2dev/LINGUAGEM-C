#include <stdio.h>

int main() {
    int n, i;
    int vetor[n];

    printf("Quantos numeros voce deseja inserir? ");
    scanf("%d", &n);

    printf("Digite %d numeros:\n", n);
    for(i = 0; i < n; i++) {
        printf("Elemento %d: ", i + 1);
        scanf("%d", &vetor[i]);
    }

    // Apresentando os dados na ordem inversa
    printf("\nOs numeros na ordem inversa sao:\n");
    for(i = n - 1; i >= 0; i--) {
        printf("%d ", vetor[i]);
    }
    printf("\n");

    return 0;
}