#include "arq.h"

int main() {
    FILE *arquivoEntrada;
    FILE *arquivoSaida;
    descMatriz *descritor;
    int *matriz;
    int label = 2;

    arquivoEntrada = fopen("entrada.txt", "r");

    inicializaDescritor(&descritor);
    matriz = CriarMatriz(arquivoEntrada, &descritor);
    PrintMatriz(matriz, descritor);
    printf("------------------ || ----------------------\n");
    RotularMatriz(&matriz, descritor, &label);
    PrintMatriz(matriz, descritor);

    free(matriz);

    return 0;
}

void inicializaDescritor(descMatriz **descritor) {
    *descritor = (descMatriz *)malloc(sizeof(descMatriz));
    (*descritor)->col = 0;
    (*descritor)->row = 0;
    (*descritor)->num = 0;
}

int *CriarMatriz(FILE *arquivo_entrada, descMatriz **descritor) {
    int *matriz;
    char character;

    matriz = (int *)malloc(sizeof(int));

    while (1) {
        if (fscanf(arquivo_entrada, "%c", &character) == EOF)
            break;
        else if (character == '\n') {
            (*descritor)->row++;
        } else {
            (*descritor)->num++;
            matriz = realloc(matriz, ((*descritor)->num) * sizeof(int));
            matriz[(*descritor)->num - 1] = (int)character - '0';
        }
    }
    (*descritor)->col = (*descritor)->num / (*descritor)->row;
    return matriz;
}

void PrintMatriz(int *matriz, descMatriz *descritor) {
    int i, j;
    for (i = 0; i < descritor->row; i++) {
        for (j = 0; j < descritor->col; j++) printf("%d ", matriz[i * descritor->col + j]);
        printf("\n");
    }
}

void RotularMatriz(int **matriz, descMatriz *descritor, int *label) {
    int i, j;
    info dados;
    printf("rotulando\n");
    PrintMatriz(*matriz, descritor);
    for (i = 0; i < descritor->row; i++) {
        for (j = 0; j < descritor->col; j++) {
            printf("%d\n", *(*(matriz) + i * descritor->col + j));
            if (*(*(matriz) + i * descritor->col + j) == 1) {
                dados.x = i;
                dados.y = j;
                Rotula(matriz, descritor, dados, label);
                (*label)++;
            }
        }
    }
}

void Rotula(int **matriz, descMatriz *descritor, info dados, int *label) {
    int i = dados.x;
    int j = dados.y;
    info aux;
    struct pilha descritorPilha;

    RotulaDireita(matriz, descritor, dados, label, &descritorPilha);
    printf("rotulando objeto");

    while (busca(&aux, &descritorPilha) == 1) {
        desempilha(&aux, &descritorPilha);
        if (*(*(matriz) + i * descritor->col + j) == *label) {
            if (*(*(matriz) + (i + 1) * descritor->col + j) == 1)
                RotulaEsquerda(matriz, descritor, dados, label, &descritorPilha);
        }
    }
}

void RotulaDireita(int **matriz, descMatriz *descritor, info dados, int *label,
                   struct pilha *descritorPilha) {
    int i = dados.x;
    int j = dados.y;
    info aux;

    while (*(*(matriz) + i * descritor->col + j) == 1) {
        aux.x = i;
        aux.y = j;
        empilha(&aux, descritorPilha);
        j++;
        *(*(matriz) + i * descritor->col + j) = *label;
    }
}

void RotulaEsquerda(int **matriz, descMatriz *descritor, info dados, int *label,
                    struct pilha *descritorPilha) {
    int i = dados.x;
    int j = dados.y;
    info aux;

    while (*(matriz[i * descritor->col + j]) == 1) {
        aux.x = i;
        aux.y = j;
        empilha(&aux, descritorPilha);
        j--;
        *(matriz[i * descritor->col + j]) = *label;
    }
}
