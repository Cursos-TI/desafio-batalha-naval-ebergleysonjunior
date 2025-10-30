#include <stdio.h>

#define TAM 10       // Tamanho do tabuleiro 10x10
#define NAVIO 3      // Valor representando parte do navio
#define AGUA 0       // Representa água
#define HABILIDADE 5 // Representa área afetada por habilidade
#define TAM_H 5      // Tamanho da matriz de habilidade (5x5)

// -----------------------------------------------------------------
// Função: Inicializa o tabuleiro com 0 (água)
// -----------------------------------------------------------------
void inicializarTabuleiro(int tabuleiro[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// -----------------------------------------------------------------
// Função: Exibe o tabuleiro de forma organizada
// -----------------------------------------------------------------
void exibirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("\n===== TABULEIRO DE BATALHA NAVAL =====\n\n");
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            if (tabuleiro[i][j] == AGUA)
                printf("~ ");     // água
            else if (tabuleiro[i][j] == NAVIO)
                printf("N ");     // navio
            else if (tabuleiro[i][j] == HABILIDADE)
                printf("* ");     // área de habilidade
        }
        printf("\n");
    }
}

// -----------------------------------------------------------------
// Funções: Criação das matrizes de habilidades (Cone, Cruz, Octaedro)
// -----------------------------------------------------------------

// Cone apontando para baixo (origem no topo)
void criarCone(int habilidade[TAM_H][TAM_H]) {
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            // O cone cresce para baixo (em forma de triângulo)
            if (j >= (TAM_H / 2 - i) && j <= (TAM_H / 2 + i))
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cruz (origem no centro)
void criarCruz(int habilidade[TAM_H][TAM_H]) {
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (i == TAM_H / 2 || j == TAM_H / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Octaedro (losango com origem no centro)
void criarOctaedro(int habilidade[TAM_H][TAM_H]) {
    int meio = TAM_H / 2;
    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            if (abs(i - meio) + abs(j - meio) <= meio)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// -----------------------------------------------------------------
// Função: Sobrepõe a matriz de habilidade no tabuleiro
// -----------------------------------------------------------------
void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_H][TAM_H], int linhaCentro, int colunaCentro) {
    int desloc = TAM_H / 2;

    for (int i = 0; i < TAM_H; i++) {
        for (int j = 0; j < TAM_H; j++) {
            // Calcula posição real no tabuleiro
            int lin = linhaCentro - desloc + i;
            int col = colunaCentro - desloc + j;

            // Garante que está dentro dos limites
            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM) {
                if (habilidade[i][j] == 1 && tabuleiro[lin][col] == AGUA) {
                    tabuleiro[lin][col] = HABILIDADE;
                }
            }
        }
    }
}

// -----------------------------------------------------------------
// Função principal
// -----------------------------------------------------------------
int main() {
    int tabuleiro[TAM][TAM];
    inicializarTabuleiro(tabuleiro);

    // Posicionando alguns navios manualmente (fixos)
    tabuleiro[2][3] = NAVIO;
    tabuleiro[2][4] = NAVIO;
    tabuleiro[2][5] = NAVIO;
    tabuleiro[6][7] = NAVIO;
    tabuleiro[7][7] = NAVIO;
    tabuleiro[8][7] = NAVIO;

    // Matrizes das habilidades
    int cone[TAM_H][TAM_H];
    int cruz[TAM_H][TAM_H];
    int octaedro[TAM_H][TAM_H];

    // Criação das formas
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicando as habilidades em diferentes pontos
    aplicarHabilidade(tabuleiro, cone, 1, 4);       // Cone no topo central
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 8, 2);   // Octaedro no canto inferior esquerdo

    // Exibe resultado final
    exibirTabuleiro(tabuleiro);

    printf("\n✅ Áreas de habilidades aplicadas com sucesso!\n");
    printf("Legenda: ~ = Água | N = Navio | * = Área afetada\n\n");

    return 0;
}
