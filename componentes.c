
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"

int numeroDeComponentes;
int totalComponentes = 0;

Componente* componentes = NULL;


void salvarConfiguracaoComponentes() {
    FILE *arquivo = fopen("config_componentes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a configuracao dos componentes.\n");
        return;
    }
    fprintf(arquivo, "%d\n", numeroDeComponentes);
    fclose(arquivo);
}

void carregarConfiguracaoComponentes() {
    FILE *arquivo = fopen("config_componentes.txt", "r");
    if (arquivo == NULL) {
        printf("Digite o numero maximo de componentes: ");
        scanf("%d", &numeroDeComponentes);
        salvarConfiguracaoComponentes();
    } else {
        fscanf(arquivo, "%d", &numeroDeComponentes);
        fclose(arquivo);
    }
}

void salvarComponentesEmArquivo() {
    FILE *arquivo = fopen("componentes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de componentes para escrita.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        fprintf(arquivo, "%d;%s;%s;%s;%d;%d;%d;%s;%s;%d;%s\n",
                componentes[i].id,
                componentes[i].designacao,
                componentes[i].numeroSerie,
                componentes[i].dataAquisicao,
                componentes[i].garantiaMeses,
                componentes[i].idFornecedor,
                componentes[i].idFabricante,
                componentes[i].tipo,
                componentes[i].condicao,
                componentes[i].idPosto,
                componentes[i].observacoes);
    }

    fclose(arquivo);
}

void carregarComponentesDoArquivo() {
    FILE *arquivo = fopen("componentes.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    totalComponentes = 0;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%[^;];%[^;];%d;%[^\n]\n",
                  &componentes[totalComponentes].id,
                  componentes[totalComponentes].designacao,
                  componentes[totalComponentes].numeroSerie,
                  componentes[totalComponentes].dataAquisicao,
                  &componentes[totalComponentes].garantiaMeses,
                  &componentes[totalComponentes].idFornecedor,
                  &componentes[totalComponentes].idFabricante,
                  componentes[totalComponentes].tipo,
                  componentes[totalComponentes].condicao,
                  &componentes[totalComponentes].idPosto,
                  componentes[totalComponentes].observacoes) == 11) {
        totalComponentes++;
    }

    fclose(arquivo);
}

void finalizarComponentes() {
    salvarComponentesEmArquivo();
    free(componentes);
}


void inicializarComponentes() {
    carregarConfiguracaoComponentes();
    componentes = (Componente*)malloc(numeroDeComponentes * sizeof(Componente));
    carregarComponentesDoArquivo();
}

void alterarLimiteComponentes() {
    printf("Digite o novo limite de componentes: ");
    scanf("%d", &numeroDeComponentes);
    componentes = (Componente*)realloc(componentes, numeroDeComponentes * sizeof(Componente));
    salvarConfiguracaoComponentes();
    printf("Limite de componentes alterado com sucesso!\n");
}

void adicionarComponente() {
    if (totalComponentes >= numeroDeComponentes) {
        printf("Limite de componentes atingido.\n");
        return;
    }

    Componente c;
    c.id = totalComponentes;

    fflush(stdin);
    printf("Designacao: ");
    gets(c.designacao);

    printf("Numero de Serie: ");
    gets(c.numeroSerie);

    printf("Data de Aquisicao (dd/mm/yyyy): ");
    gets(c.dataAquisicao);

    printf("Garantia (em meses): ");
    scanf("%d", &c.garantiaMeses);
    fflush(stdin);

    printf("ID do Fornecedor: ");
    scanf("%d", &c.idFornecedor);
    fflush(stdin);

    printf("ID do Fabricante: ");
    scanf("%d", &c.idFabricante);
    fflush(stdin);

    printf("Tipo: ");
    gets(c.tipo);

    printf("Condicao (Novo/Usado): ");
    gets(c.condicao);

    printf("ID do Posto de Trabalho: ");
    scanf("%d", &c.idPosto);
    fflush(stdin);

    printf("Observacoes: ");
    gets(c.observacoes);

    componentes[totalComponentes] = c;
    totalComponentes++;

    salvarComponentesEmArquivo();
    printf("Componente adicionado com sucesso!\n");
}

void listarComponentes() {
    system("cls");
    printf("\n======= COMPONENTES ==========\n");
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        printf("ID: %d\nDesignacao: %s\nNumero de Serie: %s\nData de Aquisicao: %s\nGarantia (meses): %d\nID Fornecedor: %d\nID Fabricante: %d\nTipo: %s\nCondicao: %s\nID Posto: %d\nObservacoes: %s\n\n",
               componentes[i].id,
               componentes[i].designacao,
               componentes[i].numeroSerie,
               componentes[i].dataAquisicao,
               componentes[i].garantiaMeses,
               componentes[i].idFornecedor,
               componentes[i].idFabricante,
               componentes[i].tipo,
               componentes[i].condicao,
               componentes[i].idPosto,
               componentes[i].observacoes);
    }
}

void pesquisarComponente() {
    char designacao[50];

    fflush(stdin);
    printf("Digite a designacao do componente: ");
    gets(designacao);

    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(componentes[i].designacao, designacao) == 0) {
            printf("Encontrado:\nID: %d\nDesignacao: %s\nNumero de Serie: %s\nData de Aquisicao: %s\nGarantia (meses): %d\nID Fornecedor: %d\nID Fabricante: %d\nTipo: %s\nCondicao: %s\nID Posto: %d\nObservacoes: %s\n",
                   componentes[i].id,
                   componentes[i].designacao,
                   componentes[i].numeroSerie,
                   componentes[i].dataAquisicao,
                   componentes[i].garantiaMeses,
                   componentes[i].idFornecedor,
                   componentes[i].idFabricante,
                   componentes[i].tipo,
                   componentes[i].condicao,
                   componentes[i].idPosto,
                   componentes[i].observacoes);
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}

void alterarComponente() {
    int id;
    printf("ID do componente a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == id) {
            fflush(stdin);
            printf("Nova Designacao: ");
            gets(componentes[i].designacao);

            printf("Novo Numero de Serie: ");
            gets(componentes[i].numeroSerie);

            printf("Nova Data de Aquisicao: ");
            gets(componentes[i].dataAquisicao);

            printf("Nova Garantia (em meses): ");
            scanf("%d", &componentes[i].garantiaMeses);
            fflush(stdin);

            printf("Novo ID Fornecedor: ");
            scanf("%d", &componentes[i].idFornecedor);
            fflush(stdin);

            printf("Novo ID Fabricante: ");
            scanf("%d", &componentes[i].idFabricante);
            fflush(stdin);

            printf("Novo Tipo: ");
            gets(componentes[i].tipo);

            printf("Nova Condicao: ");
            gets(componentes[i].condicao);

            printf("Novo ID Posto de Trabalho: ");
            scanf("%d", &componentes[i].idPosto);
            fflush(stdin);

            printf("Novas Observacoes: ");
            gets(componentes[i].observacoes);

            printf("Componente alterado com sucesso.\n");
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}

void removerComponente() {
    int id;
    printf("ID do componente a remover: ");
    scanf("%d", &id);

    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == id) {
            for (int j = i; j < totalComponentes - 1; j++) {
                componentes[j] = componentes[j + 1];
            }
            totalComponentes--;
            printf("Componente removido com sucesso.\n");
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}
