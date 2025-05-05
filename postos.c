#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "operacoes.h"
#include "funcionarios.h"
#include "util.h"

int numeroDePostos;
int totalPostos = 0;

PostoTrabalho* postos = NULL;

//----------------------------- Base de dados (arquivos em txt) para Postos ------------------------------

void salvarConfiguracaoPostos() {
    FILE *arquivo = fopen("config_postos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a configuracao dos postos.\n");
        return;
    }
    fprintf(arquivo, "%d\n", numeroDePostos);
    fclose(arquivo);
}

void carregarConfiguracaoPostos() {
    FILE *arquivo = fopen("config_postos.txt", "r");
    if (arquivo == NULL) {
        printf("Digite o numero maximo de postos de trabalho: ");
        scanf("%d", &numeroDePostos);
        salvarConfiguracaoPostos();
    } else {
        fscanf(arquivo, "%d", &numeroDePostos);
        fclose(arquivo);
    }
}

void salvarPostosEmArquivo() {
    FILE *arquivo = fopen("postos.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de postos para escrita.\n");
        return;
    }

    for (int i = 0; i < totalPostos; i++) {
        fprintf(arquivo, "%d;%d;%s;%s;%s;%s\n",
                postos[i].id,
                postos[i].idFuncionario,
                postos[i].nome,
                postos[i].local,
                postos[i].secao,
                postos[i].descricao);
    }

    fclose(arquivo);
}

void carregarPostosDoArquivo() {
    FILE *arquivo = fopen("postos.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    totalPostos = 0;
    while (fscanf(arquivo, "%d;%d;%[^;];%[^;];%[^;];%[^\n]\n",
                  &postos[totalPostos].id,
                  &postos[totalPostos].idFuncionario,
                  postos[totalPostos].nome,
                  postos[totalPostos].local,
                  postos[totalPostos].secao,
                  postos[totalPostos].descricao) == 6) {
        totalPostos++;
    }

    fclose(arquivo);
}

void finalizarPostos() {
    salvarPostosEmArquivo();
    free(postos);
    postos = NULL;
}

//---------------------------------------------------------------------------------------------------------

void inicializarPostos() {
    carregarConfiguracaoPostos();
    postos = (PostoTrabalho*)malloc(numeroDePostos * sizeof(PostoTrabalho));
    carregarPostosDoArquivo();
}

void alterarLimitePostos() {
    printf("Digite o novo limite de postos de trabalho: ");
    scanf("%d", &numeroDePostos);
    postos = (PostoTrabalho*)realloc(postos, numeroDePostos * sizeof(PostoTrabalho));
    salvarConfiguracaoPostos();
    printf("Limite de postos alterado com sucesso!\n");
}

int funcExiste(int idFuncionario) {
    for (int i = 0; i < totalFuncionarios; i++) {
        if (funcionarios[i].id == idFuncionario) {
            return 1; 
        }
    }
    return 0; 
}


char* obterNomeFuncionarioPorId(int idFuncionario) {
    for (int i = 0; i < totalFuncionarios; i++) {
        if (funcionarios[i].id == idFuncionario) {
            return funcionarios[i].nome;
        }
    }
    return NULL; // Retorna NULL se o ID não for encontrado
}


void adicionarPosto() {
    if (totalPostos >= numeroDePostos) {
        printf("Limite de postos de trabalho atingido.\n");
        return;
    }

    PostoTrabalho p;
    p.id = totalPostos;
    
    
    do
	{
	   fflush(stdin);
    printf("ID do Funcionario Responsavel: ");
    scanf("%d", &p.idFuncionario);

    if (!funcExiste(p.idFuncionario)) {
        printf("Funcionario com o ID %d nao encontrado.\n", p.idFuncionario);
    }
		
	}while(!funcExiste(p.idFuncionario));
    
    char *nomeFuncionario = obterNomeFuncionarioPorId(p.idFuncionario);
    strcpy(p.nome, nomeFuncionario); // copia o nome para o campo do posto

    
    fflush(stdin);
    /*
    printf("Nome: ");
    gets(p.nome);
    */
    
    printf("Local: ");
    gets(p.local);
    
    printf("Secao: ");
    gets(p.secao);
    
    fflush(stdin);
    printf("Descricao: ");
    gets(p.descricao);

    postos[totalPostos] = p;
    totalPostos++;

    salvarPostosEmArquivo();
    printf("Posto de trabalho adicionado com sucesso!\n");
}


void listarPostos() {
    system("cls");
    printf("\n======= Postos de Trabalho ==========\n");
    if (totalPostos == 0) {
        printf("Nenhum posto de trabalho cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalPostos; i++) {
        printf("ID: %d\nID Funcionario: %d\nNome: %s\nLocal: %s\nSecao: %s\nDescricao: %s\n\n",
               postos[i].id,
               postos[i].idFuncionario,
               postos[i].nome,
               postos[i].local,
               postos[i].secao,
               postos[i].descricao);
    }
}

void pesquisarPostoNome() {
    char nome[50];

    fflush(stdin);
    printf("Digite o nome do posto: ");
    gets(nome);

    for (int i = 0; i < totalPostos; i++) {
        if (strcmp(postos[i].nome, nome) == 0) {
            printf("Encontrado:\nID: %d\nID Funcionario: %d\nNome: %s\nLocal: %s\nSecao: %s\nDescricao: %s\n",
                   postos[i].id,
                   postos[i].idFuncionario,
                   postos[i].nome,
                   postos[i].local,
                   postos[i].secao,
                   postos[i].descricao);
            return;
        }
    }

    printf("Posto de trabalho nao encontrado.\n");
}

void pesquisarPostosComWildcards() {
    char termo[100];
    printf("Digite o termo de busca com wildcards (* e ?): ");
    fflush(stdin);
    scanf(" %[^\n]", termo);

    int encontrados = 0;
    for (int i = 0; i < totalPostos; i++) {
        if (comparaComWildcards(postos[i].nome, termo) ||
            comparaComWildcards(postos[i].local, termo) ||
            comparaComWildcards(postos[i].secao, termo) ||
            comparaComWildcards(postos[i].descricao, termo)) {

            printf("\nID: %d\n", postos[i].id);
            printf("Nome: %s\n", postos[i].nome);
            printf("Local: %s\n", postos[i].local);
            printf("Secao: %s\n", postos[i].secao);
            printf("Descricao: %s\n", postos[i].descricao);
            printf("ID do Funcionario Responsavel: %d\n", postos[i].idFuncionario);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum posto de trabalho encontrado com o termo fornecido.\n");
    }
}

void pesquisarPosto() {
    int opcao;
    printf("Pesquisar Posto de Trabalho por:\n1. Nome\n2. Wildcards\nOpcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    if (opcao == 1) {
        pesquisarPostoNome(); 
    } else if (opcao == 2) {
        pesquisarPostosComWildcards();
    } else {
        printf("Opcao invalida.\n");
    }
}



void alterarPosto() {
    int id;
    printf("ID do posto a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalPostos; i++) {
        if (postos[i].id == id) {
        	
             
            do
			{
				fflush(stdin);
				printf("Novo ID do Funcionario Responsavel: ");
                scanf("%d", &postos[i].idFuncionario);

   				if (!funcExiste(postos[i].idFuncionario)) {
        			printf("Funcionario com o ID %d nao encontrado.\n", postos[i].idFuncionario);
   				 }
			}while(!funcExiste(postos[i].idFuncionario));
            
            
            
            char *nomeFuncionario = obterNomeFuncionarioPorId(postos[i].idFuncionario);
            strcpy(postos[i].nome, nomeFuncionario);
            
            /*printf("Novo nome: ");
            gets(postos[i].nome);*/
            
            fflush(stdin);
            printf("Novo local: ");
            gets(postos[i].local);

            printf("Nova secao: ");
            gets(postos[i].secao);
            
            fflush(stdin);
            printf("Nova descricao: ");
            gets(postos[i].descricao);

            printf("Posto alterado com sucesso.\n");
            salvarPostosEmArquivo();
            return;
        }
    }

    printf("Posto de trabalho nao encontrado.\n");
}

int postoEmUso(int idPosto) {
    for (int i = 0; i < totalOperacoes; i++) {
        if (operacoes[i].idPosto == idPosto) {
            return 1; 
        }
    }
    return 0; 
}

void removerPosto() {
    int id;
    printf("ID do posto a remover: ");
    scanf("%d", &id);

    if (postoEmUso(id)) {
        printf("Este posto de trabalho esta associado a uma ou mais operacoees e nao pode ser removido.\n");
        return;
    }

    for (int i = 0; i < totalPostos; i++) {
        if (postos[i].id == id) {
            for (int j = i; j < totalPostos - 1; j++) {
                postos[j] = postos[j + 1];
            }
            totalPostos--;
            salvarPostosEmArquivo(); 
            printf("Posto de trabalho removido com sucesso.\n");
            return;
        }
    }
    printf("Posto de trabalho nao encontrado.\n");
}

