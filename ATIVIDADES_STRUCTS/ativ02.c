#include <stdio.h>

struct jogo
{
    char data[15];
    char mandante[30];
    char visitante[30];
    int gols_mandante;
    int gols_visitante;
};

int main()
{
    struct jogo jogos[5];
    int i;

    for (i = 0; i < 5; i++)
    {
        
        printf("Data (DD/MM/YYYY): ");
        scanf("%s", jogos[i].data);
        
        printf("Time mandante: ");
        scanf("%s", jogos[i].mandante);
        
        printf("Time visitante: ");
        scanf("%s", jogos[i].visitante);
        
        printf("Gols do mandante: ");
        scanf("%d", &jogos[i].gols_mandante);
        
        printf("Gols do visitante: ");
        scanf("%d", &jogos[i].gols_visitante);
    }
    
    for (i = 0; i < 5; i++)
    {
        printf("Data: %s\n", jogos[i].data);
        printf("%s %d x %d %s\n", jogos[i].mandante, jogos[i].gols_mandante, 
               jogos[i].gols_visitante, jogos[i].visitante);
    
        if (jogos[i].gols_mandante > jogos[i].gols_visitante)
        {
            printf("Resultado: %s VENCEU!\n", jogos[i].mandante);
        }
        else if (jogos[i].gols_visitante > jogos[i].gols_mandante)
        {
            printf("Resultado: %s VENCEU!\n", jogos[i].visitante);
        }
        else
        {
            printf("Resultado: EMPATE!\n");
        }
    }

    return 0;
}
