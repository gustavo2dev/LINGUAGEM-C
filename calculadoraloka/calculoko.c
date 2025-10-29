#include <stdio.h>

int main(){
    int n1, n2, test;
    char tecla = '\0';

    printf("digite algum valor: ");
    scanf("%i", &n1);
    printf("digite outro valor: ");
    scanf("%i", &n2);

    
    while ()
    {

        test = n1 + n2;
        test = test + 1;

        printf("Digite Ç para SAIR!!!");
        scanf("%C",&tecla);

        if (tecla == 'C')
        {
            printf("Saindo do loop!!!");
            break;
        }
    }
    
    printf("Os valores digitados resutou em %i", test);

    return 0;
}