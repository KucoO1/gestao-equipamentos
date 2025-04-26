
#include <stdio.h>
#include "interface.h"
#include "funcionarios.h"
#include "postos.h"
#include "empresas.h"
#include "componentes.h"




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

int menuComponentes() {
    int opcao;
    printf("\n==== GESTÃO DE COMPONENTES ====\n");
    printf("1. Adicionar Componente\n");
    printf("2. Listar Componentes\n");
    printf("3. Pesquisar Componente\n");
    printf("4. Alterar Componente\n");
    printf("5. Remover Componente\n");
    printf("0. Sair\n");
    printf("\n==============================\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);
    return opcao;
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

int menuEmpresas() {
    int opc;
    printf("\n==== GESTAO DE EMPRESAS ====\n");
    printf("1. Adicionar Empresa\n");
    printf("2. Listar Empresas\n");
    printf("3. Pesquisar Empresa\n");
    printf("4. Alterar Empresa\n");
    printf("5. Remover Empresa\n");
    printf("0. Sair\n");
    printf("\n================================\n");
    scanf("%d", &opc);
    return opc;
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
