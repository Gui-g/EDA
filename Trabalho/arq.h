#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct coord{  	
        int x;
	int y;
	} info;
		
struct PDE{	
        info dados;
	struct PDE *abaixo;
        struct PDE *acima;
	};	

struct pilha{ 
        struct PDE *topo;
        int tamPilha;
	};

typedef struct descritorMatriz{
        int row;
        int col;
        int num;
        } descMatriz;


//======================APLICACAO=====================
void inicializaDescritor(descMatriz **descritor);
int* CriarMatriz(FILE* arquivo_entrada, descMatriz **descritor);
void PrintMatriz (int *matriz, descMatriz *descritor);
void RotularMatriz (int **matriz, descMatriz *descritor, int *label);
void Rotula(int **matriz, descMatriz *descritor, info dados, int *label);
void RotulaDireita(int **matriz, descMatriz *descritor, info dados, int *label, struct pilha *descritorPilha);
void RotulaEsquerda(int **matriz, descMatriz *descritor, info dados, int *label, struct pilha *descritorPilha);

//======================PILHA=====================
struct pilha * cria(void);
int vazia(struct pilha *pil);
int empilha(info *reg, struct pilha *pil);
int desempilha(info *reg, struct pilha *pil);
int busca(info *reg, struct pilha *pil);
void reinicia(struct pilha *pil);
struct pilha *destroi(struct pilha *pil);
