#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "data.h"

int numeroDePostos;
int totalPostos=0;

 PostoTrabalho* postos;

void inicializarPostos(){
	printf("Quantos postos de trabalho tem a sua empresa?: ");
	scanf("%d",&numeroDePostos);
	postos = (PostoTrabalho*)malloc(numeroDePostos * sizeof(PostoTrabalho));
}

void adicionarPosto(){
	if (totalPostos >= numeroDePostos) {
        printf("Limite de postos de trabalho atingidos.\n");
        return;
    }
	PostoTrabalho p;
	p.id = totalPostos++;
	p.idFuncionario = totalPostos;
	
	fflush(stdin);
	printf("Nome: ");
	gets(p.nome);

	printf("Local: ");
	gets(p.local);

	printf("Secao: ");
	gets(p.secao);
	
	printf("Descricao: ");
	gets(p.descricao);
	
	postos[totalPostos] = p;
	printf("Posto de trabalho adicionado com sucesso!\n");
}
void listarPostos(){
	system("cls");
	printf("\n======= Postos de Trabalho ==========\n");
	int i;
	if (totalPostos==0){
		printf("Nenhum posto de trabalho cadastrado.");
		return;
	}
	for(int i=1;i<=totalPostos;i++){
		 printf("ID: %d\nID Funcionario: %d\nNome: %s\nLocal: %s\nSecao: %s\nDescricao: %s\n", 
            postos[i].id,
            postos[i].idFuncionario,
            postos[i].nome,
            postos[i].local,
            postos[i].secao,
			postos[i].descricao);
	}
}
void pesquisarPosto() {
	char nome[50];
	
	fflush(stdin);
	printf("Digite o nome do posto: ");
	gets(nome);
   
    
    for(int i=1;i<=totalPostos;i++){
        if(strcmp(postos[i].nome, nome) == 0){
    		printf("Encontrado:\nID: %d\nID Funcionario: %d\nNome: %s\nLocal: %s\nSecao: %s\nDescricao: %s\n", 
            postos[i].id,
            postos[i].idFuncionario,
            postos[i].nome, 
            postos[i].local,
             postos[i].secao,
            postos[i].descricao);
        return;
        printf("Posto de trabalho nao encontrado.\n");
		}
	}
}
void alterarPosto(){
	int id;
	printf("ID do posto a alterar: ");
	scanf("%d",&id);
	int i;
	for(i=1;i<=totalPostos;i++){
		if(postos[i].id == id){
			
			fflush(stdin);
			printf("Novo nome: ");
			gets(postos[i].nome);
           
            printf("Novo local: ");
            gets(postos[i].local);
            
            printf("Nova secao: ");
            gets(postos[i].secao);
			
            printf("Nova descricao: ");
            gets(postos[i].descricao);

            printf("Posto alterado com sucesso.\n");
            return;
		}
	}	
}
void removerPosto(){
	int id;
    printf("ID do posto a remover: ");
    scanf("%d", &id);

    for (int i = 1; i <= totalPostos; i++) {
        if (postos[i].id == id) {
            for (int j = i; j < totalPostos - 1; j++) {
                postos[j] = postos[j + 1];
            }
        	totalPostos--;
        	printf("Posto de trabalho removido com sucesso.\n");
        	return;
    	}
  	}
	 printf("Posto de trabalho nao encontrado.\n"); 
}
    