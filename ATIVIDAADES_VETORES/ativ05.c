#include <stdio.h>

int main() {
    int v[8], n[8], m;
    int i, j;

    for (i = 0; i < 8; i++) {

        printf("Digite um número inteiro positivo para a posição [%d]: ", i + 1);
        if (scanf("%d", &n[i]) != 1) {
            while (getchar() != '\n');
            n[i] = 0;
        }

        if (n[i] > 0)
        {
            v[i] = n[i];
        } else {
            printf("INVALIDO!!!!\n");
            v[i] = 0; 
        }
    }

    printf("Digite um inteiro positivo para saber se esta no vetor: ");
    if (scanf("%d", &m) != 1) {
        printf("Entrada inválida.\n");
        return 0;
    }

    if (m > 0)
    {
        int encontrado = 0;
        for (j = 0; j < 8; j++)
        {
            if (m == v[j])
            {
                printf("PARABÉNS!!! O NÚMERO DIGITADO %d ESTA CONTIDO NO VETOR!!!\n", m);
                encontrado = 1;
                break;
            }
        }
        if (!encontrado) {
            printf("!!!!ATENÇÃO!!!! O VALOR DIGITADO NÃO ESTA CONTIDO NO VETOR\n");
        }
    } else {
        printf("INVALIDO!!!!1\n");
    }

    return 0;
}
