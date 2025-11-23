

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITENS 10

// -------------------------------
// Structs
// -------------------------------
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
} Item;

typedef struct No {
    Item dados;
    struct No* proximo;
} No;

// -------------------------------
// Protótipos
// -------------------------------
// Vetor
void inserirItemVetor(Item mochila[], int *numItens);
void removerItemVetor(Item mochila[], int *numItens);
void listarItensVetor(Item mochila[], int numItens);
int buscarSequencialVetor(Item mochila[], int numItens, char* nome, int* comparacoes);
void ordenarVetor(Item mochila[], int numItens);
int buscarBinariaVetor(Item mochila[], int numItens, char* nome, int* comparacoes);

// Lista encadeada
void inserirItemLista(No** cabeca);
void removerItemLista(No** cabeca);
void listarItensLista(No* cabeca);
int buscarSequencialLista(No* cabeca, char* nome, int* comparacoes);

// Utilitários
void limparBufferEntrada();

// -------------------------------
// Função Principal
// -------------------------------
int main() {
    Item mochila[MAX_ITENS];
    int numItens = 0;
    No* cabeca = NULL;
    int estrutura, opcao;

    do {
        printf("\nEscolha a estrutura de dados:\n");
        printf("1 - Vetor\n2 - Lista Encadeada\n0 - Sair\nOpcao: ");
        scanf("%d", &estrutura);
        getchar();

        if (estrutura == 0) break;

        do {
            printf("\n=========== MOCHILA ===========\n");
            printf("1 – Cadastrar item\n");
            printf("2 – Remover item\n");
            printf("3 – Listar itens\n");
            printf("4 – Buscar item (sequencial)\n");
            if (estrutura == 1) printf("5 – Buscar item (binária)\n");
            printf("0 – Voltar\n");
            printf("Escolha: ");
            scanf("%d", &opcao);
            getchar();

            int comparacoes = 0;
            char nomeBusca[30];
            int resultado;

            switch(opcao) {
                case 1:
                    if (estrutura == 1) inserirItemVetor(mochila, &numItens);
                    else inserirItemLista(&cabeca);
                    break;
                case 2:
                    if (estrutura == 1) removerItemVetor(mochila, &numItens);
                    else removerItemLista(&cabeca);
                    break;
                case 3:
                    if (estrutura == 1) listarItensVetor(mochila, numItens);
                    else listarItensLista(cabeca);
                    break;
                case 4:
                    printf("Digite o nome do item a buscar: ");
                    fgets(nomeBusca, 30, stdin);
                    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                    if (estrutura == 1)
                        resultado = buscarSequencialVetor(mochila, numItens, nomeBusca, &comparacoes);
                    else
                        resultado = buscarSequencialLista(cabeca, nomeBusca, &comparacoes);
                    if (resultado != -1) printf("Item encontrado! Comparações: %d\n", comparacoes);
                    else printf("Item não encontrado. Comparações: %d\n", comparacoes);
                    break;
                case 5:
                    if (estrutura == 1) {
                        ordenarVetor(mochila, numItens);
                        printf("Digite o nome do item para busca binária: ");
                        fgets(nomeBusca, 30, stdin);
                        nomeBusca[strcspn(nomeBusca, "\n")] = '\0';
                        comparacoes = 0;
                        resultado = buscarBinariaVetor(mochila, numItens, nomeBusca, &comparacoes);
                        if (resultado != -1) printf("Item encontrado! Comparações: %d\n", comparacoes);
                        else printf("Item não encontrado. Comparações: %d\n", comparacoes);
                    } else printf("Opcao inválida para lista encadeada.\n");
                    break;
                case 0:
                    break;
                default:
                    printf("Opcao invalida!\n");
            }
        } while(opcao != 0);

    } while (estrutura != 0);

    // Libera lista encadeada
    No* atual = cabeca;
    while (atual) {
        No* temp = atual;
        atual = atual->proximo;
        free(temp);
    }

    printf("Saindo do programa...\n");
    return 0;
}

// -------------------------------
// Funções Vetor
// -------------------------------
void inserirItemVetor(Item mochila[], int *numItens) {
    if (*numItens >= MAX_ITENS) {
        printf("A mochila está cheia!\n");
        return;
    }
    printf("Nome: ");
    fgets(mochila[*numItens].nome, 30, stdin);
    mochila[*numItens].nome[strcspn(mochila[*numItens].nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(mochila[*numItens].tipo, 20, stdin);
    mochila[*numItens].tipo[strcspn(mochila[*numItens].tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &mochila[*numItens].quantidade);
    getchar();

    (*numItens)++;
    printf("Item cadastrado com sucesso!\n");
}

void removerItemVetor(Item mochila[], int *numItens) {
    if (*numItens == 0) { printf("A mochila está vazia!\n"); return; }

    char nomeBusca[30];
    printf("Nome do item para remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    for (int i=0; i<*numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j=i; j<*numItens-1; j++)
                mochila[j] = mochila[j+1];
            (*numItens)--;
            printf("Item removido com sucesso!\n");
            return;
        }
    }
    printf("Item não encontrado!\n");
}

void listarItensVetor(Item mochila[], int numItens) {
    if (numItens==0) { printf("A mochila está vazia!\n"); return; }
    for (int i=0; i<numItens; i++)
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i+1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade);
}

int buscarSequencialVetor(Item mochila[], int numItens, char* nome, int* comparacoes) {
    for (int i=0; i<numItens; i++) {
        (*comparacoes)++;
        if (strcmp(mochila[i].nome, nome) == 0) return i;
    }
    return -1;
}

void ordenarVetor(Item mochila[], int numItens) {
    for (int i=0; i<numItens-1; i++) {
        for (int j=0; j<numItens-i-1; j++) {
            if (strcmp(mochila[j].nome, mochila[j+1].nome) > 0) {
                Item temp = mochila[j];
                mochila[j] = mochila[j+1];
                mochila[j+1] = temp;
            }
        }
    }
}

int buscarBinariaVetor(Item mochila[], int numItens, char* nome, int* comparacoes) {
    int inicio=0, fim=numItens-1;
    while (inicio<=fim) {
        int meio = (inicio+fim)/2;
        (*comparacoes)++;
        int cmp = strcmp(mochila[meio].nome, nome);
        if (cmp==0) return meio;
        else if (cmp<0) inicio = meio+1;
        else fim = meio-1;
    }
    return -1;
}

// -------------------------------
// Funções Lista Encadeada
// -------------------------------
void inserirItemLista(No** cabeca) {
    No* novo = (No*) malloc(sizeof(No));
    if (!novo) { printf("Erro de memória!\n"); return; }

    printf("Nome: ");
    fgets(novo->dados.nome, 30, stdin);
    novo->dados.nome[strcspn(novo->dados.nome, "\n")] = '\0';

    printf("Tipo: ");
    fgets(novo->dados.tipo, 20, stdin);
    novo->dados.tipo[strcspn(novo->dados.tipo, "\n")] = '\0';

    printf("Quantidade: ");
    scanf("%d", &novo->dados.quantidade);
    getchar();

    novo->proximo = *cabeca;
    *cabeca = novo;

    printf("Item inserido na lista encadeada!\n");
}

void removerItemLista(No** cabeca) {
    if (!*cabeca) { printf("A lista está vazia!\n"); return; }

    char nomeBusca[30];
    printf("Nome do item para remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = '\0';

    No* atual = *cabeca;
    No* anterior = NULL;

    while (atual) {
        if (strcmp(atual->dados.nome, nomeBusca) == 0) {
            if (anterior) anterior->proximo = atual->proximo;
            else *cabeca = atual->proximo;
            free(atual);
            printf("Item removido da lista!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
    printf("Item não encontrado!\n");
}

void listarItensLista(No* cabeca) {
    if (!cabeca) { printf("A lista está vazia!\n"); return; }
    int i=1;
    while (cabeca) {
        printf("%d) Nome: %s | Tipo: %s | Quantidade: %d\n",
               i++, cabeca->dados.nome, cabeca->dados.tipo, cabeca->dados.quantidade);
        cabeca = cabeca->proximo;
    }
}

int buscarSequencialLista(No* cabeca, char* nome, int* comparacoes) {
    int i=0;
    while (cabeca) {
        (*comparacoes)++;
        if (strcmp(cabeca->dados.nome, nome)==0) return i;
        cabeca = cabeca->proximo;
        i++;
    }
    return -1;
}

// -------------------------------
// Limpar buffer
// -------------------------------
void limparBufferEntrada() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}
