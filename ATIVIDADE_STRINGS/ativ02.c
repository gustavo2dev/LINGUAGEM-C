#include <stdio.h>
#include <string.h>

int main(){
    char palavra[200];
    int a = 0, e = 0, i = 0, o = 0, u = 0;

    printf("Digite uma palavra para saber quantas vogais tem: ");
    scanf("%s", palavra);

    int n = strlen(palavra);

    for (int j = 0; j < n; j++)
    {
        if (palavra[j] == 'a')
            a++;
        else if (palavra[j] == 'e')
            e++;
        else if (palavra[j] == 'i')
            i++;
        else if (palavra[j] == 'o')
            o++;
        else if (palavra[j] == 'u')
            u++;
    }

    printf("A sua palavra tem: \n");
    printf("A => %i\n", a);
    printf("E => %i\n", e);
    printf("I => %i\n", i);
    printf("O => %i\n", o);
    printf("U => %i\n", u);

    return 0;
}