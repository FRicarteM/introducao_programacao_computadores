#include <stdio.h>
#include <string.h>

// Enum com todas as direções possíveis
typedef enum
{
    FRENTE,
    TRAS,
    ESQUERDA,
    DIREITA,
    DSE, // Diagonal Superior Esquerda
    DSD, // Diagonal Superior Direita
    DIE, // Diagonal Inferior Esquerda
    DID, // Diagonal Inferior Direita
    DC,  // Mv Cavalo Direita Cima
    DB,  // Mv Cavalo Direita Baixo
    DM,  // Mv Cavalo Direita Meio
    EC,  // Mv Cavalo Esquerda Cima
    EB,  // Mv Cavalo Esquerda Baixo
    EM,  // Mv Cavalo Esquerda Meio
    INVALIDA
} Direcao;

// Função que converte string/dígito em enum
Direcao lerDirecao(const char *entrada)
{
    if (strcmp(entrada, "F") == 0)
        return FRENTE;
    if (strcmp(entrada, "T") == 0)
        return TRAS;
    if (strcmp(entrada, "E") == 0)
        return ESQUERDA;
    if (strcmp(entrada, "D") == 0)
        return DIREITA;
    if (strcmp(entrada, "DSE") == 0)
        return DSE;
    if (strcmp(entrada, "DSD") == 0)
        return DSD;
    if (strcmp(entrada, "DIE") == 0)
        return DIE;
    if (strcmp(entrada, "DID") == 0)
        return DID;
    if (strcmp(entrada, "DC") == 0)
        return DC;
    if (strcmp(entrada, "DB") == 0)
        return DB;
    if (strcmp(entrada, "DM") == 0)
        return DM;
    if (strcmp(entrada, "EC") == 0)
        return EC;
    if (strcmp(entrada, "EB") == 0)
        return EB;
    if (strcmp(entrada, "EM") == 0)
        return EM;
    return INVALIDA;
}

// Função auxiliar para imprimir nome da direção
const char *nomeDirecao(Direcao direcao)
{
    switch (direcao)
    {
    case FRENTE:
        return "Frente";
    case TRAS:
        return "Trás";
    case ESQUERDA:
        return "Esquerda";
    case DIREITA:
        return "Direita";
    case DSE:
        return "Diagonal Superior Esquerda";
    case DSD:
        return "Diagonal Superior Direita";
    case DIE:
        return "Diagonal Inferior Esquerda";
    case DID:
        return "Diagonal Inferior Direita";
    case DC:
        return "Movimento Cavalo Direita Cima";
    case DB:
        return "Movimento Cavalo Direita Baixo";
    case DM:
        return "Movimento Cavalo Direita Meio";
    case EC:
        return "Movimento Cavalo Esquerda Cima";
    case EB:
        return "Movimento Cavalo Esquerda Baixo";
    case EM:
        return "Movimento Cavalo Esquerda Meio";
    default:
        return "Inválida";
    }
}

void moverBispoRecursivo(int x, int y, Direcao dir, int passosRestantes)
{
    if (passosRestantes == 0)
    {
        printf("Bispo parou em (%d, %d)\n", x, y);
        return; // condição de parada
    }

    // Loop externo: deslocamento vertical
    for (int i = 0; i < 1; i++)
    {
        // Loop interno: deslocamento horizontal
        for (int j = 0; j < 1; j++)
        {
            switch (dir)
            {
            case DSE:
                x--;
                y++;
                break;
            case DSD:
                x++;
                y++;
                break;
            case DIE:
                x--;
                y--;
                break;
            case DID:
                x++;
                y--;
                break;
            default:
                break;
            }
        }
    }

    printf("  Bispo moveu para (%d, %d)\n", x, y);

    // chamada recursiva — continua o movimento
    moverBispoRecursivo(x, y, dir, passosRestantes - 1);
}

// Funções de movimento
void moverTorre(int casas, Direcao dir)
{
    printf("\nTorre moveu para %s por %d casas:\n", nomeDirecao(dir), casas);
    for (int i = 1; i <= casas; i++)
        printf("  Passo %d: Torre moveu uma casa para %s\n", i, nomeDirecao(dir));
}

void moverBispo(int casas, Direcao dir)
{
    int x = 4, y = 4; // posição inicial no centro

    printf("\nBispo começa em (%d, %d)\n", x, y);
    printf("Movendo-se para %s...\n", nomeDirecao(dir));

    moverBispoRecursivo(x, y, dir, casas);
}

void moverRainha(int casas, Direcao dir)
{
    printf("\nRainha moveu para %s por %d casas:\n", nomeDirecao(dir), casas);
    for (int i = 1; i <= casas; i++)
        printf("  Passo %d: Rainha moveu uma casa para %s\n", i, nomeDirecao(dir));
}

void moverCavalo(Direcao dir)
{
    int x = 0, y = 0; // posição inicial

    printf("\nCavalo inicia em (%d, %d)\n", x, y);
    printf("Movendo para %s...\n", nomeDirecao(dir));

    // loops aninhados simulando o salto em L
    for (int passo = 1; passo <= 3; passo++)
    {
        switch (dir)
        {
        case DC:
        case DB:
        case DM:
            x++; // 3 passos à direita
            break;
        case EC:
        case EB:
        case EM:
            x--; // 3 passos à esquerda
            break;
        }
        printf("  Passo %d → (%d, %d)\n", passo, x, y);
    }

    // Agora o “pé” do L — o desvio vertical/horizontal
    for (int i = 0; i < 1; i++)
    {
        switch (dir)
        {
        case DC:
        case EC:
            y++; // 1 para cima
            break;
        case DB:
        case EB:
            y--; // 1 para baixo
            break;
        case DM:
            y += 2; // movimento meio (2 cima)
            break;
        case EM:
            y += 2; // movimento meio (2 cima)
            break;
        }
        printf("  Desvio final → (%d, %d)\n", x, y);
    }

    printf("Cavalo terminou em (%d, %d)\n", x, y);
}

int main()
{
    int opcao, casas;
    char entrada[4];
    Direcao direcao;

    printf("=== Peças de Xadrez Elegíveis ===\n\n");
    printf("1. Torre\n");
    printf("2. Bispo\n");
    printf("3. Rainha\n");
    printf("4. Cavalo\n");
    printf("\nEscolha a peça que deseja mover: ");
    scanf("%d", &opcao);

    if (opcao == 4)
    {
        casas = 0; // Cavalo não usa número de casas
    }
    else
    {
        printf("\nQuantas casas deseja mover? ");
        scanf("%d", &casas);
    }

    switch (opcao)
    {
    case 1:
        printf("\n--- Torre ---\n");
        printf("Direções possíveis: F (frente), T (trás), E (esquerda), D (direita)\n");
        printf("Escolha a direção: ");
        scanf("%s", entrada);
        direcao = lerDirecao(entrada);
        if (direcao == FRENTE || direcao == TRAS || direcao == ESQUERDA || direcao == DIREITA)
            moverTorre(casas, direcao);
        else
            printf("Direção inválida para a Torre!\n");
        break;

    case 2:
        printf("\n--- Bispo ---\n");
        printf("Direções possíveis: DSE (diagonal SE), DSD (diagonal SD), DIE (diagonal IE), DID (diagonal ID)\n");
        printf("Escolha a direção: ");
        scanf("%s", entrada);
        direcao = lerDirecao(entrada);
        if (direcao == DSE || direcao == DSD || direcao == DIE || direcao == DID)
            moverBispo(casas, direcao);
        else
            printf("Direção inválida para o Bispo!\n");
        break;

    case 3:
        printf("\n--- Rainha ---\n");
        printf("Direções possíveis: F (frente), T (trás), E (esquerda), D (direita), DSE (diagonal SE), DSD (diagonal SD), DIE (diagonal IE), DID (diagonal ID)\n");
        printf("Escolha a direção: ");
        scanf("%s", entrada);
        direcao = lerDirecao(entrada);
        if (direcao != INVALIDA)
            moverRainha(casas, direcao);
        else
            printf("Direção inválida para a Rainha!\n");
        break;

    case 4:
        printf("\n--- Cavalo ---\n");
        printf("Direções possíveis: DC (diagonal cima), DB (diagonal baixo), DM (diagonal meio), EC (esquerda cima), EB (esquerda baixo), EM (esquerda meio)\n");
        printf("Escolha a direção: ");
        scanf("%s", entrada);
        direcao = lerDirecao(entrada);
        if (direcao == DC || direcao == DB || direcao == DM || direcao == EC || direcao == EB || direcao == EM)
            moverCavalo(direcao);
        else
            printf("Direção inválida para o Cavalo!\n");
        break;

    default:
        printf("Opção inválida.\n");
        break;
    }

    printf("\nFim da simulação.\n");
    return 0;
}
