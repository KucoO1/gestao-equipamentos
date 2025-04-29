#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "operacoes.h"

int numeroDeEmpresas;
int totalEmpresas = 0;
Empresa* empresas;

//-------------------------------------- Base de dados (arquivos em txt) ----------------------------------------

void salvarConfiguracaoEmpresas() {
    FILE *arquivo = fopen("configEmpresas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a configuracao de empresas.\n");
        return;
    }
    fprintf(arquivo, "%d\n", numeroDeEmpresas);
    fclose(arquivo);
}

void carregarConfiguracaoEmpresas() {
    FILE *arquivo = fopen("configEmpresas.txt", "r");
    if (arquivo == NULL) {
        printf("Digite o numero maximo de empresas: ");
        scanf("%d", &numeroDeEmpresas);
        salvarConfiguracaoEmpresas();
    } else {
        fscanf(arquivo, "%d", &numeroDeEmpresas);
        fclose(arquivo);
    }
}

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
    carregarConfiguracaoEmpresas();
    empresas = (Empresa*) malloc(numeroDeEmpresas * sizeof(Empresa));
    if (empresas == NULL) {
        printf("Erro ao alocar memoria para empresas.\n");
        exit(1);
    }
    carregarEmpresasDoArquivo();
}

void alterarLimiteEmpresas() {
    printf("Digite o novo limite de empresas: ");
    scanf("%d", &numeroDeEmpresas);
    empresas = (Empresa*) realloc(empresas, numeroDeEmpresas * sizeof(Empresa));
    if (empresas == NULL) {
        printf("Erro ao realocar memoria.\n");
        exit(1);
    }
    salvarConfiguracaoEmpresas();
    printf("Limite de empresas alterado com sucesso!\n");
}

void finalizarEmpresas() {
    salvarEmpresasEmArquivo();
    free(empresas);
}

//--------------------------------------------------------------------------------------------------------------

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

    printf("Empresa nao encontrada.\n");
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
    printf("Empresa nao encontrada.\n");
}


int empresaEstaEmOperacoes(int idEmpresa) {
    for (int i = 0; i < totalOperacoes; i++) {
        if (operacoes[i].idEmpresa == idEmpresa) {
            return 1; // Encontrada ligação
        }
    }
    return 0; // Sem ligação
}


void removerEmpresa() {
    int id;
    printf("ID da empresa a remover: ");
    scanf("%d", &id);

  if(empresaEstaEmOperacoes(id)) {
        printf("Erro: Esta empresa esta associada a uma ou mais operacoes. Nao pode ser removida.\n");
        return;
    }
    else
    {
       for (int i = 0; i < totalEmpresas; i++) 
	   {
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
	}

    
    printf("Empresa nao encontrada.\n");
}
