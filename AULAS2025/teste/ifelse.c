
#include <stdio.h>

int main(){
    int val1, val2, resul, decis;

    printf("Digite 1 para somar, 2 para subitrair.");
    scanf("%i", &val2);

    if(decis == 1){

        printf("Você escolheu soma, digite o primeiro valor:");
        scanf("%i", &val1);

        printf("Digite o segundo valor:");
        scanf("%i", &val2);

        resul = val1 + val2;    
        
        printf("O resultado da soma é %i",resul);
    }
     else if(decis == 2){

         printf("Você escolheu subitrair, digite o primeiro valor:");
        scanf("%i", &val1);

        printf("Digite o segundo valor:");
        scanf("%i", &val2);

        resul = val1 + val2;    
        
        printf("O resultado da subitração é %i",resul);
    }    

    else {

       printf("Digite um valor entre 1 e 2.");
    }

    return 0;
}