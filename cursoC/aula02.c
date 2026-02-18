#include <stdio.h>

int main() {

    // =========================
    // TIPOS INTEIROS
    // =========================

    int idade = 25;           
    // inteiro comum
    // mascara: %d

    short pequeno = 10;       
    // inteiro menor
    // mascara: %hd

    long grande = 100000;     
    // inteiro grande
    // mascara: %ld

    long long gigantesco = 9999999999;
    // inteiro muito grande
    // mascara: %lld


    // =========================
    // TIPOS DECIMAIS
    // =========================

    float altura = 1.75f;     
    // número decimal simples
    // mascara: %f

    double peso = 70.5;       
    // decimal mais preciso
    // mascara: %lf

    long double super_preciso = 3.1415926535;
    // decimal super preciso
    // mascara: %Lf


    // =========================
    // CARACTERES
    // =========================

    char letra = 'A';         
    // armazena um caractere
    // mascara: %c


    // =========================
    // TEXTO (STRING)
    // =========================

    char nome[] = "Gustavo";  
    // string é vetor de char
    // mascara: %s


    // =========================
    // BOOLEANO (C99)
    // =========================

    _Bool ligado = 1;         
    // 0 = falso | 1 = verdadeiro
    // mascara: %d


    // =========================
    // EXEMPLO DE USO
    // =========================

    printf("Idade: %d\n", idade);
    printf("Altura: %.2f\n", altura);
    printf("Nome: %s\n", nome);

    return 0;
}
