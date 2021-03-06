#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct pessoa {
    char nome[50];
    char code[7];
} PESSOA;

void menu() {
    printf("\n\t\tTrabalho EDA2\n");
    printf("\n1- Cadastrar uma pessoa\n");
    printf("2- Listar pessoas\n");
    printf("3- Pesquisar pessoa\n");
    printf("0- Fechar programa\n");
    printf("\n\tSelecione a opcao desejada: ");
}

void cadastrarPessoa() {
    printf("\n\tCadastro de Pessoa\n");
    PESSOA novaPessoa;
    printf("Nome (sem espacos): ");
    scanf("%s", novaPessoa.nome);
    //scanf(" %[^\n]s", novaPessoa.nome);
    printf("Codigo de 6 digitos: ");
    scanf("%s", novaPessoa.code);

    FILE* file = fopen("pessoas.txt", "a");
    fprintf(file, "%s %s\n", novaPessoa.code, novaPessoa.nome);
    fclose(file);
}

void listarPessoas() {
    printf("\nCodigo\tNome\n");
    FILE* file = fopen("pessoas.txt", "r");
    if (file != NULL) {
        PESSOA pessoa;
        while (!feof(file)) {
            fscanf(file, "%s %s\n", pessoa.code, pessoa.nome);
            printf("%s\t%s\n", pessoa.code, pessoa.nome);
        }
        fclose(file);
    } else {
        printf("\nERRO OU NENHUMA PESSOA CADASTRADA\n");
    }
}

void pesquisarPessoa() {
    printf("\nDigite o codigo de 6 digitos da pessoa que deseja encontrar: ");
    char codeDesejado[7];
    scanf("%s", codeDesejado);
    FILE* file = fopen("pessoas.txt", "r");
    if (file != NULL) {
        int lines = 0;
        PESSOA *pessoas = (PESSOA *) malloc(sizeof(PESSOA));

        for (int i = 0; !feof(file); i++) {
            fscanf(file, "%s %s\n", pessoas[i].code, pessoas[i].nome);
                pessoas = (PESSOA *) realloc(pessoas, (i + 2) * sizeof(PESSOA));
                lines = i + 1;
        }
        fclose(file);

        int existe = 0;
        int posicao_inicial = 0;
        for (int i = 0; i < lines; i++) {
            if (strcmp(codeDesejado, pessoas[i].code) == 0) {
                printf("\nNome: %s\n", pessoas[i].nome);
                printf("Code: %s\n", pessoas[i].code);
                existe = 1;

                PESSOA aux;
                strcpy(aux.code, pessoas[posicao_inicial].code);
                strcpy(aux.nome, pessoas[posicao_inicial].nome);

                strcpy(pessoas[posicao_inicial].code, pessoas[i].code);
                strcpy(pessoas[posicao_inicial].nome, pessoas[i].nome);

                strcpy(pessoas[i].code, aux.code);
                strcpy(pessoas[i].nome, aux.nome);

                posicao_inicial ++;
            } else {
                //Nothing to do.
            }
        }
        if (!existe) {
            printf("\nCODIGO NAO CADASTRADO!\n");
        } else {
            FILE* file = fopen("pessoas.txt", "w");
           for (int i = 0; i < lines; i++) {
                fprintf(file, "%s %s\n", pessoas[i].code, pessoas[i].nome);
            }
            fclose(file);
        }
        free(pessoas);
    } else {
        printf("\nERRO OU NENHUMA PESSOA CADASTRADA!\n");
    }
}

int main() {
    int opc;
    do {
        menu();
        scanf("%d", &opc);
        switch (opc) {
            case 0:
                break;

            case 1:
                cadastrarPessoa();
                break;

            case 2:
                listarPessoas();
                break;

            case 3:
                pesquisarPessoa();
                break;

            default:
                printf("\nDIGITE UMA OPCAO VALIDA!!");
                break;
        }
    } while (opc);

    return 0;
}