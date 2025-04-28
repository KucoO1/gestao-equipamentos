// main.c

#include <stdio.h>
#include "interface.h"
#include "funcionarios.h"
#include "postos.h"
#include "empresas.h"
#include "operacoes.h"
#include "componentes.h"
#include <stdlib.h>


int main() {
    int opcao, opc1, opc2,opc0,opc;
    do {
        opcao = menuPrincipal();
    switch (opcao) {
        case 1:
    system("cls");
    inicializarComponentes(); 
    do {
        opc0 = menuComponentes();
        switch (opc0) {
            case 1:
                system("cls");
                adicionarComponente();
                break;
            case 2:
                system("cls");
                listarComponentes();
                break;
            case 3:
                system("cls");
                pesquisarComponente();
                break;
            case 4:
                system("cls");
                alterarComponente();
                break;
            case 5:
                system("cls");
                removerComponente();
                break;
            case 0:
                printf("Saindo do menu de componentes...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opc0 != 0);
    finalizarComponentes();
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
             		case 6:
             			system("cls");
             			alterarLimiteFuncionarios();
             			break;
             		case 0:
             			printf("Saindo do menu de funcionarios");
             			break;
             		default:
             			printf("Opcao Invalida");
				 }

				 }while(opc1!=0);
             	finalizar();
                break;
            case 3:
                system("cls");
    			inicializarEmpresas(); 
    			do {
        			opc =  menuEmpresas(); 
        			switch (opc) {
            			case 1:
                			system("cls");
                			adicionarEmpresa();
                		break;
            			case 2:
                			listarEmpresas();
               			 	break;
            			case 3:
                			system("cls");
                			pesquisarEmpresa();
                			break;
            			case 4:
                			system("cls");
                			alterarEmpresa();
                			break;
            			case 5:
                			system("cls");
                			removerEmpresa();
                		break;
            			case 0:
                			printf("Saindo do menu de empresas...\n");
                			break;
            			default:
                			printf("Opcao invalida.\n");
        			}
    			} while (opc != 0);
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
            	system("cls");
            	carregarOperacoesDoArquivo();
                do{
             		opc2 = menuOperacoes();
             		switch(opc2){
             		case 1:
             			system("cls");
             			inserirOperacao();
             			break;
             		case 2:
             			system("cls");
             			listarOperacoes();
             			break;
             		case 3:
             			system("cls");
             			pesquisarOperacao();
             			break;
             		case 4:
             			system("cls");
             			alterarOperacao();
             			break;
             		case 5:
             			system("cls");
             			apagarOperacao();
             			break;
             		case 0:
             			printf("Saindo do menu de operacoes");
             			break;
             		default:
             			printf("Opcao invalida");
				 }
				 }while(opc2!=0);

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
