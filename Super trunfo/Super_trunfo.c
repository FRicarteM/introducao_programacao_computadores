#include <stdio.h>
#include <string.h>

// Estrutura das cartas
struct Carta
{
    char cidade[50];
    int expectativaVida, pib, populacao, densidadeDemografica;
};

// Função que recebe as variáveis e retorna uma Carta.
struct Carta criaCarta(const char *cidade, int expectativaVida, int pib, int populacao, int densidadeDemografica)
{
    struct Carta carta;
    strcpy(carta.cidade, cidade);
    carta.expectativaVida = expectativaVida;
    carta.pib = pib;
    carta.populacao = populacao;
    carta.densidadeDemografica = densidadeDemografica;
    return carta;
}

// Função para comparar atributos.
void compararAtributo(struct Carta c1, struct Carta c2, int atributo)
{
    switch (atributo)
    {
    case 1: // Expectativa de vida
        (c1.expectativaVida > c2.expectativaVida) ? printf("\n%s, com %d anos, possui a maior expectativa de vida, do que %s, com %d anos.\n", c1.cidade, c1.expectativaVida, c2.cidade, c2.expectativaVida) : (c1.expectativaVida < c2.expectativaVida) ? printf("\n%s, com %d anos, possui a maior expectativa de vida, do que %s, com %d anos.\n", c2.cidade, c2.expectativaVida, c1.cidade, c1.expectativaVida)
                                                                                                                                                                                                                                                         : printf("\nEmpate na expectativa de vida!\n");
        break;

    case 2: // PIB
        (c1.pib > c2.pib) ? printf("\n%s, com R$ %d bilhões, possui o maior PIB, do que %s, com R$ %d bilhões.\n", c1.cidade, c1.pib, c2.cidade, c2.pib) : (c1.pib < c2.pib) ? printf("\n%s, com R$ %d bilhões, possui o maior PIB, do que %s, com R$ %d bilhões.\n", c2.cidade, c2.pib, c1.cidade, c1.pib)
                                                                                                                                                                             : printf("\nEmpate no PIB!\n");
        break;

    case 3: // População
        (c1.populacao > c2.populacao) ? printf("\n%s, com %d habitantes, possui a maior população, do que %s, com %d habitantes.\n", c1.cidade, c1.populacao, c2.cidade, c2.populacao) : (c1.populacao < c2.populacao) ? printf("\n%s, com %d habitantes, possui a maior população, do que %s, com %d habitantes.\n", c2.cidade, c2.populacao, c1.cidade, c1.populacao)
                                                                                                                                                                                                                       : printf("\nEmpate na população!\n");
        break;

    case 4: // Densidade demográfica
        (c1.densidadeDemografica < c2.densidadeDemografica) ? printf("\n%s, com %d habitantes por km², possui a menor densidade demográfica, do que %s, com %d habitantes por km².\n", c1.cidade, c1.densidadeDemografica, c2.cidade, c2.densidadeDemografica) : (c1.densidadeDemografica > c2.densidadeDemografica) ? printf("\n%s, com %d habitantes por km², possui a menor densidade demográfica, do que %s, com %d habitantes por km².\n", c2.cidade, c2.densidadeDemografica, c1.cidade, c1.densidadeDemografica)
                                                                                                                                                                                                                                                                                                                     : printf("\nEmpate na densidade demográfica!\n");
        break;

    default:
        printf("\nAtributo inválido!\n");
        break;
    }
}

// Função para soma dos atributos.
int somaAtributo(struct Carta c, int atributo1, int atributo2)
{
    int soma = 0;

    // primeiro atributo
    switch (atributo1)
    {
    case 1:
        soma += c.expectativaVida;
        break;
    case 2:
        soma += c.pib;
        break;
    case 3:
        soma += c.populacao;
        break;
    case 4:
        soma += c.densidadeDemografica;
        break;
    default:
        printf("Atributo 1 inválido!\n\n");
        break;
    }

    // segundo atributo
    switch (atributo2)
    {
    case 1:
        soma += c.expectativaVida;
        break;
    case 2:
        soma += c.pib;
        break;
    case 3:
        soma += c.populacao;
        break;
    case 4:
        soma += c.densidadeDemografica;
        break;
    default:
        printf("Atributo 2 inválido!\n\n");
        break;
    }

    return soma;
}

int main()
{

    int jogarNovamente = 0;

    while (jogarNovamente == 0)
    {

        // Instância de uma carta.
        struct Carta carta1, carta2;

        // Variáveis para armazenar os dados da carta.
        char cidade[50];
        int expectativaVida, pib, populacao, densidadeDemografica;

        // --- Carta 1 ---
        // Solicita os dados da carta ao usuário.
        printf("Digite o nome da carta: ");
        fgets(cidade, sizeof(cidade), stdin);

        // remover o '\n' que o fgets adiciona,
        cidade[strcspn(cidade, "\n")] = '\0';

        printf("Digite a expectativa de vida: ");
        scanf("%d", &expectativaVida);

        printf("Digite o PIB: ");
        scanf("%d", &pib);

        printf("Digite a população: ");
        scanf("%d", &populacao);

        printf("Digite a densidade demográfica: ");
        scanf("%d", &densidadeDemografica);

        // Cria a carta com os dados fornecidos.
        carta1 = criaCarta(cidade, expectativaVida, pib, populacao, densidadeDemografica);

        // Limpa o buffer antes do próximo fgets.
        getchar();

        // --- Carta 2 ---
        printf("\nDigite o nome da carta 2: ");
        fgets(cidade, sizeof(cidade), stdin);
        cidade[strcspn(cidade, "\n")] = '\0';

        printf("Expectativa de vida: ");
        scanf("%d", &expectativaVida);

        printf("PIB: ");
        scanf("%d", &pib);

        printf("População: ");
        scanf("%d", &populacao);

        printf("Densidade demográfica: ");
        scanf("%d", &densidadeDemografica);

        carta2 = criaCarta(cidade, expectativaVida, pib, populacao, densidadeDemografica);

        int atributo1, atributo2;

        // Loop infinito até o jogador escolher atributos válidos.
        while (1)
        {
            printf("\nEscolha dois atributos para comparar:\n");
            printf("1. Expectativa de vida\n");
            printf("2. PIB\n");
            printf("3. População\n");
            printf("4. Densidade demográfica\n");
            printf("\nDigite o número dos atributos: \n");

            scanf("%d %d", &atributo1, &atributo2);

            // Validação dos atributos.
            if (atributo1 < 1 || atributo1 > 4 || atributo2 < 1 || atributo2 > 4)
            {
                printf("\nUm ou ambos os atributos são inválidos! Tente novamente.\n");
                getchar();
                continue;
            }

            if (atributo1 == atributo2)
            {
                printf("\nOs atributos devem ser diferentes! Tente novamente.\n");
                getchar();
                continue;
            }

            // Se chegou aqui, atributos são válidos — sai do loop.
            break;
        }

        // Exibe a comparação dos atributos escolhidos.
        printf("\nResultado da Comparação dos atributos escolhidos:\n\n");
        compararAtributo(carta1, carta2, atributo1);
        compararAtributo(carta1, carta2, atributo2);

        int somaCarta1 = somaAtributo(carta1, atributo1, atributo2);
        int somaCarta2 = somaAtributo(carta2, atributo1, atributo2);

        // Exibe o vencedor pela soma dos atributos.
        printf("\n\nResultado da soma dos atributos:\n\n");
        if (somaCarta1 > somaCarta2)
            printf("\n%s vence com a soma dos atributos: %d\n", carta1.cidade, somaCarta1);
        else if (somaCarta1 < somaCarta2)
            printf("\n%s vence com a soma dos atributos: %d\n", carta2.cidade, somaCarta2);
        else
            printf("\nEmpate na soma dos atributos: %d\n", somaCarta1);

        // Pergunta se quer jogar de novo.
        int escolha;

        printf("\nDeseja jogar novamente? (1 = sim, 0 = não): \n");

        scanf("%d", &escolha);
        getchar();

        if (escolha == 0)
            jogarNovamente = 1;
    }

    printf("\nJogo encerrado. Obrigado por jogar!\n");
    return 0;
}