#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TAREFAS 100
#define MAX_DESC 100

/**
 * @struct Tarefa
 * @brief Representa uma tarefa com prioridade e descrição.
 */
typedef struct {
    int prioridade;             /**< Prioridade da tarefa (menor valor = mais urgente) */
    char descricao[MAX_DESC];   /**< Descrição da tarefa */
} Tarefa;

/**
 * @struct MinHeap
 * @brief Estrutura para representar um min-heap de tarefas.
 */
typedef struct {
    Tarefa tarefas[MAX_TAREFAS]; /**< Array para armazenar as tarefas */
    int tamanho;                 /**< Número atual de tarefas no heap */
} MinHeap;

/**
 * @brief Troca duas tarefas no heap.
 * @param a Ponteiro para a primeira tarefa.
 * @param b Ponteiro para a segunda tarefa.
 */
void troca(Tarefa *a, Tarefa *b) {
    Tarefa temp = *a;
    *a = *b;
    *b = temp;
}

/**
 * @brief Corrige o heap de baixo para cima para manter a propriedade de min-heap.
 * @param heap Ponteiro para o min-heap.
 * @param index Índice da tarefa inserida que pode violar a propriedade do heap.
 */
void heapify_up(MinHeap *heap, int index) {
    // Indice do elemento pai ao que foi passado
    int indexPai = (index - 1) / 2;
    if (index && heap->tarefas[indexPai].prioridade > heap->tarefas[index].prioridade) {
        troca(&heap->tarefas[index], &heap->tarefas[indexPai]);  // Troca o pai com o filho
        heapify_up(heap, indexPai); // Verificação da integridade do heap com o elemento PAI
    }
}

/**
 * @brief Corrige o heap de cima para baixo após remoção do elemento raiz.
 * @param heap Ponteiro para o min-heap.
 * @param index Índice do elemento que precisa ser "heapificado".
 */
void heapify_down(MinHeap *heap, int index) {
    int menor = index;
    int esquerda = 2 * index + 1;
    int direita = 2 * index + 2;

    // Se a prioridade do filho à esquerda for menor
    if (esquerda < heap->tamanho && heap->tarefas[esquerda].prioridade < heap->tarefas[menor].prioridade)
        menor = esquerda; // O menor agora é o da esquerda

    // Se a prioridade do filho à direita for menor
    if (direita < heap->tamanho && heap->tarefas[direita].prioridade < heap->tarefas[menor].prioridade)
        menor = direita; // O menor agora é o da direita

    // Se o menor tiver mudado
    if (menor != index) {
        // Troca o atual com o menor e repete o processo recursivamente
        troca(&heap->tarefas[index], &heap->tarefas[menor]);
        heapify_down(heap, menor);
    }
}

/**
 * @brief Inicializa o heap definindo seu tamanho como zero.
 * @param heap Ponteiro para o min-heap a ser inicializado.
 */
void inicializa_heap(MinHeap *heap) {
    heap->tamanho = 0;
}

/**
 * @brief Insere uma nova tarefa no min-heap.
 * @param heap Ponteiro para o min-heap onde a tarefa será inserida.
 * @param prioridade Prioridade da tarefa (menor valor = mais urgente).
 * @param descricao Descrição da tarefa (string).
 */
void inserir_tarefa(MinHeap *heap, int prioridade, const char *descricao) {
    // Heap cheio?
    if (heap->tamanho == MAX_TAREFAS) {
        printf("Heap cheio! Não é possível adicionar mais tarefas.\n");
        return;
    }

    Tarefa nova = {prioridade, ""};

    // Coloca a descricao passada no parametro na nova tarefa
    strncpy(nova.descricao, descricao, MAX_DESC - 1);
    nova.descricao[MAX_DESC - 1] = '\0';

    // Insere no final
    heap->tarefas[heap->tamanho] = nova;

    // "Heapifica" para cima a partir do ultimo elemento, verificando a integridade do Heap
    heapify_up(heap, heap->tamanho);
    heap->tamanho++;
}

/**
 * @brief Remove e retorna a tarefa com maior prioridade (menor valor).
 * @param heap Ponteiro para o min-heap.
 * @return Tarefa removida; se heap vazio, retorna tarefa com prioridade -1.
 */
Tarefa remover_tarefa_mais_urgente(MinHeap *heap) {
    Tarefa tarefa_removida = { -1, "" };

    // Heap vazio?
    if (heap->tamanho == 0) {
        printf("Nenhuma tarefa disponível.\n");
        return tarefa_removida;
    }
    
    // Remove a tarefa com maior prioridade
    tarefa_removida = heap->tarefas[0];

    // Faz a tarefa mais prioritária na verdade ser a última
    heap->tarefas[0] = heap->tarefas[heap->tamanho - 1];
    heap->tamanho--;

    // Heapifica pra baixo pra organizar os elementos corretamente
    heapify_down(heap, 0);

    return tarefa_removida;
}

/**
 * @brief Exibe todas as tarefas atualmente armazenadas no heap (não necessariamente ordenadas).
 * @param heap Ponteiro para o min-heap.
 */
void mostrar_tarefas(MinHeap *heap) {
    if (heap->tamanho == 0) {
        printf("Nenhuma tarefa para mostrar.\n");
        return;
    }

    printf("Tarefas atuais:\n");
    for (int i = 0; i < heap->tamanho; i++) {
        printf("Prioridade: %d - %s\n", heap->tarefas[i].prioridade, heap->tarefas[i].descricao);
    }
}

int main() {
    MinHeap agenda;
    inicializa_heap(&agenda);

    inserir_tarefa(&agenda, 3, "Estudar para prova");
    inserir_tarefa(&agenda, 1, "Entregar relatório");
    inserir_tarefa(&agenda, 2, "Responder e-mails");

    mostrar_tarefas(&agenda);

    printf("\nPegando a tarefa mais urgente:\n");
    Tarefa t = remover_tarefa_mais_urgente(&agenda);
    if (t.prioridade != -1)
        printf("Prioridade: %d, Tarefa: %s\n", t.prioridade, t.descricao);

    printf("\nTarefas restantes:\n");
    mostrar_tarefas(&agenda);

    return 0;
}
