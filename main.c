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
    for (i = 1; i < n; i++) {
        chave = v[i];
        j = i - 1;
        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
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