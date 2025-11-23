#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_COMPONENTES 20

// Struct que representa um componente
typedef struct {
    char nome[30];
    char tipo[20];
    int prioridade;
} Componente;

// Protótipos das funções
void bubbleSortNome(Componente comp[], int n, int *comparacoes);
void insertionSortTipo(Componente comp[], int n, int *comparacoes);
void selectionSortPrioridade(Componente comp[], int n, int *comparacoes);
int buscaBinariaPorNome(Componente comp[], int n, char chave[], int *comparacoes);
void mostrarComponentes(Componente comp[], int n);

// Função principal
int main() {
    Componente torre[MAX_COMPONENTES];
    int n = 0;  // número de componentes cadastrados
    int opcao;
    
    printf("Cadastro de componentes da torre (até %d itens)\n", MAX_COMPONENTES);
    while (n < MAX_COMPONENTES) {
        printf("\nNome do componente: ");
        fgets(torre[n].nome, 30, stdin);
        torre[n].nome[strcspn(torre[n].nome, "\n")] = '\0';

        printf("Tipo do componente (controle/suporte/propulsao): ");
        fgets(torre[n].tipo, 20, stdin);
        torre[n].tipo[strcspn(torre[n].tipo, "\n")] = '\0';

        printf("Prioridade (1 a 10): ");
        scanf("%d", &torre[n].prioridade);
        getchar(); 
        n++;

        printf("Deseja adicionar outro componente? (1-sim / 0-nao): ");
        scanf("%d", &opcao);
        getchar();
        if (opcao == 0) break;
    }

    int comparacoes;
    char chave[30];

    do {
        printf("\n= MENU DE ORDENACAO E BUSCA=\n");
        printf("1 - Ordenar por nome (Bubble Sort)\n");
        printf("2 - Ordenar por tipo (Insertion Sort)\n");
        printf("3 - Ordenar por prioridade (Selection Sort)\n");
        printf("4 - Busca binaria por nome\n");
        printf("5 - Mostrar componentes\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        clock_t inicio, fim;
        double tempo;

        switch(opcao) {
            case 1:
                comparacoes = 0;
                inicio = clock();
                bubbleSortNome(torre, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por nome (Bubble Sort):\n");
                mostrarComponentes(torre, n);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 2:
                comparacoes = 0;
                inicio = clock();
                insertionSortTipo(torre, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por tipo (Insertion Sort):\n");
                mostrarComponentes(torre, n);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 3:
                comparacoes = 0;
                inicio = clock();
                selectionSortPrioridade(torre, n, &comparacoes);
                fim = clock();
                tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
                printf("\nComponentes ordenados por prioridade (Selection Sort):\n");
                mostrarComponentes(torre, n);
                printf("Comparacoes: %d | Tempo: %.6f s\n", comparacoes, tempo);
                break;

            case 4:
                printf("\nDigite o nome do componente para busca binaria: ");
                fgets(chave, 30, stdin);
                chave[strcspn(chave, "\n")] = '\0';
                comparacoes = 0;
                int idx = buscaBinariaPorNome(torre, n, chave, &comparacoes);
                if (idx != -1) {
                    printf("Componente encontrado! Nome: %s | Tipo: %s | Prioridade: %d\n",
                           torre[idx].nome, torre[idx].tipo, torre[idx].prioridade);
                } else {
                    printf("Componente nao encontrado.\n");
                }
                printf("Comparacoes: %d\n", comparacoes);
                break;

            case 5:
                mostrarComponentes(torre, n);
                break;

            case 0:
                printf("Saindo...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    return 0;
}

// Mostrar componentes
void mostrarComponentes(Componente comp[], int n) {
    printf("\n===== COMPONENTES =====\n");
    for (int i=0; i<n; i++) {
        printf("%d) Nome: %s | Tipo: %s | Prioridade: %d\n", i+1, comp[i].nome, comp[i].tipo, comp[i].prioridade);
    }
}

// Bubble Sort por nome
void bubbleSortNome(Componente comp[], int n, int *comparacoes) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            (*comparacoes)++;
            if (strcmp(comp[j].nome, comp[j+1].nome) > 0) {
                Componente temp = comp[j];
                comp[j] = comp[j+1];
                comp[j+1] = temp;
            }
        }
    }
}

// Insertion Sort por tipo
void insertionSortTipo(Componente comp[], int n, int *comparacoes) {
    for (int i = 1; i < n; i++) {
        Componente chave = comp[i];
        int j = i-1;
        while (j >=0) {
            (*comparacoes)++;
            if (strcmp(comp[j].tipo, chave.tipo) > 0) {
                comp[j+1] = comp[j];
                j--;
            } else {
                break;
            }
        }
        comp[j+1] = chave;
    }
}

// Selection Sort por prioridade
void selectionSortPrioridade(Componente comp[], int n, int *comparacoes) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            (*comparacoes)++;
            if (comp[j].prioridade < comp[min_idx].prioridade) {
                min_idx = j;
            }
        }
        Componente temp = comp[i];
        comp[i] = comp[min_idx];
        comp[min_idx] = temp;
    }
}

// Busca binária por nome
int buscaBinariaPorNome(Componente comp[], int n, char chave[], int *comparacoes) {
    int inicio = 0, fim = n-1;
    while (inicio <= fim) {
        int meio = (inicio+fim)/2;
        (*comparacoes)++;
        int cmp = strcmp(comp[meio].nome, chave);
        if (cmp == 0) return meio;
        else if (cmp < 0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}
