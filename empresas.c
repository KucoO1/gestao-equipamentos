#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int numeroDeEmpresas;
int totalEmpresas = 0;
Empresa* empresas;

void salvarEmpresasEmArquivo() {
    FILE *arquivo = fopen("empresas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < totalEmpresas; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                empresas[i].id,
                empresas[i].nome,
                empresas[i].tipo,
                empresas[i].contacto);
    }

    fclose(arquivo);
}

void carregarEmpresasDoArquivo() {
    FILE *arquivo = fopen("empresas.txt", "r");
    if (arquivo == NULL) return;

    totalEmpresas = 0;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n",
                  &empresas[totalEmpresas].id,
                  empresas[totalEmpresas].nome,
                  empresas[totalEmpresas].tipo,
                  empresas[totalEmpresas].contacto) == 4) {
        totalEmpresas++;
    }

    fclose(arquivo);
}

void inicializarEmpresas() {
    printf("Digite o número máximo de empresas: ");
    scanf("%d", &numeroDeEmpresas);
    empresas = (Empresa*) malloc(numeroDeEmpresas * sizeof(Empresa));
    carregarEmpresasDoArquivo();
}

void adicionarEmpresa() {
    if (totalEmpresas >= numeroDeEmpresas) {
        printf("Limite de empresas atingido.\n");
        return;
    }

    Empresa e;
    e.id = totalEmpresas;

    fflush(stdin);
    printf("Nome da empresa: ");
    gets(e.nome);

    printf("Tipo (Fornecedor, Fabricante, etc.): ");
    gets(e.tipo);

    printf("Contacto: ");
    gets(e.contacto);

    empresas[totalEmpresas] = e;
    totalEmpresas++;
    salvarEmpresasEmArquivo();
    printf("Empresa adicionada com sucesso!\n");
}

void listarEmpresas() {
    system("cls");
    printf("\n======= EMPRESAS =========\n");

    if (totalEmpresas == 0) {
        printf("Nenhuma empresa cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalEmpresas; i++) {
        printf("ID: %d\nNome: %s\nTipo: %s\nContacto: %s\n\n",
               empresas[i].id,
               empresas[i].nome,
               empresas[i].tipo,
               empresas[i].contacto);
    }
}

void pesquisarEmpresa() {
    char nome[50];

    fflush(stdin);
    printf("Digite o nome da empresa: ");
    gets(nome);

    for (int i = 0; i < totalEmpresas; i++) {
        if (strcmp(empresas[i].nome, nome) == 0) {
            printf("\nEncontrado:\nID: %d\nNome: %s\nTipo: %s\nContacto: %s\n",
                   empresas[i].id,
                   empresas[i].nome,
                   empresas[i].tipo,
                   empresas[i].contacto);
            return;
        }
    }

    printf("Empresa não encontrada.\n");
}

void alterarEmpresa() {
    int id;
    printf("ID da empresa a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalEmpresas; i++) {
        if (empresas[i].id == id) {
            fflush(stdin);
            printf("Novo nome: ");
            gets(empresas[i].nome);

            printf("Novo tipo: ");
            gets(empresas[i].tipo);

            printf("Novo contacto: ");
            gets(empresas[i].contacto);

            salvarEmpresasEmArquivo();
            printf("Empresa alterada com sucesso.\n");
            return;
        }
    }
    printf("Empresa não encontrada.\n");
}

void removerEmpresa() {
    int id;
    printf("ID da empresa a remover: ");
    scanf("%d", &id);

    for (int i = 0; i < totalEmpresas; i++) {
        if (empresas[i].id == id) {
            for (int j = i; j < totalEmpresas - 1; j++) {
                empresas[j] = empresas[j + 1];
            }
            totalEmpresas--;
            salvarEmpresasEmArquivo();
            printf("Empresa removida com sucesso.\n");
            return;
        }
    }
    printf("Empresa não encontrada.\n");
}
