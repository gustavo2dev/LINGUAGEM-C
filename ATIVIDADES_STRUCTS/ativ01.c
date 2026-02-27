#include <stdio.h>
struct pessoa
{
    char nome[50];
    float peso;
    float altura;
    float IMC;
};
int main(){
    struct pessoa p1;

    printf("Digite seu nome: \n");
    scanf("%s", p1.nome);

    printf("Digite seu peso: \n");
    scanf("%f", &p1.peso);

    printf("Digite sua altura: \n");
    scanf("%f", &p1.altura);

    printf("\n");

    p1.IMC = p1.peso / (p1.altura * p1.altura);

    if (p1.IMC < 18.5)
    {
        printf("PESO BAIXO!!!!\n");
    }
    else if (p1.IMC < 25.0)
    {
        printf("PESO NORMAL!!!!\n");
    }
    else if (p1.IMC < 30.0)
    {
        printf("SOBREPESO!!!!\n");
    }
    else if (p1.IMC < 35.0)
    {
        printf("OBESIDADE 1 !!!!\n");
    }
    else if (p1.IMC < 40.0)
    {
        printf("OBESIDADE 2 !!!!\n");
    }
    else
    {
        printf("OBESIDADE 3 !!!!\n");
    }

    printf("O IMC do(a) %s é %.3f sendo sua altura %.2f e seu peso %.2f \n", p1.nome, p1.IMC, p1.altura, p1.peso);

    return 0;
}