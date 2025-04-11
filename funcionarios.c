#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "data.h"

int numeroDeFuncionarios;
int totalFuncionarios=0;

Funcionario* funcionarios;

void inicializarFuncionarios(){
	printf("Quantos funcionarios tem a sua empresa?: ");
	scanf("%d",&numeroDeFuncionarios);
	funcionarios = (Funcionario*)malloc(numeroDeFuncionarios * sizeof(Funcionario));
}

void adicionarFuncionario(){
	if (totalFuncionarios >= numeroDeFuncionarios) {
        printf("Limite de funcionarios atingido.\n");
        return;
    }
	Funcionario f;
	f.id = totalFuncionarios++;
	
	fflush(stdin);
	printf("Nome: ");
	gets(f.nome);

	printf("Funcao: ");
	gets(f.funcao);
	

	printf("Descricao: ");
	gets(f.descricao);
	
	funcionarios[totalFuncionarios] = f;
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
	for(int i=1;i<=totalFuncionarios;i++){
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
   
    
    for(int i=1;i<=totalFuncionarios;i++){
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


