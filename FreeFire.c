#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

// =========================
//        STRUCT ITEM
// =========================
typedef struct {
    char nome[30];
    char tipo[30];
    int quantidade;
    int prioridade; // 1 a 5
} Item;

// =========================
//  ENUM CRITÉRIO DE ORDENAÇÃO
// =========================
typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO,
    ORDENAR_PRIORIDADE
} CriterioOrdenacao;

// Vetor mochila
Item mochila[MAX];
int numItens = 0;
bool ordenadaPorNome = false;

// =========================
//        FUNÇÕES
// =========================

void limparTela() {
    for (int i = 0; i < 30; i++)
        printf("\n");
}

void exibirMenu() {
    printf("\n====== MOCHILA — FREE FIRE ======\n");
    printf("Itens na mochila: %d/%d\n", numItens, MAX);
    printf("Ordenada por nome? %s\n", ordenadaPorNome ? "SIM" : "NAO");
    printf("-----------------------------------\n");
    printf("1. Adicionar um item\n");
    printf("2. Remover um item\n");
    printf("3. Listar todos os itens\n");
    printf("4. Ordenar os itens\n");
    printf("5. Busca binária por nome\n");
    printf("0. Sair\n");
    printf("Escolha: ");
}

// ============================
//      INSERIR ITEM
// ============================
void inserirItem() {
    if (numItens >= MAX) {
        printf("⚠️ Mochila cheia! Não é possível adicionar mais itens.\n");
        return;
    }

    Item novo;

    printf("Nome do item: ");
    fgets(novo.nome, 30, stdin);
    novo.nome[strcspn(novo.nome, "\n")] = 0;

    printf("Tipo do item: ");
    fgets(novo.tipo, 30, stdin);
    novo.tipo[strcspn(novo.tipo, "\n")] = 0;

    printf("Quantidade: ");
    scanf("%d", &novo.quantidade);

    printf("Prioridade (1 a 5): ");
    scanf("%d", &novo.prioridade);
    getchar();

    mochila[numItens++] = novo;
    ordenadaPorNome = false;

    printf("✔ Item adicionado com sucesso!\n");
}

// ============================
//      REMOVER ITEM
// ============================
void removerItem() {
    if (numItens == 0) {
        printf("⚠️ Mochila vazia!\n");
        return;
    }

    char nomeBusca[30];
    printf("Digite o nome do item a remover: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    for (int i = 0; i < numItens; i++) {
        if (strcmp(mochila[i].nome, nomeBusca) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("✔ Item removido!\n");
            return;
        }
    }

    printf("❌ Item não encontrado.\n");
}

// ============================
//      LISTAR ITENS
// ============================
void listarItens() {
    if (numItens == 0) {
        printf("⚠️ Mochila vazia!\n");
        return;
    }

    printf("\n====== ITENS NA MOCHILA ======\n");
    for (int i = 0; i < numItens; i++) {
        printf("[%d] %s | %s | Qtd: %d | Prio: %d\n",
               i + 1,
               mochila[i].nome,
               mochila[i].tipo,
               mochila[i].quantidade,
               mochila[i].prioridade);
    }
}

// ============================
//      INSERTION SORT
// ============================
void insertionSort(CriterioOrdenacao criterio) {
    int comparacoes = 0;

    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;

        while (j >= 0) {
            bool cond = false;

            if (criterio == ORDENAR_NOME)
                cond = strcmp(mochila[j].nome, chave.nome) > 0;

            else if (criterio == ORDENAR_TIPO)
                cond = strcmp(mochila[j].tipo, chave.tipo) > 0;

            else if (criterio == ORDENAR_PRIORIDADE)
                cond = mochila[j].prioridade < chave.prioridade;

            comparacoes++;

            if (!cond) break;

            mochila[j + 1] = mochila[j];
            j--;
        }
        mochila[j + 1] = chave;
    }

    printf("✔ Ordenação concluída! Comparações: %d\n", comparacoes);

    ordenadaPorNome = (criterio == ORDENAR_NOME);
}

// ============================
//      MENU DE ORDENAÇÃO
// ============================
void menuDeOrdenacao() {
    printf("\nOrdenar por:\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Tipo (A-Z)\n");
    printf("3. Prioridade (5 → 1)\n");
    printf("Escolha: ");

    int op;
    scanf("%d", &op);
    getchar();

    if (op < 1 || op > 3) {
        printf("⚠️ Opção inválida.\n");
        return;
    }

    insertionSort((CriterioOrdenacao)op);
}

// ============================
//      BUSCA BINÁRIA
// ============================
void buscaBinariaPorNome() {
    if (!ordenadaPorNome) {
        printf("⚠️ A busca binária exige que os itens estejam ordenados por nome!\n");
        return;
    }

    char nomeBusca[30];
    printf("Nome do item a buscar: ");
    fgets(nomeBusca, 30, stdin);
    nomeBusca[strcspn(nomeBusca, "\n")] = 0;

    int ini = 0, fim = numItens - 1;

    while (ini <= fim) {
        int meio = (ini + fim) / 2;
        int cmp = strcmp(nomeBusca, mochila[meio].nome);

        if (cmp == 0) {
            printf("✔ Item encontrado!\n");
            printf("%s | %s | Qtd: %d | Prio: %d\n",
                mochila[meio].nome,
                mochila[meio].tipo,
                mochila[meio].quantidade,
                mochila[meio].prioridade);
            return;
        }
        else if (cmp > 0)
            ini = meio + 1;
        else
            fim = meio - 1;
    }

    printf("❌ Item não encontrado.\n");
}

// ============================
//           MAIN
// ============================
int main() {
    int opc;

    do {
        exibirMenu();
        scanf("%d", &opc);
        getchar(); // limpar buffer

        limparTela();

        switch (opc) {
            case 1: inserirItem(); break;
            case 2: removerItem(); break;
            case 3: listarItens(); break;
            case 4: menuDeOrdenacao(); break;
            case 5: buscaBinariaPorNome(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("⚠️ Opção inválida!\n");
        }

    } while (opc != 0);

    return 0;
}
