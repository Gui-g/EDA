#include "arq.h"

struct pilha* cria(void) {
    struct pilha *p = NULL;
    p = (struct pilha*)malloc(sizeof(struct pilha));
    if (p) {
	    p->topo = NULL;
        p->tamPilha = 0;
    }
    return p;
}

int vazia(struct pilha *pil) {
    if (pil->topo == NULL)
        return 1;
    else
        return 0;
}

int empilha(info *reg, struct pilha *pil) {
    struct PDE *aux = NULL;
    aux=(struct PDE*) malloc(sizeof(struct PDE));
    if (aux!=NULL) {
        memcpy(&(aux->dados), reg, sizeof(info));
	    aux->abaixo = pil->topo;
        pil->topo->acima = aux;
     	pil->topo = aux;
	    (pil->tamPilha)++;
        return 1;
    }
    else
        return 0;
}

int desempilha(info *reg, struct pilha *pil) {
    struct PDE *aux = NULL;	  
    if (vazia(pil) == 0) {
        memcpy(reg, &(pil->topo->dados), sizeof(info));
	    aux = pil->topo->abaixo;
	    free(pil->topo);
	    pil->topo = aux;
        (pil->tamPilha)--;
        return 1;
    }
    else
        return 0;
}

int busca(info *reg, struct pilha *pil) {  
    if (vazia(pil) == 0){   
        memcpy(reg, &(pil->topo->dados),sizeof(info));
        return 1;
    }
    else
        return 0;
}

void reinicia(struct pilha *pil) {
    struct PDE *aux = NULL;	  
    if (vazia(pil) == 0) {	 
	    aux = pil->topo->abaixo;
        while(aux!=NULL) {
            free(pil->topo);
            pil->topo=aux;
            aux=aux->abaixo;

        }
    	free(pil->topo);
	    pil->topo = NULL;
       	pil->tamPilha = 0;
    }
}

struct pilha *destroi(struct pilha *pil) {
    reinicia(pil);
    free(pil);
    return NULL;
}