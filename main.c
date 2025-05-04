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
    
    // Inicialização global dos ficheiros na memória para garantir a consistência dos dados e evitar vazamentos dde memória 
    
    inicializarComponentes(); 
    inicializarFuncionarios();
    inicializarEmpresas(); 
    inicializarPostos();
    carregarOperacoesDoArquivo();
    
    
    do {
    	limparTela();
        opcao = menuPrincipal();
    switch (opcao) {
        case 1:
    limparTela();
    
    do {
        opc0 = menuComponentes();
        switch (opc0) {
            case 1:
                limparTela();
                adicionarComponente();
                break;
            case 2:
                limparTela();
                listarComponentes();
                break;
            case 3:
                limparTela();
                pesquisarComponente();
                break;
            case 4:
                limparTela();
                alterarComponente();
                break;
            case 5:
                limparTela();
                trocarPostoComponente();
                break;
            case 6:
                limparTela();
                removerComponente();
                break;
            case 0:
                printf("Saindo do menu de componentes...\n");
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opc0 != 0);
    break;
     
            case 2:
            	limparTela();
            	
             	do{
             		opc1 = menuFuncionarios();
             		switch(opc1){
             		case 1:
             			limparTela();
             			adicionarFuncionario();
             			break;
             		case 2:
             			listarFuncionarios();
             			break;
             		case 3:
             			limparTela();
             			pesquisarFuncionario();
             			break;
             		case 4:
             			limparTela();
             			alterarFuncionario();
             			break;
             		case 5:
             			limparTela();
             			removerFuncionario();
             			break;
             		case 6:
             			limparTela();
             			alterarLimiteFuncionarios();
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
                limparTela();
    			
    			do {
        			opc =  menuEmpresas(); 
        			switch (opc) {
            			case 1:
                			limparTela();
                			adicionarEmpresa();
                		break;
            			case 2:
                			listarEmpresas();
               			 	break;
            			case 3:
                			limparTela();
                			pesquisarEmpresa();
                			break;
            			case 4:
                			limparTela();
                			alterarEmpresa();
                			break;
            			case 5:
                			limparTela();
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
                limparTela();
            	
             	do{
             		opc2 = menuPostos();
             		switch(opc2){
             		case 1:
             			limparTela();
             			adicionarPosto();
             			break;
             		case 2:
             			listarPostos();
             			break;
             		case 3:
             			limparTela();
             			pesquisarPosto();
             			break;
             		case 4:
             			limparTela();
             			alterarPosto();
             			break;
             		case 5:
             			limparTela();
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
            	limparTela();
            	
                do{
             		opc2 = menuOperacoes();
             		switch(opc2){
             		case 1:
             			limparTela();
             			inserirOperacao();
             			break;
             		case 2:
             			limparTela();
             			listarOperacoes();
             			break;
             		case 3:
             			limparTela();
             			pesquisarOperacao();
             			break;
             		case 4:
             			limparTela();
             			alterarOperacao();
             			break;
             		case 5:
             			limparTela();
             			apagarOperacao();
             			break;
             			
             			// Submenu para consultas específicas
             			case 6: 
             			limparTela();
             			do {
                         opc1 = menuConsultas();
        
          				switch(opc1) {
            	case 1:
            		limparTela();
               	 	listarComponentesAtrasados();
                	break;
            	case 2:
            		limparTela();
                	listarComponentesPorPosto();
                	break;
                case 3:
                	limparTela();
					listarComponentesFora();
				 	break;
				case 4:
					limparTela();
					listarComponentesNoPosto();
					break;
				case 5:
					limparTela();
					PesquisarEmpresaComponente();
					break;
            	case 0:
                	printf("Voltando ao menu das operacoes...\n");
                	break;
            	default:
               	 printf("Opcao invalida. Tente novamente.\n");
        }
        
    } while(opc1 != 0);
                    

             		break;	
             		case 0:
             			printf("Saindo do menu de operacoes...");
             			
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
    
    //Liberação dos ficheiros da memória antes de encerrar o programa
    
    finalizarComponentes();
    finalizarFuncionarios();
	finalizarEmpresas();
	finalizarPostos();
    finalizarOperacoes();
    
    return 0;
}
