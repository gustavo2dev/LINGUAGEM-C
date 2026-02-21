
#include <stdio.h>

int main() {
int numeros[5];
int i;

printf("Digite 5 numeros inteiros:\n");
for(i = 0; i < 5; i++) {
printf("Posicao [%i]: ", i);
scanf("%i", &numeros[i]);
}

printf("Os numeros digitados foram:\n");
for(i = 0; i < 5; i++) {
printf("%i ", numeros[i]);
}
return 0;
}