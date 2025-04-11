// main.c

#include <stdio.h>
#include "interface.h"
#include <stdlib.h>

int main() {
    int opcao;
    int opc1;
    int opc2;
    do {
        opcao = menuPrincipal();
        switch (opcao) {
            case 1:
                menuComponentes();
                break;
            case 2:
            	system("cls");
            	inicializarFuncionarios();
             	do{
             		opc1 = menuFuncionarios();
             		switch(opc1){
             		case 1:
             			system("cls");
             			adicionarFuncionario();
             			break;
             		case 2:
             			listarFuncionarios();
             			break;
             		case 3:
             			system("cls");
             			pesquisarFuncionario();
             			break;
             		case 4:
             			system("cls");
             			alterarFuncionario();
             			break;
             		case 5:
             			system("cls");
             			removerFuncionario();
             			break;
             		case 0:
             			printf("Saindo do menu de funcionarios");
             			break;
             		default:
             			printf("Opcao Invalida");
				 }
				 }while(opc1!=0);
             	
                break;
            case 3:
                menuEmpresas();
                break;
            case 4:
                system("cls");
            	inicializarPostos();
             	do{
             		opc2 = menuPostos();
             		switch(opc2){
             		case 1:
             			system("cls");
             			adicionarPosto();
             			break;
             		case 2:
             			listarPostos();
             			break;
             		case 3:
             			system("cls");
             			pesquisarPosto();
             			break;
             		case 4:
             			system("cls");
             			alterarPosto();
             			break;
             		case 5:
             			system("cls");
             			removerPosto();
             			break;
             		case 0:
             			printf("Saindo do menu de posto de trabalho");
             			break;
             		default:
             			printf("Opcao invalida");
				 }
				 }while(opc2!=0);
                break;
            case 5:
                menuOperacoes();
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);
    return 0;
}
