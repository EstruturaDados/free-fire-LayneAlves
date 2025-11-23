#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_ITENS 10


// Struct que representa um item

typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

// Protótipos das funções
void inserirItem(Item mochila[], int *numItens);
void removerItem(Item mochila[], int *numItens);
void listarItens(Item mochila[], int numItens);
void buscarItem(Item mochila[], int numItens);

// Função principal
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    int opcao;

    do {
        printf("\n= MOCHILA – FREE FIRE =\n");
        printf("1 – Cadastrar item\n");
        printf("2 – Remover item\n");
        printf("3 – Listar itens\n");
        printf("4 – Buscar item (sequencial)\n");
        printf("0 – Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar(); // limpa buffer do enter

        switch (opcao) {
            case 1:
                inserirItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 2:
                removerItem(mochila, &numItens);
                listarItens(mochila, numItens);
                break;
            case 3:
                listarItens(mochila, numItens);
                break;
            case 4:
                buscarItem(mochila, numItens);
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);

    return 0;
}

// Inserir item no vetor
void inserirItem(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("\nA mochila está cheia!\n");
        return;
    }

    printf("\nNome do item: ");
    fgets(mochila[*numItens].nome, 30, stdin);
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = '\0';

    printf("Tipo (arma, municao, cura): ");
    fgets(mochila[*numItens].tipo, 20, stdin);
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*numItens].quantidade);
    getchar();

    (*numItens)++;

    printf("\nItem cadastrado com sucesso!\n");
}

// Remover item pelo nome

void removerItem(Item mochila[], int *numItens) {
    if (*numItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    char nomeBusca[30]; 
    printf("\nDigite o nome do item que deseja remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < *numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            // mover itens para "fechar o buraco"
            for (int j = i; j < *numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            (*numItens)--;
            printf("\nItem removido com sucesso!\n");
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}


// Listar todos os itens

void listarItens(Item mochila[], int numItens) {
    if (numItens == 0) {
        printf("\nA mochila está vazia!\n");
        return;
    }

    printf("\n= ITENS NA MOCHILA =\n");
    for (int i = 0; i < numItens; i++) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade);
    }
}

// Busca sequencial
void buscarItem(Item mochila[], int numItens) {
    char nomeBusca[30];

    printf("\nDigite o nome do item que deseja buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            printf("\nItem encontrado!\n");
            printf("Nome: %s\nTipo: %s\nQuantidade: %d\n",
                   mochila[i].nome,
                   mochila[i].tipo,
                   mochila[i].quantidade);
            return;
        }
    }

    printf("\nItem não encontrado!\n");
}
