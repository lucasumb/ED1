#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <queue>
using namespace std;
//Aluno : Lucas de Oliveira Umbelino

void atualizar(struct noBst* no);
struct noBst* balancear(struct noBst* no);
struct noBst* rebalancearEsqEsq(struct noBst* no);
struct noBst* rebalancearEsqDir(struct noBst* no);
struct noBst* rebalancearDirDir(struct noBst* no);
struct noBst* rebalancearDirEsq(struct noBst* no);
int altura(struct noBst* raiz);

/**
 * Embora durante a aula eu disse que precisar�amos
 * das vari�veis alturaEsq e alturaDir, na verdade n�o
 * � necess�rio. Depois de implementar que percebi algo
 * �bvio: para pegar a altura de uma sub-�rvore basta
 * obter o valor da vari�vel altura na sub-�rvore. (:
 **/
struct noBst {
    int val;
    int altura;
    int balanco;
    struct noBst* esq;
    struct noBst* dir;
};

/**
 * Funcao que aloca um novo noBst, e
 * ajusta os ponteiros esq e dir para NULL,
 * e vari�veis altura e balanco para 0.
 **/
struct noBst* alocarNovoNo(int val) {
    struct noBst* novoNo = (struct noBst*)malloc(sizeof(struct noBst));
    novoNo->val = val;
    novoNo->dir = NULL;
    novoNo->esq = NULL;
    novoNo->altura = 0;
    novoNo->balanco = 0;
    return novoNo;
}

/**
 * Funcao que rotaciona uma arvore para a
 * direita e retorna a nova raiz.
 **/
struct noBst* rotacaoDireita(struct noBst* arvore) {
    struct noBst* esq = arvore->esq;
    arvore->esq = esq->dir;
    esq->dir = arvore;
    atualizar(esq->dir);
    atualizar(esq);

    return esq;     //nova raiz da arvore
}

/**
 * Funcao que rotaciona uma arvore para a
 * esquerda e retorna a nova raiz.
 **/
struct noBst* rotacaoEsquerda(struct noBst* arvore) {
    struct noBst* dir = arvore->dir;
    arvore->dir = dir->esq;
    dir->esq = arvore;
    atualizar(dir->esq);
    atualizar(dir);

    return dir;
}

/**
 * Funcao que recebe a raiz de uma BST, e
 * insere um novo valor na BST. Tamanho deve
 * ser incrementado.
 * Ambos tamanho e raiz s�o passados por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� inserido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de inserir de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
void inserir(struct noBst** raiz, int val, int* tamanho) {
    if ((*raiz) == NULL) {
        (*raiz) = alocarNovoNo(val);
        (*tamanho)++;
    }
    else if (val > (*raiz)->val) {
        inserir(&(*raiz)->dir, val, tamanho);
        atualizar(*raiz);
        if ((*raiz)->balanco == 2 || (*raiz)->balanco == -2)
            (*raiz) = balancear(*raiz);
    }
    else {
        inserir(&(*raiz)->esq, val, tamanho);
        atualizar(*raiz);
        if ((*raiz)->balanco == 2 || (*raiz)->balanco == -2)
            (*raiz) = balancear(*raiz);
    }
}

/**
 * Funcao que recebe a raiz de uma BST e atualiza sua altura
 * e fator de balan�o.
 * Lembre que a altura das sub-�rvores direita e esquerda
 * n�o v�o mudar, por isso a implementa��o n�o � t�o complicada.
 **/
void atualizar(struct noBst* no) {
    (no)->altura = altura(no);
    if ((no)->esq == NULL && (no)->dir == NULL)
        (no)->balanco = 0;
    else if ((no)->dir == NULL)
        (no)->balanco = -(no)->esq->altura;
    else if ((no)->esq == NULL)
        (no)->balanco = (no)->dir->altura;
    else
        (no)->balanco = (no)->dir->altura - (no)->esq->altura;
}

/**
 * Funcao que recebe a raiz de uma BST e identifica em qual caso
 * ela se encaixa para executar os procedimentos de balanceamento
 * corretos:
 *      - Caso 1: esquerda-esquerda e esquerda-cheio
 *      - Caso 2: esquerda-direita
 *      - Caso 3: direita-direita e direita-cheio
 *      - Caso 4: direita-esquerda
 * Dica: usar fator de balan�o do n� e de uma de suas sub-�rvores
 * para descobrir qual � o caso.
 **/
struct noBst* balancear(struct noBst* no) {

    if (no->balanco == -2 && no->esq->balanco == -1)
        return rebalancearEsqEsq(no);
    else if (no->balanco == -2 && no->esq->balanco == 1)
        return rebalancearEsqDir(no);
    else if (no->balanco == 2 && no->dir->balanco == 1)
        return rebalancearDirDir(no);
    else if(no->balanco == 2 && no->dir->balanco == -1)
        return rebalancearDirEsq(no);

    return no;
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 1.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqEsq(struct noBst* no) {
    return rotacaoDireita(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 2.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearEsqDir(struct noBst* no) {
    no->esq = rotacaoEsquerda(no->esq);
    return rebalancearEsqEsq(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 3.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirDir(struct noBst* no) {
    return rotacaoEsquerda(no);
}

/**
 * Funcao que recebe a raiz de uma BST e usa as rota��es
 * apropriadas para balancear uma �rvore desbalanceada no caso 4.
 * Lembre-se que durante o balanceamento a raiz muda
 * e essa fun��o deve retornar a nova raiz.
 **/
struct noBst* rebalancearDirEsq(struct noBst* no) {
    no->dir = rotacaoDireita(no->dir);
    return rebalancearDirDir(no);
}

/**
 * Funcao que retorna o maior valor de uma �rvore.
 * Mesma implementa��o da BST.
 **/
int max(struct noBst* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->dir == NULL)
        return raiz->val;
    else
        return max(raiz->dir);
}

/**
 * Funcao que retorna o menor valor de uma �rvore.
 * Mesma implementa��o da BST.
 **/
int min(struct noBst* raiz) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->esq == NULL)
        return raiz->val;
    else
        return min(raiz->esq);
}

/**
 * Funcao que retorna a altura de uma �rvore.
 * A altura de uma �rvore � dada pela quantidade
 * de arestas entre a raiz e a folha mais distante.
 * Mesma implementa��o da BST.
 **/
int altura(struct noBst* raiz) {
    if (raiz == NULL || (raiz->dir == NULL && raiz->esq == NULL))
        return 0;

    int alturaEsq = 1 + altura(raiz->esq);
    int alturaDir = 1 + altura(raiz->dir);

    if (alturaDir > alturaEsq)
        return alturaDir;
    else
        return alturaEsq;
}

/**
 * Funcao que recebe a raiz de uma �rvore, e
 * remove o n� que contem o valor passado como
 * argumento. Tamanho deve ser decrementado.
 * Tamanho � passado por refer�ncia.
 * Lembrar de atualizar altura e fator de balanco dos n�s
 * antecessores do n� removido, bem como balance�-los caso
 * seja necess�rio.
 * Dica: reutilizar a fun��o de remover de BST, e lembrar
 * de como usar inteligentemente a recurs�o para conseguir
 * atualizar e balancear os n�s antecessores.
 **/
struct noBst* remover(struct noBst* raiz, int val, int* tamanho) {
    if (raiz == NULL)
        return NULL;
    else if (raiz->val > val) {
        raiz->esq = remover(raiz->esq, val, tamanho);
    }
    else if (raiz->val < val) {
        raiz->dir = remover(raiz->dir, val, tamanho);
    }
    else {
        if (raiz->dir == NULL && raiz->esq == NULL) {
            free(raiz);
            raiz = NULL;
            (*tamanho)--;
        }
        else if (raiz->esq == NULL) {
            struct noBst* aux = raiz;
            raiz = raiz->dir;
            free(aux);
            (*tamanho)--;
        }
        else if (raiz->dir == NULL) {
            struct noBst* aux = raiz;
            raiz = raiz->esq;
            free(aux);
            (*tamanho)--;
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
    if (raiz != NULL) {
        atualizar(raiz);
        if ((raiz)->balanco == 2 || (raiz)->balanco == -2)
            (raiz) = balancear(raiz);
    }
    return raiz;
}

void imprimir(queue<struct noBst*> nosImpressao);

/**
* Fun��o que imprime a �rvore.
* Pode ser �til para depura��o.
**/
void imprimir(struct noBst* raiz) {
    queue<struct noBst*> nosImpressao;
    nosImpressao.push(raiz);
    imprimir(nosImpressao);
}

void imprimir(queue<struct noBst*> nosImpressao) {

    queue<struct noBst*> nosImpressaoProxNivel;

    while (!nosImpressao.empty()) {
        struct noBst* noImpressao = nosImpressao.front();
        //add filhos na fila
        if (noImpressao != NULL) {
            if (noImpressao->esq != NULL)
                nosImpressaoProxNivel.push(noImpressao->esq);
            else
                nosImpressaoProxNivel.push(NULL);
            if (noImpressao->dir != NULL)
                nosImpressaoProxNivel.push(noImpressao->dir);
            else
                nosImpressaoProxNivel.push(NULL);
        }
        nosImpressao.pop();

        if (noImpressao != NULL) {
            cout << to_string(noImpressao->val) << " | ";
        }
        else {
            cout << "N | ";
        }
    }
    cout << endl << endl;
    if (!nosImpressaoProxNivel.empty())
        imprimir(nosImpressaoProxNivel);
}