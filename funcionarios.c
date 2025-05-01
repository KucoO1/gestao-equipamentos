#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "data.h"

int numeroDeFuncionarios;
int totalFuncionarios=0;

Funcionario* funcionarios = NULL;

//-------------------------------------- Base de dados (arquivos em txt) ----------------------------------------
void salvarConfiguracao() {
    FILE *arquivo = fopen("config.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a configuracao.\n");
        return;
    }
    fprintf(arquivo, "%d\n", numeroDeFuncionarios);
    fclose(arquivo);
}

void carregarConfiguracao() {
    FILE *arquivo = fopen("config.txt", "r");
    if (arquivo == NULL) {
        printf("Digite o numero maximo de funcionarios: ");
        scanf("%d", &numeroDeFuncionarios);
        salvarConfiguracao(); 
    } else {
        fscanf(arquivo, "%d", &numeroDeFuncionarios);
        fclose(arquivo);
    }
}

void salvarFuncionariosEmArquivo() {
    FILE *arquivo = fopen("funcionarios.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < totalFuncionarios; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                funcionarios[i].id,
                funcionarios[i].nome,
                funcionarios[i].funcao,
                funcionarios[i].descricao);
    }

    fclose(arquivo);
}

void carregarFuncionariosDoArquivo() {
    FILE *arquivo = fopen("funcionarios.txt", "r");
    if (arquivo == NULL) {
        return; 
    }
	totalFuncionarios = 0;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n",
                  &funcionarios[totalFuncionarios].id,
                  funcionarios[totalFuncionarios].nome,
                  funcionarios[totalFuncionarios].funcao,
                  funcionarios[totalFuncionarios].descricao) == 4) {
        totalFuncionarios++;
    }

    fclose(arquivo);
}

void finalizarFuncionarios() {
    salvarFuncionariosEmArquivo();
    free(funcionarios);
    funcionarios = NULL;
}

//--------------------------------------------------------------------------------------------------------------

void inicializarFuncionarios(){
	carregarConfiguracao();
	funcionarios = (Funcionario*)malloc(numeroDeFuncionarios * sizeof(Funcionario));
	carregarFuncionariosDoArquivo();
}
void alterarLimiteFuncionarios() {
    printf("Digite o novo limite de funcionarios: ");
    scanf("%d", &numeroDeFuncionarios);
    funcionarios = (Funcionario*)realloc(funcionarios, numeroDeFuncionarios * sizeof(Funcionario));
    salvarConfiguracao();
    printf("Limite alterado com sucesso!\n");
}

void adicionarFuncionario(){
	if (totalFuncionarios >= numeroDeFuncionarios) {
        printf("Limite de funcionarios atingido.\n");
        return;
    }
	Funcionario f;
	f.id = totalFuncionarios;

	fflush(stdin);
	printf("Nome: ");
	gets(f.nome);

	printf("Funcao: ");
	gets(f.funcao);

	printf("Descricao: ");
	gets(f.descricao);

	funcionarios[totalFuncionarios] = f;
	totalFuncionarios++;
	salvarFuncionariosEmArquivo();
	printf("Funcionario adicionado com sucesso!\n");

}

void listarFuncionarios(){
	system("cls");
	printf("\n======= FUNCIONARIOS ==========\n");
	int i;
	if (totalFuncionarios==0){
		printf("Nenhum funcionario cadastrado.");
		return;
	}
	for (int i = 0; i < totalFuncionarios; i++) {
    printf("ID: %d\nNome: %s\nFuncao: %s\nDescricao: %s\n\n", 
           funcionarios[i].id,
           funcionarios[i].nome,
           funcionarios[i].funcao,
           funcionarios[i].descricao);
}

}
void pesquisarFuncionario() {
	char nome[50];
	
	fflush(stdin);
	printf("Digite o nome do funcionario: ");
	gets(nome);
    
    for(int i=0;i<totalFuncionarios;i++){
        if(strcmp(funcionarios[i].nome, nome) == 0){
    		printf("Encontrado:\nID: %d\nNome: %s\nFuncao: %s\nDescricao: %s\n", 
            funcionarios[i].id, 
            funcionarios[i].nome, 
            funcionarios[i].funcao, 
            funcionarios[i].descricao);
        	return;
        	printf("Funcionario nao encontrado.\n");
	    }
	}  
}
void alterarFuncionario(){
	int id;
	printf("ID do funcionario a alterar: ");
	scanf("%d",&id);
	int i;
	for(i=1;i<=totalFuncionarios;i++){
		if(funcionarios[i].id == id){
			
			fflush(stdin);
			printf("Novo nome: ");
			gets(funcionarios[i].nome);

            printf("Nova funcao: ");
            gets(funcionarios[i].funcao);

            printf("Nova descricao: ");
            gets(funcionarios[i].descricao);

            printf("Funcionario alterado com sucesso.\n");
            return;
		}
	}
}
void removerFuncionario(){
	int id;
    printf("ID do funcionario a remover: ");
    scanf("%d", &id);

    for (int i = 1; i <= totalFuncionarios; i++) {
        if (funcionarios[i].id == id) {
            for (int j = i; j < totalFuncionarios - 1; j++) {
                funcionarios[j] = funcionarios[j + 1];
            }
        	totalFuncionarios--;
        	printf("Funcionario removido com sucesso.\n");
        	return;
    	}
  	}
	 printf("Funcionario nao encontrado.\n"); 
}

