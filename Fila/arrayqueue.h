#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct arrayqueue {
    int frente;
    int tras;
    int* elementos;
    int tamanho;    //tam do array
    int qtdade;     //qtdade de elementos no array    
};

struct arrayqueue* inicializar(int tamArray) {
    struct arrayqueue* fila = (struct arrayqueue*)malloc(sizeof(struct arrayqueue));
    fila->elementos = (int*)malloc(tamArray * sizeof(int));
    fila->frente = -1;
    fila->tras = -1;
    fila->qtdade = 0;
    fila->tamanho = tamArray;
    return fila;
}

//se a fila estiver nula, instancie a fila com tamanho 10
//por causa da possibilidade de instanciacao usamos struct arrayqueue**
//se a fila encher, simplesmente não enfileire
void enfileirar(struct arrayqueue** fila, int val) {
    if ((*fila) == NULL)
        (*fila) = inicializar(10);

    //ou (tras+1)%tamanho == 
    if ( ((*fila)->tras + 1)%(*fila)->tamanho == (*fila)->frente )
        return;

    if ((*fila)->frente == -1)
        (*fila)->frente = ((*fila)->frente + 1) % (*fila)->tamanho;

    (*fila)->tras = ((*fila)->tras + 1) % (*fila)->tamanho;
    (*fila)->elementos[(*fila)->tras] = val;
    (*fila)->qtdade++;
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int desenfileirar(struct arrayqueue* fila) {
    if (fila == NULL || fila->qtdade == 0) {
        return INT_MIN;
    }
    else {
        int valor = fila->elementos[fila->frente];
        fila->frente = (fila->frente + 1) % fila->tamanho;
        fila->qtdade--;
        return valor;
    }
}

//retorne a constante INT_MIN se a fila for nula ou vazia
int frente(struct arrayqueue* fila) {
    if (fila == NULL || fila->qtdade == 0) {
        return INT_MIN;
    }
    else {
        return fila->elementos[fila->frente];
    }
}