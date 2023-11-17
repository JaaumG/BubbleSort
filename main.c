#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAMANHO_VET 10000

// Funcoes utilitarias
// Preenche um vetor de tamanho n com numeros aleatorios de 0 ate limite
void initRand(int *vetor, int n, int limite) {
    int i;
    float fatorMult = ((float) limite) / (float) RAND_MAX;
    srand(time(NULL));
    for (i = 0; i < n; i++) {
        vetor[i] = rand() * fatorMult;
    }
}

// Calcula o tempo entre duas tomadas de tempo em segundos
float calculaTempoSegundos(clock_t ini, clock_t fim) {
    return ((double) fim - ini) / CLOCKS_PER_SEC;
}

// Faz o processador aguardar ms milisegundos - Consome CPU !
void dormir(unsigned int ms) {
    clock_t goal = ms + clock();
    while (goal > clock());
}


// Imprime o vetor
void imprimeVetor(int v[], int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        if (i > 0) printf(", ");
        printf("%d", v[i]);
    }
    printf("\n");
}

int *copiarVetor(int vet[], int tamanho) {
    int *v = malloc(tamanho * sizeof(int));
    int i;
    for (i = 0; i < tamanho; i++) {
        v[i] = vet[i];
    }
    return v;
}

void bubbleSort(int v[], int tam) {
    int i, fim = tam-1, chave;
    bool troca = true;
    while (troca){
        troca = false;
        for (i = 0; i < fim; i++) {
            if (v[i] > v[i+1]){
                chave = v[i];
                v[i] = v[i+1];
                v[i+1] = chave;
                troca = true;
            }
        }
    }
}

void insertionSort(int v[], int n) {
    int i, j, chave;
    for (j = 1; j < n; j++) {
        chave = v[j];
        i = j - 1;
        while (i >= 0 && v[i] > chave) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = chave;
    }
}

void selectionSort(int num[], int tam) {
    int i, j, min;
    for (i = 0; i < (tam - 1); i++) {
        min = i;
        for (j = (i + 1); j < tam; j++) {
            if (num[j] < num[min]) min = j;
        }
        if (i != min) {
            int swap = num[i];
            num[i] = num[min];
            num[min] = swap;
        }
    }
}

void shellSort(int *vet, int size) {
    int i, j, value;
    int gap = 1;
    while (gap< size)
        gap = 3 * gap + 1;
    while (gap > 1) {
        gap /= 3;
        for (i = gap; i < size; i++) {
            value = vet[i];
            j = i;
            while (j >= gap && value < vet[j - gap]) {
                vet[j] = vet[j - gap];
                j -= gap;
            }
            vet[j] = value;
        }
    }
}

void merge(int vetor[], int comeco, int meio, int fim) {
    int com1 = comeco, com2 = meio + 1, comAux = 0, tam = fim - comeco + 1;
    int *vetAux;
    vetAux = (int *) malloc(tam * sizeof(int));
    while (com1 <= meio && com2 <= fim) {
        if (vetor[com1] < vetor[com2]) {
            vetAux[comAux] = vetor[com1];
            com1++;
        } else {
            vetAux[comAux] = vetor[com2];
            com2++;
        }
        comAux++;
    }
    //Caso ainda haja elementos na primeira metade
    while (com1 <= meio) {
        vetAux[comAux] = vetor[com1];
        comAux++;
        com1++;
    }
    //Caso ainda haja elementos na segunda metade
    while (com2 <= fim) {
        vetAux[comAux] = vetor[com2];
        comAux++;
        com2++;
    }
    //Move os elementos de volta para o vetor original
    for (comAux = comeco; comAux <= fim; comAux++) {
        vetor[comAux] = vetAux[comAux - comeco];
    }
    free(vetAux);
}

void mergeSort(int vetor[], int comeco, int fim) {
    if (comeco < fim) {
        int meio = (fim + comeco) / 2;
        mergeSort(vetor, comeco, meio);
        mergeSort(vetor, meio + 1, fim);
        merge(vetor, comeco, meio, fim);
    }
}

void constroiHeap(int p_vetor[], int tamanho, int indice_raiz) {
    int ramificacao, valor;
    valor = p_vetor[indice_raiz];
    while (indice_raiz <= tamanho / 2) {
        ramificacao = 2 * indice_raiz + 1;
        if (ramificacao>tamanho) break;
        if (ramificacao + 1 < tamanho  && p_vetor[ramificacao] < p_vetor[ramificacao + 1]) ramificacao++;
        if (valor >= p_vetor[ramificacao]) break;
        p_vetor[indice_raiz] = p_vetor[ramificacao];
        indice_raiz = ramificacao;
    }
    p_vetor[indice_raiz] = valor;
}

void heapSort(int *p_vetor, int tamanho){
    int indice, troca;
    for (indice = tamanho/2; indice >= 0; indice--)
        constroiHeap(p_vetor, tamanho, indice);
    while (tamanho>0){
        troca = p_vetor[0];
        p_vetor[0] = p_vetor[tamanho];
        p_vetor[tamanho] = troca;
        constroiHeap(p_vetor, --tamanho, 0);
    }
}

int particao(int v[], int p, int r){
    int c = v[p], i = p+1, j = r, t;
    while (1) {
        while(i <= j && v[i] <= c) ++i;
        while (c < v[j]) --j;
        if (i >= j) break;
        t = v[i]; v[i] = v[j]; v[j] = t;
        ++i; --j;
    }
    v[p] = v[j]; v[j] = c;
    return j;
}

void quicksort(int v[], int p, int r){
    int j;
    if (p < r) {
        j = particao(v, p, r);
        quicksort(v, p, j-1);
        quicksort(v, j+1, r);
    }
}

int main(int argc, char *argv[]) {
    clock_t ini, fim;

    int vetBubble[TAMANHO_VET];

    int *vetInsertion;

    initRand(vetBubble, TAMANHO_VET, 5000);

    // So podemos comparar a performance se os
    // metodos de ordenacao ordenarem exatamente os
    // mesmos dados
    vetInsertion = copiarVetor(vetBubble, TAMANHO_VET);

    printf("\nBubble Sort\n");

    imprimeVetor(vetBubble, 20); // apenas 20 posicoes

    ini = clock();
    bubbleSort(vetBubble, TAMANHO_VET);
    fim = clock();

    imprimeVetor(vetBubble, 20); // apenas 20 posicoes
    printf("Tempo Bubble Sort %f\n", calculaTempoSegundos(ini, fim));


    printf("\nInsertion Sort\n");

    imprimeVetor(vetInsertion, 20); // apenas 20 posicoes

    ini = clock();
    insertionSort(vetInsertion, TAMANHO_VET);
    fim = clock();

    imprimeVetor(vetInsertion, 20); // apenas 20 posicoes
    printf("Tempo Insertion Sort %f\n", calculaTempoSegundos(ini, fim));

    return 0;
}