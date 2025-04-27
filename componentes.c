#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "data.h"  

Componente* componentes;
int totalComponentes = 0;

void inicializarComponentes() {
    componentes = (Componente*)malloc(MAX * sizeof(Componente));
    if (componentes == NULL) {
        printf("Erro ao alocar memoria para componentes.\n");
        exit(1);
    }
    carregarComponentesDoArquivo();
}

void finalizarComponentes() {
    salvarComponentesEmArquivo();
    free(componentes);
}

void salvarComponentesEmArquivo() {
    FILE *arquivo = fopen("componentes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar componentes em arquivo.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        fprintf(arquivo, "%d;%s;%s;%s;%d;%d;%d;%s;%s;%s\n", 
                componentes[i].id, 
                componentes[i].designacao, 
                componentes[i].numeroSerie, 
                componentes[i].dataAquisicao,
                componentes[i].garantiaMeses,
                componentes[i].idFornecedor,
                componentes[i].idFabricante,
                componentes[i].tipo,
                componentes[i].condicao,
                componentes[i].observacoes);
    }

    fclose(arquivo);
}

void carregarComponentesDoArquivo() {
    FILE *arquivo = fopen("componentes.txt", "r");
    if (arquivo == NULL) {
        return; 
    }

    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%[^;];%[^;];%[^\n]\n", 
                  &componentes[totalComponentes].id,
                  componentes[totalComponentes].designacao,
                  componentes[totalComponentes].numeroSerie,
                  componentes[totalComponentes].dataAquisicao,
                  &componentes[totalComponentes].garantiaMeses,
                  &componentes[totalComponentes].idFornecedor,
                  &componentes[totalComponentes].idFabricante,
                  componentes[totalComponentes].tipo,
                  componentes[totalComponentes].condicao,
                  componentes[totalComponentes].observacoes) == 10) {
        totalComponentes++;
    }

    fclose(arquivo);
}

void adicionarComponente() {
    if (totalComponentes >= MAX) {
        printf("Limite de componentes atingido.\n");
        return;
    }

    Componente c;
    c.id = totalComponentes + 1;
     printf("Designacao: ");
    gets(c.designacao);

    printf("Numero de Serie: ");
    gets(c.numeroSerie);

    printf("Data de Aquisicao (dd/mm/aaaa): ");
    gets(c.dataAquisicao);

    printf("Garantia (meses): ");
    scanf("%d", &c.garantiaMeses);

    printf("ID do Fornecedor: ");
    scanf("%d", &c.idFornecedor);

    printf("ID do Fabricante: ");
    scanf("%d", &c.idFabricante);

    printf("Tipo: ");
    gets(c.tipo);

    printf("Condicao (Novo/Usado): ");
    gets(c.condicao);

    printf("Observacoes: ");
    gets(c.observacoes);

    componentes[totalComponentes++] = c;
    salvarComponentesEmArquivo();
    printf("Componente adicionado com sucesso!\n");
}

void listarComponentes() {
    printf("\n==== LISTA DE COMPONENTES ====\n");
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        printf("ID: %d | Designacao: %s | Nº Série: %s | Data Aquisicao: %s | Garantia: %d meses | Tipo: %s | Condicao: %s\n", 
                componentes[i].id, 
                componentes[i].designacao,
                componentes[i].numeroSerie, 
                componentes[i].dataAquisicao,
                componentes[i].garantiaMeses,
                componentes[i].tipo, 
                componentes[i].condicao);
    }
}

void pesquisarComponente() {
    int id;
    printf("ID do componente a pesquisar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == id) {
            printf("ID: %d | Designacao: %s | Nº Serie: %s | Data Aquisicao: %s | Garantia: %d meses | Tipo: %s | Condicao: %s | Observacoes: %s\n", 
                    componentes[i].id, 
                    componentes[i].designacao,
                    componentes[i].numeroSerie, 
                    componentes[i].dataAquisicao,
                    componentes[i].garantiaMeses,
                    componentes[i].tipo, 
                    componentes[i].condicao,
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
            printf("Nova designacao: ");
			gets(componentes[i].designacao);

			printf("Novo numero de serie: ");
			gets(componentes[i].numeroSerie);

			printf("Nova data de aquisicao: ");
			gets(componentes[i].dataAquisicao);

			printf("Nova garantia (meses): ");
			scanf("%d", &componentes[i].garantiaMeses);

			printf("Novo ID do fornecedor: ");
			scanf("%d", &componentes[i].idFornecedor);

			printf("Novo ID do fabricante: ");
			scanf("%d", &componentes[i].idFabricante);

			getchar(); 

			printf("Novo tipo: ");
			gets(componentes[i].tipo);

			printf("Nova condicao (Novo/Usado): ");
			gets(componentes[i].condicao);

			printf("Novas observacoes: ");
			gets(componentes[i].observacoes);

			salvarComponentesEmArquivo();
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
            salvarComponentesEmArquivo();
            printf("Componente removido com sucesso.\n");
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}