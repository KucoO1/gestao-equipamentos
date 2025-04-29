
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

int menuComponentes() {
    int opc0;
    printf("\n==== GESTAO DE COMPONENTES ====\n");
    printf("1. Adicionar Componente\n");
    printf("2. Listar Componentes\n");
    printf("3. Pesquisar Componente\n");
    printf("4. Alterar Componente\n");
    printf("5. Remover Componente\n");
    printf("0. Sair\n");
    printf("\n==============================\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opc0);
    return opc0;
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

int menuOperacoes() {
    int opc3;

    printf("\n=== MENU OPERACOES ===\n");
    printf("1. Inserir Operacao\n");
    printf("2. Listar Operacoes\n");
    printf("3. Pesquisar Operacoes\n");
    printf("4. Alterar Operacao\n");
    printf("5. Remover Operacao\n");
    printf("6. Consultas\n");
    printf("0. Sair\n");
    printf("Opcao: ");
    scanf("%d", &opc3);
    
    

    return opc3;
}

// Submenu para Consultas específicas
int menuConsultas() {
	int opc4;
    
        printf("\n=== Menu de Consultas ===\n");
        printf("1. Componentes que ultrapassaram a data prevista de chegada\n");
        printf("2. Componentes por Posto de Trabalho\n");
        printf("3. Componentes fora do Posto de Trabalho (em operacoes)\n");
        printf("4. Componentes presentes no Posto de Trabalho\n");
        printf("5. Pesquisar Empresas ou Componentes (por nome, ID ou numero de serie)\n");
        printf("0. Voltar ao menu de operacoes\n");
        printf("Opcao: ");
        scanf("%d", &opc4);
        
	
	return opc4;
}
