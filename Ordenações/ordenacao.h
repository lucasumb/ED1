#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED

//troca deve ser declarado antes de selectionSortIP
void troca(int* v, int i, int j)
{
    int aux = v[i];
    v[i] = v[j];
    v[j] = aux;
}

void impressaoVetor (int* v, int tamanho)
{
    for(int i=0; i<tamanho; i++)
    {
        printf("%d ", v[i]);
    }
    printf("\n");
}

//selectionSort Out-of-Place
void selectionSortOP(int** v, int tamanho)
{
    int* ordenado  = (int*) malloc (tamanho * sizeof(int));
    int iMenor;

    for(int i = 0; i<tamanho; i++)
    {
        iMenor = i;
        for(int j=0; j<tamanho; j++)
        {
            if( (*v)[j]< (*v)[iMenor] )
            {
                iMenor = j;
            }
        }
        ordenado[i] = (*v)[iMenor];
        (*v)[iMenor] = INT_MAX;
    }
    (*v) = ordenado;
}

//selectionSort in-Place
void selectionSortIP(int* v, int tamanho)
{
    int iMenor;
    for(int i=0; i<(tamanho-1); i++)
    {
        iMenor = i;
        for(int j= i+1; j< tamanho; j++)
        {
            if( v[j] < v[iMenor] )
            {
                iMenor = j;
            }
        }
        troca(v,i,iMenor);
    }
}

void bubbleSort(int* v, int n){
    for(int varredura = 0; varredura < n-1; varredura++){
        bool trocou = false;
        for(int i = 0; i < n-varredura-1; i++){
            if(v[i]>v[i+1]){
                int temp = v[i];
                v[i] = v[i+1];
                v[i+1] = temp;
                trocou = true;
            }
        }
        if(trocou==false)
            return;
    }
}

//insertionSort Out-of-Place
void insertionSortOP(int** v, int tamanho) {
    int* ordenado = (int*) malloc (tamanho * sizeof(int));

    for(int i=0;i<tamanho; i++){
        int j;
        for(j= i; j>0; j--){
            if( (*v)[i] < ordenado[j-1] ){
                ordenado[j] = ordenado[j-1];
            }
            else{
                break;
            }
        }
        ordenado[j] = (*v)[i];
    }
    (*v) = ordenado;
}

//insertionSort In-Place
void insertionSortIP(int** v, int tamanho) {

    for(int i=1;i<tamanho; i++){
        int j;
        for(j= i; j>0; j--){
            if( (*v)[j] <(*v)[j-1] ){
                troca((*v),j,j-1);
                //ordenado[j] = ordenado[j-1];
            }
            else{
                break;
            }
        }
        //troca((*v),j,i);
        //ordenado[j] = (*v)[i];
    }
}




#endif // ORDENACAO_H_INCLUDED
