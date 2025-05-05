
#include <stdio.h>
#include "interface.h"
#include "funcionarios.h"
#include "postos.h"
#include <stdlib.h>

void limparTela(){
    system("cls");
}
    

int menuPrincipal() {
    int opcao;
    printf("\n==== SISTEMA DE GESTAO DE EQUIPAMENTOS ====\n");
    printf("1. Gerir Componentes\n");
    printf("2. Gerir Funcionarios\n");
    printf("3. Gerir Empresas\n");
    printf("4. Gerir Postos de Trabalho\n");
    printf("5. Gerir Operacoes\n");
    printf("6. Gerir Estatisticas\n");
    printf("0. Sair\n");
    printf("\n================================\nOpcao:");
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
    printf("5. Alterar o posto de trabalho para um componente\n");
    printf("6. Remover Componente\n");
     printf("7. Gerir Subcomponentes \n");
    printf("0. Sair\n");
    printf("\n================================\nOpcao:");
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
    printf("\n================================\nOpcao:");
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
    printf("6. Menu Ofertas\n");
    printf("0. Sair\n");
    printf("\n================================\nOpcao:");
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
    printf("\n================================\nOpcao:");
  	scanf("%d",&opc2);
  	return opc2;
}

int menuOperacoes() {
    int opc3;

    printf("\n==== MENU OPERACOES ====\n");
    printf("1. Inserir Operacao\n");
    printf("2. Listar Operacoes\n");
    printf("3. Pesquisar Operacoes\n");
    printf("4. Alterar Operacao\n");
    printf("5. Remover Operacao\n");
    printf("6. Consultas\n");
    printf("0. Sair\n");
   printf("\n================================\nOpcao:");
    scanf("%d", &opc3);
    
    

    return opc3;
}

// Extras 



int menuSubComponentes() {
    int opc0;
    printf("\n==== Gerir Subcomponentes ====\n");
    printf("1. Adicionar subcomponente\n");
    printf("2. Alterar subcomponente\n");
    printf("3. Listar subcomponentes\n");
    printf("4. Remover subcomponente\n");
    printf("0. Sair\n");
    printf("\n================================\nOpcao:");
    scanf("%d", &opc0);
    return opc0;
}


int mostrarEstatisticasGerais() {
    int opcao;
        printf("\n===== ESTATISTICAS GERAIS =====\n");
        printf("1. Estatisticas de Ofertas\n");
        printf("2. Estatisticas de Componentes\n");
        printf("3. Estatisticas de Empresas\n");
        printf("4. Estatisticas de Subcomponentes\n");
        printf("0. Voltar\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
         return opcao;
}

int menuOfertas() {
    int opc5;
   
    printf("\n====== GESTAO DE OFERTAS ===========\n");
    printf("1. Adicionar nova oferta de preco/tempo\n");
    printf("2. Listar todas as ofertas existentes\n");
    printf("3. Comparar ofertas por componente\n");
    printf("4. Alterar dados de uma oferta\n");
    printf("5. Remover uma oferta existente\n");
    printf("0. Voltar ao menu das empresas\n");
    printf("=====================================\n");
    printf("Opcao: ");
    scanf("%d", &opc5);
    return opc5;
}

// Submenu para Consultas específicas
int menuConsultas() {
	int opc4;
    
        printf("\n====== Menu de Consultas ======\n");
        printf("1. Componentes que ultrapassaram a data prevista de chegada\n");
        printf("2. Componentes por Posto de Trabalho\n");
        printf("3. Componentes fora do Posto de Trabalho (em operacoes)\n");
        printf("4. Componentes presentes no Posto de Trabalho\n");
        printf("5. Pesquisar Empresas ou Componentes (por nome, ID ou numero de serie)\n");
        printf("0. Voltar ao menu de operacoes\n");
        printf("\n================================\nOpcao:");
        scanf("%d", &opc4);
        
	
	return opc4;
}
