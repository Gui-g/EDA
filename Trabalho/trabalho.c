#include "arq.h"

int main() {
    FILE *arquivoEntrada;
    FILE *arquivoSaida;
    descMatriz *descritor;
    int *matriz;
    int label = 1, maiorlabel;

    arquivoEntrada = fopen("entrada.txt", "r");
    inicializaDescritor(&descritor);
    matriz = CriarMatriz(arquivoEntrada, &descritor);
    fclose(arquivoEntrada);
    PrintMatriz(matriz, descritor);
    printf("------------------------------------------------------ || ----------------------------------------------------------\n");
    RotularMatriz(&matriz, descritor, &label);
    PrintMatriz(matriz, descritor);
    printf("------------------------------------------------------ || ----------------------------------------------------------\n");
    maiorlabel = AcharMaior(&matriz, descritor, &label);
    MatrizFinal(&matriz, descritor, &maiorlabel);
    PrintMatrizCenterMass(matriz,descritor);
    arquivoSaida = fopen("saida.txt", "w+");
    printFile(arquivoSaida, *descritor, matriz);
    fclose(arquivoSaida);

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
        for (j = 0; j < descritor->col; j++) printf("%2d ", matriz[i * descritor->col + j]);
        printf("\n");
    }
}

void RotularMatriz(int **matriz, descMatriz *descritor, int *label) {
    int i, j;
    info dados;
    for (i = 0; i < descritor->row; i++) {
        for (j = 0; j < descritor->col; j++) {
            if (*(*(matriz) + i * descritor->col + j) == 1) {
                dados.x = i;
                dados.y = j;
                (*label)++;
                Rotula(matriz, descritor, &dados, label);
            }
        }
    }
}

void Rotula(int **matriz, descMatriz *descritor, info *dados, int *label) {
    int i = dados->x;
    int j = dados->y;
    info aux;
    struct pilha *descritorPilha;
    descritorPilha = cria();

    Rotular(matriz, descritor, dados, label, descritorPilha);

    //direita
    while(*(*(matriz) + i*descritor->col + j) == 1) {
        j++;
        aux.x = i;
        aux.y = j;
        Rotular(matriz, descritor, &aux, label, descritorPilha); 
    }

    //baixo
    while(desempilha(&aux, descritorPilha)) {
            i = aux.x;
            j = aux.y;
            if(*(*(matriz) + (i+1)*descritor->col + j) == 1) {
                aux.x = i+1;
                aux.y = j;
                Rotular(matriz, descritor, &aux, label, descritorPilha); 
            }

            if(*(*(matriz) + i*descritor->col + (j-1)) == 1) {
                aux.x = i;
                aux.y = j-1;
                Rotular(matriz, descritor, &aux, label, descritorPilha); 
            }

            if(*(*(matriz) + i*descritor->col + (j+1)) == 1) {
                aux.x = i;
                aux.y = j+1;
                Rotular(matriz, descritor, &aux, label, descritorPilha); 
            }
    }

}

void Rotular(int **matriz, descMatriz *descritor, info *dados, int *label,
                   struct pilha *descritorPilha) {
    int i = dados->x;
    int j = dados->y;
    info aux;

    if (*(*(matriz) + i * descritor->col + j) == 1) {
        aux.x = i;
        aux.y = j;
        empilha(&aux, descritorPilha);
        *(*(matriz) + i * descritor->col + j) = *label;
    }
}

int AcharMaior (int **matriz, descMatriz *descritor, int *label){
    int i, j, num, max, quant, maxquant;

    num = 2;
    max = 2;
    maxquant = 0;
    quant = 0;
    for(i=2;i<=*label;i++) {
        for(j=0;j<descritor->num;j++){
            if(*(*(matriz) + j) == num) 
                quant++;
        }
        if(quant > maxquant) {
            maxquant = quant;
            max = num;
        }
        num++;
    }
    
    return max;
}

void MatrizFinal(int **matriz, descMatriz *descritor, int *label){

    int i;
    for(i=0; i<descritor->num; i++) {
        if(*(*(matriz) + i) == *label)
            *(*(matriz) + i) = 1;
        else
            *(*(matriz) + i) = 0;
    }

}

void PrintMatrizCenterMass(int *matriz, descMatriz *descritor) {
    int i, j, lin=0, col=0, size=0;

    for(i=0; i<descritor->row;i++){
        for(j=0;j<descritor->col;j++) {
            if(matriz[i * descritor->col + j] == 1) {
                lin += i;
                col += j;
                size++;
            }
        }
    }

    lin /= size;
    col /= size;

    for (i = 0; i < descritor->row; i++) {
        for (j = 0; j < descritor->col; j++) {
            if(i == lin && j == col)
                printf(ANSI_COLOR_RED "%2d " ANSI_COLOR_RESET, matriz[i * descritor->col + j]);
            else
                printf("%2d ", matriz[i * descritor->col + j]);
        }
        printf("\n");
    }

    printf("Centro de Massa = [%d, %d]\n", lin, col);
}

void printFile(FILE *f, descMatriz descritor, int *matriz) {
    int i, j;
    for(i=0;i<descritor.row;i++){
        for(j=0;j<descritor.col;j++){
            fprintf(f, "%d", matriz[i * descritor.col + j] == 1? 1:0);
        }
        fprintf(f, "\n");
    }
}