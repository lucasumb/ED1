#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
//Aluno: Lucas de Oliveira Umbelino

struct noBst {
    int val;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL.
 **/
struct noBst* alocarNovoNo(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->dir = NULL;
    novoNo->esq = NULL;

    return novoNo;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz são passados por referência.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {

    if ( (*raiz) == NULL) {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else if ((*raiz)->val < val) {
        inserir( &((*raiz)->dir) , val, tamanho);
    }
    else {
        inserir(&((*raiz)->esq), val, tamanho);
    }
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * verifica se a mesma contém um dado valor.
 **/
bool buscar(struct noBst* raiz, int val) {
    if ( raiz == NULL) {
        return false;
    }
    else if (raiz->val == val) {
        return true;
    }
    else if (raiz->val < val) {
        buscar( raiz->dir , val);
    }
    else {
        buscar( raiz->esq, val);
    }
}

/**
 * Funcao que retorna o maior valor de uma BST.
 **/
int max(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->dir == NULL) {
        return raiz->val;
    }
    else {
        return max(raiz->dir);
    }
}

/**
 * Funcao que retorna o menor valor de uma BST.
 **/
int min(struct noBst* raiz) {
    if (raiz == NULL) {
        return NULL;
    }

    if (raiz->esq == NULL) {
        return raiz->val;
    }
    else {
        return min(raiz->esq);
    }
}

/**
 * Funcao que retorna a altura de uma BST.
 * A altura de uma BST é dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 **/
int altura(struct noBst* raiz) {
    if (raiz == NULL || (raiz->dir == NULL && raiz->esq == NULL) ) {
        return 0;
    }

    int alturaEsq =  1 + altura(raiz->esq);
    int alturaDir = 1 + altura(raiz->dir);

    if (alturaDir > alturaEsq) {
        return alturaDir;
    }
    else {
        return alturaEsq;
    }
}

/**
 * Funcao que navega em-ordem na BST e
 * imprime seus elementos.
 **/
void emOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }

    emOrdem(raiz->esq);
    printf(" %d", raiz->val);
    emOrdem(raiz->dir);

}

/**
 * Funcao que navega pre-ordem na BST e
 * imprime seus elementos.
 **/
void preOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }
     
    printf(" %d", raiz->val);
    preOrdem(raiz->esq);
    preOrdem(raiz->dir);

}

/**
 * Funcao que navega pos-ordem na BST e
 * imprime seus elementos.
 **/
void posOrdem(struct noBst* raiz) {
    if (raiz == NULL) {
        return;
    }

    posOrdem(raiz->esq);
    posOrdem(raiz->dir);
    printf(" %d", raiz->val);
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * remove o no que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho é passado por referência.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    if (raiz == NULL) {
        return NULL;
    }
    else if (raiz->val < val) {
        raiz->dir = remover(raiz->dir, val, tamanho);
    }
    else if (raiz->val > val) {
        raiz->esq = remover(raiz->esq, val, tamanho);
    }
    else {
        if (raiz->esq == NULL && raiz->dir == NULL) {
            free(raiz);
            raiz = NULL;
            tamanho--;
        }
        else if (raiz->esq == NULL) {
            struct noBst* noRemovido = raiz;
            raiz = raiz->dir;
            free(noRemovido);
            tamanho--;
        }
        else if (raiz->dir == NULL) {
            struct noBst* noRemovido = raiz;
            raiz = raiz->esq;
            free(noRemovido);
            tamanho--;
        }
        else {
            struct noBst* aux = raiz->esq;
            while (aux->dir != NULL) {
                aux = aux->dir;
            }
            raiz->val = aux->val;
            aux->val = val;
            raiz->esq = remover(raiz->esq, val, tamanho);
        }
    }
    return raiz;
}