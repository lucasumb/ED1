#include <stdlib.h>
#include <stdio.h>

struct no {
    struct no* ant;
    int val;
    struct no* prox;
};

struct doublylinkedlist {
    struct no* cabeca;
    struct no* cauda;
    int qtdade;
};

struct doublylinkedlist* inicializar() {
    struct doublylinkedlist* lista = (struct doublylinkedlist*)malloc(sizeof(struct doublylinkedlist));
    lista->qtdade = 0;
    lista->cauda = NULL;
    lista->cabeca = NULL;
    return lista;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->prox = NULL;
    novoNo->ant = NULL;
    novoNo->val = valor;
    return novoNo;
}

void inserirElementoNoInicio(struct doublylinkedlist* lista, int valor) {
    struct no* novoNo = alocarNovoNo(valor);
    struct no* aux;

    if (lista->qtdade == 0) {
        lista->cabeca = novoNo;
        lista->cauda = novoNo;
        lista->qtdade++;
    }
    else {
        aux = lista->cabeca;
        aux->ant = novoNo;
        novoNo->prox = aux;
        lista->cabeca = novoNo;
        lista->qtdade++;
    }
}

void inserirElementoNoFim(struct doublylinkedlist* lista, int valor) {
    if (lista->qtdade == 0) {
        inserirElementoNoInicio(lista, valor);
        return;
    }

    struct no* novoNo = alocarNovoNo(valor);

    novoNo->ant = lista->cauda;
    (lista->cauda)->prox = novoNo;
    lista->cauda = novoNo;

    lista->qtdade++;
}

void inserirElementoEmPosicao(struct doublylinkedlist* lista, int valor, int posicao) {
    if (posicao > lista->qtdade || posicao < 0) {
        return;
    }
    if (posicao == lista->qtdade) {
        inserirElementoNoFim(lista, valor);
        return;
    }
    if (posicao == 0) {
        inserirElementoNoInicio(lista, valor);
        return;
    }

    struct no* novoNo = alocarNovoNo(valor);
    struct no* aux;
    int distanciaCauda = (lista->qtdade - posicao - 1);

    if (posicao <= distanciaCauda) {
        //percorre pela cabeça
        aux = lista->cabeca;
        for (int i = 0; i < posicao; i++) {
            aux = aux->prox;
        }
    }
    else {
        //percorre pela cauda
        aux = lista->cauda;
        for (int i = 0; i < distanciaCauda; i++) {
            aux = aux->ant;
        }
    }

    (aux->ant)->prox = novoNo;
    novoNo->ant = aux->ant;
    aux->ant = novoNo;
    novoNo->prox = aux;

    lista->qtdade++;
}

int obterElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao >= 0 && posicao < lista->qtdade) {
        int distanciaCauda = (lista->qtdade - posicao - 1);
        struct no* aux;

        if (posicao <= distanciaCauda) {
            aux = lista->cabeca;
            for (int i = 0; i < posicao; i++) {
                aux = aux->prox;
            }
        }
        else {
            aux = lista->cauda;
            for (int i = 0; i < distanciaCauda; i++) {
                aux = aux->ant;
            }
        }

        return aux->val;
    }
}

void removerElementoEmPosicao(struct doublylinkedlist* lista, int posicao) {
    if (posicao < 0 || posicao >= lista->qtdade) {
        return;
    }

    struct no* aux;
    int distanciaCauda = lista->qtdade - posicao - 1;

    if (posicao <= distanciaCauda) {
        aux = lista->cabeca;
        for (int i = 0; i < posicao; i++) {
            aux = aux->prox;
        }
    }
    else {
        aux = lista->cauda;
        for (int i = 0; i < distanciaCauda; i++) {
            aux = aux->ant;
        }
    }
    if (posicao == 0) {
        lista->cabeca = aux->prox;
        if (lista->cabeca != NULL)
            (lista->cabeca)->ant = NULL;
        else
            lista->cauda = NULL;
    }
    else if (posicao == (lista->qtdade - 1)) {
        lista->cauda = aux->ant;
        (lista->cauda)->prox = NULL;
    }
    else {
        (aux->ant)->prox = aux->prox;
        (aux->prox)->ant = aux->ant;
    }
    lista->qtdade--;

    free(aux);
}

void imprimirLista(struct no** cabeca) {
    //usamos o aux para percorrer a lista
    if ((*cabeca) != NULL) {
        struct no* aux = (*cabeca);
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL) {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else {
        printf("A lista está vazia!");
    }
}