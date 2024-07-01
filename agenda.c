#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTATOS 100
#define MAX_NOME 50
#define MAX_DDD 5
#define MAX_TELEFONE 15
#define ARQUIVO_CONTATOS "contatos.dat"

//armazenar as informacoes de um contato
typedef struct {
    char nome[MAX_NOME];
    char ddd[MAX_DDD];
    char telefone[MAX_TELEFONE];
} Contato;

//armazenar o catalogo de contatos
typedef struct {
    Contato contatos[MAX_CONTATOS];
    int total;
} Catalogo;

// prototipos das funcoes
void adicionar_contato(Catalogo *catalogo, char *nome, char *ddd, char *telefone);
void pesquisar_contato_nome(Catalogo *catalogo, char *nome);

void excluir_contato(Catalogo *catalogo, char *nome);
void excluir_todos_contatos(Catalogo *catalogo);
void salvar_contatos(Catalogo *catalogo);
void carregar_contatos(Catalogo *catalogo);
void ordenar_contatos(Catalogo *catalogo);
void exibir_contatos(Catalogo *catalogo);

int main() {
    Catalogo catalogo;
    catalogo.total = 0;

    carregar_contatos(&catalogo);

    int opcao;
    char nome[MAX_NOME];
    char ddd[MAX_DDD];
    char telefone[MAX_TELEFONE];

    do {
        printf("\nCatalogo de Contatos\n");
        printf("1. Adicionar Contato\n");
        printf("2. Pesquisar Contato por Nome\n");
        printf("3. Excluir Contato\n");
        printf("4. Salvar Contatos\n");
        printf("5. Carregar Contatos\n");
        printf("6. Exibir Contatos\n");
        printf("7. Excluir Todos os Contatos\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                printf("Digite o nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite o DDD: ");
                fgets(ddd, MAX_DDD, stdin);
                ddd[strcspn(ddd, "\n")] = '\0'; 
                printf("Digite o telefone: ");
                fgets(telefone, MAX_TELEFONE, stdin);
                telefone[strcspn(telefone, "\n")] = '\0';
                adicionar_contato(&catalogo, nome, ddd, telefone);
                break;
            case 2:
                printf("Digite o nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                pesquisar_contato_nome(&catalogo, nome);
                break;
            case 3:
                printf("Digite o nome: ");
                fgets(nome, MAX_NOME, stdin);
                nome[strcspn(nome, "\n")] = '\0';
                excluir_contato(&catalogo, nome);
                break;
            case 4:
                salvar_contatos(&catalogo);
                break;
            case 5:
                carregar_contatos(&catalogo);
                break;
            case 6:
                exibir_contatos(&catalogo);
                break;
            case 7:
                excluir_todos_contatos(&catalogo);
                break;
            case 0:
                salvar_contatos(&catalogo);
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while (opcao != 0);

    return 0;
}

// funcao adicionar um novo contato
void adicionar_contato(Catalogo *catalogo, char *nome, char *ddd, char *telefone) {
    int telefone_len = strlen(telefone);
    if (telefone_len < 9 || telefone_len > 12) {
        printf("Erro: O telefone deve ter entre 9 e 12 numeros.\n");
        return;
    }
    if (catalogo->total < MAX_CONTATOS) {
        strncpy(catalogo->contatos[catalogo->total].nome, nome, MAX_NOME);
        strncpy(catalogo->contatos[catalogo->total].ddd, ddd, MAX_DDD);
        strncpy(catalogo->contatos[catalogo->total].telefone, telefone, MAX_TELEFONE);
        catalogo->total++;
        printf("Contato adicionado com sucesso!\n");
    } else {
        printf("Catalogo cheio, nao e possivel adicionar mais contatos.\n");
    }
}

// funcao pesquisar um contato pelo nome
void pesquisar_contato_nome(Catalogo *catalogo, char *nome) {
    int i;
    for (i = 0; i < catalogo->total; i++) {
        if (strcmp(catalogo->contatos[i].nome, nome) == 0) {
            printf("Contato encontrado: %s - (%s) %s\n", catalogo->contatos[i].nome, catalogo->contatos[i].ddd, catalogo->contatos[i].telefone);
            return;
        }
    }
    printf("Contato nao encontrado.\n");
}

// funcao excluir um contato pelo nome
void excluir_contato(Catalogo *catalogo, char *nome) {
    int i, j;
    for (i = 0; i < catalogo->total; i++) {
        if (strcmp(catalogo->contatos[i].nome, nome) == 0) {
            for (j = i; j < catalogo->total - 1; j++) {
                catalogo->contatos[j] = catalogo->contatos[j + 1];
            }
            catalogo->total--;
            printf("Contato excluido com sucesso!\n");
            return;
        }
    }
    printf("Contato nao encontrado.\n");
}

// funcao excluir todos os contatos do catalogo
void excluir_todos_contatos(Catalogo *catalogo) {
    catalogo->total = 0;
    printf("Todos os contatos foram excluidos.\n");
}

// funcao salvar os contatos no disco
void salvar_contatos(Catalogo *catalogo) {
    FILE *arquivo = fopen(ARQUIVO_CONTATOS, "wb");
    if (arquivo != NULL) {
        fwrite(catalogo, sizeof(Catalogo), 1, arquivo);
        fclose(arquivo);
        printf("Contatos salvos com sucesso!\n");
    } else {
        printf("Erro ao salvar contatos.\n");
    }
}

// funcao carregar os contatos do disco
void carregar_contatos(Catalogo *catalogo) {
    FILE *arquivo = fopen(ARQUIVO_CONTATOS, "rb");
    if (arquivo != NULL) {
        fread(catalogo, sizeof(Catalogo), 1, arquivo);
        fclose(arquivo);
        printf("Contatos carregados com sucesso!\n");
    } else {
        catalogo->total = 0;
        printf("Nenhum contato para carregar.\n");
    }
}

// funcao exibir todos os contatos 
void exibir_contatos(Catalogo *catalogo) {
    int i;

    printf("\nLista de Contatos:\n");
    printf("--------------------------------------------------------\n");
    printf("| %-30s | %-4s | %-12s |\n", "Nome", "DDD", "Telefone");
    printf("--------------------------------------------------------\n");

    for (i = 0; i < catalogo->total; i++) {
        printf("| %-30s | %-4s | %-12s |\n", catalogo->contatos[i].nome, catalogo->contatos[i].ddd, catalogo->contatos[i].telefone);
    }

    printf("--------------------------------------------------------\n");
}

