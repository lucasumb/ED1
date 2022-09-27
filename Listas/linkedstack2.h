#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct no {
    int val;
    struct no* prox;
};

struct linkedstack {
    struct no* topo;
    int qtdade;
};

struct linkedstack* inicializar() {
    struct linkedstack* pilha = (struct linkedstack*)malloc(sizeof(struct linkedstack));
    pilha->qtdade = 0;
    pilha->topo = NULL;
    return pilha;
}

struct no* alocarNovoNo(int valor) {
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

//retornar true se a pilha for nula ou vazia
bool vazia(struct linkedstack* pilha) {
    if (pilha == NULL || pilha->qtdade == 0)
        return true;
    else
        return false;
}

//se a pilha estiver nula, instancie a pilha
//por causa da possibilidade de instanciacao usamos struct linkedstack**
void empilhar(struct linkedstack** pilha, int valor) {
    if ((*pilha) == NULL)
        *pilha = inicializar();

    struct no* novoNo = alocarNovoNo(valor);

    if ((*pilha)->topo == NULL)
        (*pilha)->topo = novoNo;
    else {
        struct no* aux = (*pilha)->topo;

        while (aux->prox != NULL)
            aux = aux->prox;

        aux->prox = novoNo;
    }
    (*pilha)->qtdade++;
}

//decrementar qtdade se a pilha não estiver nula ou vazia
void desempilhar(struct linkedstack* pilha) {
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;

        if (aux->prox == NULL) {
            pilha->topo = NULL;
        }
        else {
            while ( ((aux->prox)->prox) != NULL )
                aux = aux->prox;

            aux->prox = NULL;
        }
        pilha->qtdade--;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int desempilharRetornando(struct linkedstack* pilha) {
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        int valor;

        if (aux->prox == NULL) {
            valor = aux->val;
            pilha->topo = NULL;
        }
        else {
            while (((aux->prox)->prox) != NULL)
                aux = aux->prox;

            valor = (aux->prox)->val;
            aux->prox = NULL;
        }
        pilha->qtdade--;
        return valor;
    }
    else {
        return INT_MIN;
    }
}

//retorne a constante INT_MIN se a pilha for nula ou vazia
int topo(struct linkedstack* pilha) {
    if (vazia(pilha))
        return INT_MIN;
    else {
        struct no* aux = pilha->topo;

        while ((aux->prox) != NULL)
            aux = aux->prox;
        
        return aux->val;
    }
}

void exibirPilha(struct linkedstack* pilha) {
    //usamos o aux para percorrer a lista
    if (!vazia(pilha)) {
        struct no* aux = pilha->topo;
        //navega partindo do topo até chegar NULL
        printf("_\n");
        do {
            printf("%d\n", aux->val);
            aux = aux->prox;
        } while (aux != NULL);
        printf("_");
    }
    else {
        printf("A pilha está vazia!");
    }
}