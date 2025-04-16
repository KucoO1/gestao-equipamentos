
#include <stdio.h>
#include "interface.h"
#include "funcionarios.h"
#include "postos.h"


int menuPrincipal() {
    int opcao;
    printf("\n==== SISTEMA DE GESTAO DE EQUIPAMENTOS ====\n");
    printf("1. Gerir Componentes\n");
    printf("2. Gerir Funcionarios\n");
    printf("3. Gerir Empresas\n");
    printf("4. Gerir Postos de Trabalho\n");
    printf("5. Gerir Operacoes\n");
    printf("0. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opcao);
    return opcao;
}

void menuComponentes() {
    printf("Menu de Componentes (em construcao)\n");
}

int menuFuncionarios() {
	int opc1;
    printf("\n==== GESTAO DE FUNCIONARIOS ====\n");
    printf("1. Adicionar Funcionarios\n");
    printf("2. Listar Funcionarios\n");
    printf("3. Pesquisar Funcionario\n");
    printf("4. Alterar Funcionario\n");
    printf("5. Remover Funcionario\n");
    printf("6. Alterar limite de funcionarios\n");
    printf("0. Sair\n");
    printf("\n================================\n");
  	scanf("%d",&opc1);
  	return opc1;
}

void menuEmpresas() {
    printf("Menu de Empresas (em construcao)\n");
}

int menuPostos() {
    int opc2;
    printf("\n==== GESTAO DE POSTOS DE TRABALHO ====\n");
    printf("1. Adicionar Postos de trablho\n");
    printf("2. Listar Postos de trabaho\n");
    printf("3. Pesquisar Postos de trabalho\n");
    printf("4. Alterar Postos de trabalho\n");
    printf("5. Remover Postos de trabalho\n");
    printf("0. Sair\n");
    printf("\n================================\n");
  	scanf("%d",&opc2);
  	return opc2;
}

void menuOperacoes() {
    printf("Menu de Operacoes (em construcao)\n");
}
