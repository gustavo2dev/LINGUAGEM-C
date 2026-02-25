#include <stdio.h>

int main() {
    int i;
    int valor1[4], valor2[4], Resul[8];
    int control = 0;

    for (i = 0; i < 4; i++) {
        printf("Digite um número da posição: [%d]\n", i);
        scanf("%d", &valor1[i]);

        printf("Digite um número da posição: [%d]\n", i);
        scanf("%d", &valor2[i]);

        if (valor1[i] % 2 == 0) {
            Resul[control++] = valor1[i];
        }
        if (valor2[i] % 2 == 0) {
            Resul[control++] = valor2[i];
        }
    }

    printf("Os valores pares armazenados são:\n");
    for (i = 0; i < control; i++) {
        printf("%d\n", Resul[i]);
    }

    return 0;
}