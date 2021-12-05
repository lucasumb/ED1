#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stack>
using namespace std;

//NOME: LUCAS DE OLIVEIRA UMBELINO

/* Q1: Inverta uma lista duplamente ligada
 * com um algoritmo in-place (ou seja, sem
 * criar uma nova lista duplamente ligada)
 */

struct noDuplo {
    struct noDuplo* ant;
    int val;
    struct noDuplo* prox;
};

struct doublylinkedlist {
    struct noDuplo* cabeca;
    struct noDuplo* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializarDLL() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->cabeca = NULL;
    lista->cauda = NULL;
    lista->qtdade = 0;
    return lista;
}

struct noDuplo* alocarNovoNoDuplo(int valor) {
    struct noDuplo* novoNo = (struct noDuplo*)malloc(sizeof(struct noDuplo));
    novoNo->val = valor;
    novoNo->ant = NULL;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    //aloca espaço na memória e popula novoNo
    struct noDuplo* novoNo = alocarNovoNoDuplo(valor);

    if (lista->cabeca == NULL) {
        //quando a lista é vazia, basta apontar o cabeca e cauda para o novoNo
        lista->cabeca = novoNo;
    }
    else {
        //atualizamos o ponteiro novoNo->ant para o antigo último nó
        novoNo->ant = lista->cauda;
        //ponteiro prox do antigo último nó para o novoNo
        lista->cauda->prox = novoNo;
    }
    //uma certeza: inserindo no fim, a cauda apontará para o novoNo
    lista->cauda = novoNo;
    lista->qtdade++;
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    struct noDuplo* aux = lista->cabeca;
    for (int i = 0; i < posicao && aux->prox != NULL; i++) {
        aux = aux->prox;
    }
    return aux->val;
}

void inverterDoublyLinkedList(struct doublylinkedlist* lista) {
    if (lista == NULL)
        return;
    if (lista->qtdade == 1 || lista->qtdade == 0) {
        return;
    }

    struct noDuplo* aux = lista->cauda;

    struct noDuplo* auxTroca = lista->cabeca;
    lista->cabeca = lista->cauda;
    lista->cauda = auxTroca;
    while (aux != NULL) {
        auxTroca = aux->prox;
        aux->prox = aux->ant;
        aux->ant = auxTroca;
        aux = aux->prox;
    }
}

/******************************************/

/* Q2: escreva um algoritmo que detecte se uma
 * certa combinacao de parenteses estah balanceada.
 * Dica: usar pilha, pode ser a impl "stack" CPP STL.
 * Olhe os casos de teste para entender o que eh uma
 * combinacao balanceada.
 */

bool balanceamentoParenteses(const char* parenteses, int tam) {
    //cont1 conta os (, cont2 conta os )
    int cont1 = 0, cont2 = 0;
    for (int i = 0; i < tam; i++) {
        if (parenteses[i] == '(') {
            cont1++;
        }
        if (parenteses[i] == ')') {
            cont2++;
        }
        if (cont2 > cont1) {
            return false;
        }
    }
    if (cont1 == cont2)
        return true;
    else
        return false;
}

/******************************************/

/* Q3: Inverta uma lista ligada (LinkedList)
 * com um algoritmo in-place (ou seja, sem
 * criar uma nova LinkedList)
 */

struct no {
    int val;
    struct no* prox;
};

struct linkedlist {
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializarLL() {
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->cabeca = NULL;
    lista->qtdade = 0;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    if (lista->cabeca == NULL) {
        lista->cabeca = novoNo;
    }
    else {
        struct no* aux = lista->cabeca;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
    lista->qtdade++;
}

void inverterLinkedListInPlace(struct linkedlist* lista) {
    if (lista == NULL)
        return;
    if (lista->qtdade == 1 || lista->qtdade == 0) {
        return;
    }

    struct no* aux = lista->cabeca;
    struct no* auxLocomover = (lista->cabeca)->prox;

    aux->prox = NULL;
    while (auxLocomover != NULL) {
        aux = auxLocomover;
        auxLocomover = auxLocomover->prox;
        aux->prox = lista->cabeca;
        lista->cabeca = aux;
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao) {
    struct no* aux = lista->cabeca;
    for (int i = 0; i < posicao && aux->prox != NULL; i++) {
        aux = aux->prox;
    }
    return aux->val;
}