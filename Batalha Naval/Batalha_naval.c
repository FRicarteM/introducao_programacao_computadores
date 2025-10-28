#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define TAM 10 // tamanho do tabuleiro

// enum para as linhas (A–J)
enum Linha
{
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8,
    J = 9
};

// Estrutura de um navio
struct Navio
{
    char simbolo;  // Letra do navio
    int tamanho;   // Quantas casas ocupa
    char nome[20]; // Nome do navio
};

// Protótipos
void inicializarTabuleiro(char tabuleiro[TAM][TAM]);
void exibirTabuleiro(char tabuleiro[TAM][TAM]);
int letraParaIndice(char letra);
int posicionarNavio(char tabuleiro[TAM][TAM], struct Navio navio);
int ataque(char tabuleiro[TAM][TAM]);
int contarRestantes(char tabuleiro[TAM][TAM]);

int main()
{
    char tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Navios do jogo
    struct Navio portaAvioes = {'P', 5, "Porta-aviões"};
    struct Navio encouracado = {'E', 4, "Encouraçado"};
    struct Navio cruzeiro = {'C', 3, "Cruzeiro"};
    struct Navio submarino = {'S', 2, "Submarino"};

    printf("=== BATALHA NAVAL ===\n");
    exibirTabuleiro(tabuleiro);

    // Posiciona os navios
    posicionarNavio(tabuleiro, portaAvioes);
    exibirTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, encouracado);
    exibirTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, cruzeiro);
    exibirTabuleiro(tabuleiro);

    posicionarNavio(tabuleiro, submarino);
    exibirTabuleiro(tabuleiro);

    printf("\nTodos os navios foram posicionados!\n");

    // Início da batalha
    int jogadas = 0;
    while (contarRestantes(tabuleiro) > 0)
    {
        jogadas++;
        printf("\n=== ATAQUE %d ===\n", jogadas);
        exibirTabuleiro(tabuleiro);
        ataque(tabuleiro);
    }

    printf("\nPARABÉNS! Você afundou todos os navios em %d jogadas!\n", jogadas);
    return 0;
}

// Inicializa o tabuleiro com '~'
void inicializarTabuleiro(char tabuleiro[TAM][TAM])
{
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '~';
}

// Exibe o tabuleiro formatado
void exibirTabuleiro(char tabuleiro[TAM][TAM])
{
    printf("\n    ");
    for (int j = 0; j < TAM; j++)
        printf("%d ", j);
    printf("\n");

    for (int i = 0; i < TAM; i++)
    {
        printf(" %c  ", 'A' + i);
        for (int j = 0; j < TAM; j++)
            printf("%c ", tabuleiro[i][j]);
        printf("\n");
    }
    printf("\n");
}

// Converte uma letra (A–J) em índice (0–9)
int letraParaIndice(char letra)
{
    letra = toupper(letra);
    if (letra >= 'A' && letra <= 'J')
        return letra - 'A';
    return -1;
}

// Posiciona um navio no tabuleiro
int posicionarNavio(char tabuleiro[TAM][TAM], struct Navio navio)
{
    int linha, coluna;
    char coordLetra;
    char orientacao;

    while (1)
    {
        printf("\nPosicione o %s (tamanho %d)\n", navio.nome, navio.tamanho);
        printf("Informe a coordenada inicial (ex: A5): ");
        scanf(" %c%d", &coordLetra, &coluna);
        linha = letraParaIndice(coordLetra);

        if (linha == -1 || coluna < 0 || coluna >= TAM)
        {
            printf("Coordenada inválida! Tente novamente.\n");
            continue;
        }

        printf("Orientação (H = horizontal, V = vertical): ");
        scanf(" %c", &orientacao);
        orientacao = toupper(orientacao);

        // Verifica se cabe e se o espaço está livre
        int valido = 1;
        if (orientacao == 'H')
        {
            if (coluna + navio.tamanho > TAM)
            {
                printf("O navio não cabe horizontalmente aí!\n");
                continue;
            }
            for (int j = 0; j < navio.tamanho; j++)
                if (tabuleiro[linha][coluna + j] != '~')
                    valido = 0;
            if (!valido)
            {
                printf("Espaço ocupado!\n");
                continue;
            }
            for (int j = 0; j < navio.tamanho; j++)
                tabuleiro[linha][coluna + j] = navio.simbolo;
            break;
        }
        else if (orientacao == 'V')
        {
            if (linha + navio.tamanho > TAM)
            {
                printf("O navio não cabe verticalmente aí!\n");
                continue;
            }
            for (int i = 0; i < navio.tamanho; i++)
                if (tabuleiro[linha + i][coluna] != '~')
                    valido = 0;
            if (!valido)
            {
                printf("Espaço ocupado!\n");
                continue;
            }
            for (int i = 0; i < navio.tamanho; i++)
                tabuleiro[linha + i][coluna] = navio.simbolo;
            break;
        }
        else
        {
            printf("Orientação inválida! Use H ou V.\n");
        }
    }
    return 1;
}

// Executa um ataque no tabuleiro
int ataque(char tabuleiro[TAM][TAM])
{
    char coordLetra;
    int coluna;
    int linha;

    printf("Digite a coordenada do ataque (ex: B7): ");
    scanf(" %c%d", &coordLetra, &coluna);
    linha = letraParaIndice(coordLetra);

    if (linha == -1 || coluna < 0 || coluna >= TAM)
    {
        printf("Coordenada inválida! Jogue novamente.\n");
        return 0;
    }

    char *celula = &tabuleiro[linha][coluna];
    if (*celula == '~')
    {
        *celula = 'O'; // água
        printf("Errou! Água!\n");
    }
    else if (*celula == 'O' || *celula == 'X')
    {
        printf("Você já atacou essa posição!\n");
    }
    else
    {
        *celula = 'X'; // acerto
        printf("Acertou um navio!\n");
    }
    return 1;
}

// Conta quantas partes de navio restam
int contarRestantes(char tabuleiro[TAM][TAM])
{
    int contador = 0;
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] == 'P' || tabuleiro[i][j] == 'E' ||
                tabuleiro[i][j] == 'C' || tabuleiro[i][j] == 'S')
                contador++;
    return contador;
}