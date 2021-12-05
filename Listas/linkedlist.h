#include <stdlib.h>
#include <stdio.h>

struct no
{
    int val;
    struct no* prox;
};

struct linkedlist
{
    struct no* cabeca;
    int qtdade;
};

struct linkedlist* inicializar()
{
    struct linkedlist* lista = (struct linkedlist*)malloc(sizeof(struct linkedlist));
    lista->qtdade = 0;
    lista->cabeca = NULL;
    return lista;
}

struct no* alocarNovoNo(int valor)
{
    struct no* novoNo = (struct no*)malloc(sizeof(struct no));
    novoNo->val = valor;
    novoNo->prox = NULL;
    return novoNo;
}

void inserirElementoNoFim(struct linkedlist* lista, int valor)
{
    struct no* aux = lista->cabeca;
    struct no* novoNo = alocarNovoNo(valor);

    if (aux == NULL)
    {
        lista->cabeca = novoNo;
        lista->qtdade++;
    }
    else
    {
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novoNo;
        lista->qtdade++;
    }

}

void inserirElementoNoInicio(struct linkedlist* lista, int valor)
{
    struct no* aux = lista->cabeca;
    struct no* novoNo = alocarNovoNo(valor);
    if (aux == NULL)
    {
        lista->cabeca = novoNo;
        lista->qtdade++;
    }
    else {
        novoNo->prox = aux;
        lista->cabeca = novoNo;
        lista->qtdade++;
    }
}

void inserirElementoEmPosicao(struct linkedlist* lista, int valor, int posicao)
{
    if (posicao >= 0 && posicao <= lista->qtdade)
    {

        if (posicao == lista->qtdade)
        {
            inserirElementoNoFim(lista, valor);
            return;
        }
        if (posicao == 0)
        {
            inserirElementoNoInicio(lista, valor);
            return;
        }

        struct no* aux = lista->cabeca;
        struct no* novoNo = alocarNovoNo(valor);
        for (int i = 1; i < posicao; i++)
        {
            aux = aux->prox;
        }
        novoNo->prox = aux->prox;
        aux->prox = novoNo;
        lista->qtdade++;
    }
}

int obterElementoEmPosicao(struct linkedlist* lista, int posicao)
{
    if (posicao >= 0 && posicao < lista->qtdade)
    {
        struct no* aux = lista->cabeca;
        for (int i = 0; i < posicao; i++)
        {
            aux = aux->prox;
        }

        return aux->val;
    }
}

void removerElementoEmPosicao(struct linkedlist* lista, int posicao)
{
    if (posicao >= 0 && posicao < lista->qtdade)
    {
        struct no* aux = lista->cabeca;
        struct no* auxProximo = aux->prox;
        if (posicao == 0) {
            lista->cabeca = auxProximo;
            free(aux);
            lista->qtdade--;
            return;
        }

        for (int i = 1; i < posicao; i++)
        {
            aux = aux->prox;
        }
        auxProximo = aux->prox;
        aux->prox = auxProximo->prox;
        free(auxProximo);
        lista->qtdade--;
    }
}

void imprimirLista(struct linkedlist* lista)
{
    //usamos o aux para percorrer a lista
    if (lista->cabeca != NULL)
    {
        struct no* aux = lista->cabeca;
        //navega partindo da cabeça até chegar NULL
        printf("[");
        do
        {
            printf("%d", aux->val);
            aux = aux->prox;
            if (aux != NULL)
            {
                printf(", ");
            }
        } while (aux != NULL);
        printf("]");
    }
    else
    {
        printf("A lista está vazia!");
    }
}

