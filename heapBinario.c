#include <stdio.h>
#define MAX 100  // Tamanho máximo do heap

// Estrutura do heap
typedef struct {
    int dados[MAX];  // Vetor para armazenar os elementos do heap
    int tamanho;     // Número atual de elementos no heap
} Heap;

// Função para trocar dois elementos
void trocar(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Reorganiza o heap para cima após inserção
void subir(Heap* heap, int indice) {
    while (indice > 0) {
        int pai = (indice - 1) / 2;
        if (heap->dados[indice] > heap->dados[pai]) {
            trocar(&heap->dados[indice], &heap->dados[pai]);
            indice = pai;
        } else {
            break;
        }
    }
}

// Insere um novo valor no heap
void inserir(Heap* heap, int valor) {
    if (heap->tamanho >= MAX) {
        printf("Heap cheio!\n");
        return;
    }
    heap->dados[heap->tamanho] = valor;
    subir(heap, heap->tamanho);
    heap->tamanho++;
}

// Reorganiza o heap para baixo após remoção
void descer(Heap* heap, int indice) {
    while (1) {
        int maior = indice;
        int esq = 2 * indice + 1;
        int dir = 2 * indice + 2;

        if (esq < heap->tamanho && heap->dados[esq] > heap->dados[maior]) {
            maior = esq;
        }
        if (dir < heap->tamanho && heap->dados[dir] > heap->dados[maior]) {
            maior = dir;
        }

        if (maior != indice) {
            trocar(&heap->dados[indice], &heap->dados[maior]);
            indice = maior;
        } else {
            break;
        }
    }
}

// Remove o maior valor (raiz) do heap
int remover_max(Heap* heap) {
    if (heap->tamanho == 0) {
        printf("Heap vazio!\n");
        return -1;
    }

    int max = heap->dados[0];
    heap->tamanho--;
    heap->dados[0] = heap->dados[heap->tamanho];
    descer(heap, 0);
    return max;
}

// Imprime o heap como vetor
void imprimir(Heap* heap) {
    printf("Heap: ");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("%d ", heap->dados[i]);
    }
    printf("\n");
}

// Função principal para testes
int main() {
    Heap heap;
    heap.tamanho = 0;

    inserir(&heap, 30);
    inserir(&heap, 20);
    inserir(&heap, 40);
    inserir(&heap, 50);
    inserir(&heap, 10);

    imprimir(&heap);

    printf("Removido: %d\n", remover_max(&heap));
    imprimir(&heap);

    return 0;
}
