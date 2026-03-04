#include <stdio.h>
#include <string.h>

int main(){
    char palavra[200], letra;
    char *t;

    printf("Digite uma string: \n");
    scanf("%s", palavra);

    printf("Digite uma letra para localiza-la na string: \n");
    scanf(" %c", &letra);

    t = strrchr(palavra, letra);

     if (t != NULL)
     {
        printf("A ultima ocorrencia de '%c' em '%s' esta na posicao %ld\n", letra, palavra, t - palavra + 1);
     }else{
        printf("O caractere '%c' não esta localizado em '%s'\n", letra, palavra);
     }

    return 0;
}