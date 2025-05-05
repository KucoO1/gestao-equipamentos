#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "data.h"
#include "postos.h"
#include "empresas.h"
#include "componentes.h"
#include "util.h"




Operacao *operacoes = NULL;
int totalOperacoes = 0;

// Base da dados em arquivo .txt

void salvarOperacoesEmArquivo() {
    FILE *arquivo = fopen("operacoes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];
        fprintf(arquivo, "%d;%s;%d;%d;%d;%s;%s;%s;%s;%d;%s;%.2f;%s\n",
                op->numeroInterno, op->numeroExterno, op->idPosto, op->idComponente, op->idEmpresa,
                op->tipoOperacao, op->dataSaida, op->dataChegada, op->dataPrevista,
                op->idFuncionario, op->dataOperacao, op->montante, op->observacoes);
    }

    fclose(arquivo);
}


void carregarOperacoesDoArquivo() {
    FILE *arquivo = fopen("operacoes.txt", "r");
    if (arquivo == NULL) return;

    Operacao temp;
    while (fscanf(arquivo, "%d;%29[^;];%d;%d;%d;%29[^;];%10[^;];%10[^;];%10[^;];%d;%10[^;];%f;%99[^\n]\n",
                  &temp.numeroInterno, temp.numeroExterno, &temp.idPosto, &temp.idComponente, &temp.idEmpresa,
                  temp.tipoOperacao, temp.dataSaida, temp.dataChegada, temp.dataPrevista,
                  &temp.idFuncionario, temp.dataOperacao, &temp.montante, temp.observacoes) == 13) {
        Operacao *novo = realloc(operacoes, (totalOperacoes + 1) * sizeof(Operacao));
		
		if (novo == NULL) 
		{
   		 printf("Erro ao alocar memória para operação.\n");
   		 break; 
		}
		operacoes = novo;
		operacoes[totalOperacoes++] = temp;
    }

    fclose(arquivo);
}

void finalizarOperacoes() {
	
    salvarOperacoesEmArquivo();
    free(operacoes);
    operacoes = NULL;
	
}

// Validações 

int idExiste(const char *filename, int id) {
    FILE *file = fopen(filename, "r");
    if (!file) return 0;

    int encontrado = 0, tempId;
    while (fscanf(file, "%d", &tempId) == 1) {
        
		if (tempId == id) {
            encontrado = 1;
            break;
        }
        // Ignora o resto da linha
        char buffer[200];
        fgets(buffer, sizeof(buffer), file);
    }

    fclose(file);
    return encontrado;
}

int funcionarioExiste(int id) {
    return idExiste("funcionarios.txt", id);
}

int componenteExiste(int id) {
    return idExiste("componentes.txt", id);
}

int empresaExiste(int id) {
    return idExiste("empresas.txt", id);
}

int postoExiste(int id) {
    return idExiste("postos.txt", id);
}

int operacaoExiste(int id) {
    return idExiste("operacoes.txt", id);
}

// Listagem detalhada


// Função auxiliar para comparar datas no formato "dd/mm/yyyy"
int compararDatas(const char *data1, const char *data2) {
    int dia1, mes1, ano1;
    int dia2, mes2, ano2;

    sscanf(data1, "%d/%d/%d", &dia1, &mes1, &ano1);
    sscanf(data2, "%d/%d/%d", &dia2, &mes2, &ano2);

    if (ano1 != ano2)
        return ano1 - ano2;
    if (mes1 != mes2)
        return mes1 - mes2;
    return dia1 - dia2;
}

// Função para obter a data atual no formato "dd/mm/yyyy"
void obterDataAtual(char *dataHoje) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(dataHoje, "%02d/%02d/%04d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
}

// Função para listar componentes com data prevista ultrapassada
void listarComponentesAtrasados() {
    char hoje[11];
    obterDataAtual(hoje);

    printf("\n=== Componentes que ultrapassaram a data prevista de chegada ===\n");
    int encontrou = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        if (operacoes[i].dataPrevista[0] != '\0' && compararDatas(hoje, operacoes[i].dataPrevista) > 0) {
            printf("Componente ID: %d | Posto de Trabalho ID: %d | Data Prevista: %s\n",
                   operacoes[i].idComponente, operacoes[i].idPosto, operacoes[i].dataPrevista);
            encontrou = 1;
        }
    }
    if (!encontrou) {
        printf("Nenhum componente ultrapassou a data prevista.\n");
    }
}

//Listagem de componentes (e sua condição) por Posto de Trabalho

void listarComponentesPorPosto() {
    printf("\n=== Componentes por Posto de Trabalho ===\n");

    if (totalComponentes == 0 || componentes == NULL) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        printf("Posto de Trabalho ID: %d\n", componentes[i].idPosto);
        printf(" -> Componente ID: %d | Designacao: %s | Condicao: %s\n",
               componentes[i].id, componentes[i].designacao, componentes[i].condicao);
    }
}


// Função para listar componentes que estão fora (em reparação, garantia, etc.)
void listarComponentesFora() {
    printf("\n=== Componentes Fora do Posto de Trabalho ===\n");
    int encontrado = 0;
    
    for (int i = 0; i < totalComponentes; i++) {
        int componenteEstaFora = 0;

        for (int j = 0; j < totalOperacoes; j++) {
            if (operacoes[j].idComponente == componentes[i].id) {
                // Se há data de saída e não há data de chegada → ainda fora
                if (strlen(operacoes[j].dataSaida) > 0 && strlen(operacoes[j].dataChegada) == 0) {
                    componenteEstaFora = 1;
                    break;
                }
            }
        }

        if (componenteEstaFora) {
            printf("ID: %d | Designacao: %s | Condicao: %s\n", componentes[i].id, componentes[i].designacao, componentes[i].condicao);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum componente encontrado fora do posto.\n");
    }
}

// Função para listar componentes que estão no posto de trabalho
void listarComponentesNoPosto() {
    printf("\n=== Componentes Presentes no Posto de Trabalho ===\n");
    int encontrado = 0;

    for (int i = 0; i < totalComponentes; i++) {
        int componenteEstaFora = 0;

        for (int j = 0; j < totalOperacoes; j++) {
            if (operacoes[j].idComponente == componentes[i].id) {
                if (strlen(operacoes[j].dataSaida) > 0 && strlen(operacoes[j].dataChegada) == 0) {
                    componenteEstaFora = 1;
                    break;
                }
            }
        }

        if (!componenteEstaFora) {
            printf("ID: %d | Designacao: %s | Condicao: %s\n", componentes[i].id, componentes[i].designacao, componentes[i].condicao);
            encontrado = 1;
        }
    }

    if (!encontrado) {
        printf("Nenhum componente encontrado no posto de trabalho.\n");
    }
}

//Pesquisar empresas

void pesquisarEmpresas() {
    char termo[50];
    printf("Digite nome ou ID da empresa a pesquisar: ");
    fflush(stdin);
    scanf(" %[^\n]", termo);

    int idBusca = atoi(termo); // "ASCII to Integer" - converte uma string (texto) que representa um número em um inteiro (int).
    int encontrou = 0;
    
    //A função strstr "string string", procura uma substring dentro de outra string.
    
    /*strstr(str1, str2) busca a primeira ocorrência da str2 dentro de str1.
Se encontrar, retorna um ponteiro para o início da ocorrência.
Se não encontrar, retorna NULL.*/

    for (int i = 0; i < totalEmpresas; i++) {
        if (empresas[i].id == idBusca || strstr(empresas[i].nome, termo) != NULL) {
            printf("\n=== Empresa Encontrada ===\n");
            printf("ID: %d\n", empresas[i].id);
            printf("Nome: %s\n", empresas[i].nome);
            printf("Tipo: %s\n", empresas[i].tipo);
            printf("Contacto: %s\n", empresas[i].contacto);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhuma empresa encontrada.\n");
}

//Pesqusar Componentes

void pesquisarComponentes() {
    char termo[50];
    printf("Digite nome, ID ou numero de serie do componente a pesquisar: ");
    fflush(stdin);
    scanf(" %[^\n]", termo);

    int idBusca = atoi(termo);
    int encontrou = 0;

    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == idBusca ||
            strstr(componentes[i].designacao, termo) != NULL ||
            strstr(componentes[i].numeroSerie, termo) != NULL) {

            printf("\n=== Componente Encontrado ===\n");
            printf("ID: %d\n", componentes[i].id);
            printf("Designacao: %s\n", componentes[i].designacao);
            printf("Numero de Serie: %s\n", componentes[i].numeroSerie);
            printf("Condicao: %s\n", componentes[i].condicao);
            printf("ID Posto: %d\n", componentes[i].idPosto);
            encontrou = 1;
        }
    }

    if (!encontrou)
        printf("Nenhum componente encontrado.\n");
}

void PesquisarEmpresaComponente(){
	
    int escolha;
    printf("Pesquisar por:\n1. Empresa\n2. Componente\nOpcao: ");
    fflush(stdin);
    scanf("%d", &escolha);
    
    if(escolha == 1)
    {
    	pesquisarEmpresas();
    	return;
	}
	else if(escolha == 2)
	{

		pesquisarComponentes();
		return;	
		
	}
	else {
        printf("Opcao invalida.\n");
        return;
    }

	
}


/*--------------  Inserir Operações  --------------*/


void inserirOperacao() {
    Operacao nova;

    fflush(stdin);
    printf("Numero interno: ");
    scanf("%d", &nova.numeroInterno);
	printf("Numero externo: ");
    scanf(" %[^\n]", nova.numeroExterno);
    
    do {
    
	fflush(stdin);
    printf("ID do posto: ");
    scanf("%d", &nova.idPosto);
    
    if (!postoExiste(nova.idPosto)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
} while (!postoExiste(nova.idPosto));
    
   
   do {
   	fflush(stdin);
    printf("ID do componente: ");
    scanf("%d", &nova.idComponente);
    
    if (!componenteExiste(nova.idComponente)) {
        printf("Componente nao encontrado! Tente novamente.\n");
    }
} while (!componenteExiste(nova.idComponente));

do {
	fflush(stdin);
    printf("ID da empresa: ");
    scanf("%d", &nova.idEmpresa);
    
    if (!empresaExiste(nova.idEmpresa)) {
        printf("Empresa nao encontrada! Tente novamente.\n");
    }
} while (!empresaExiste(nova.idEmpresa));
   
    fflush(stdin);
    
    printf("Tipo de operacao: ");
    scanf(" %[^\n]", nova.tipoOperacao);
    
    
    printf("Data de saida (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataSaida);
    
    printf("Data de chegada (deixe em branco se estiver fora): ");
	getchar(); // limpar o '\n' pendente do scanf anterior
	fgets(nova.dataChegada, sizeof(nova.dataChegada), stdin);
	nova.dataChegada[strcspn(nova.dataChegada, "\n")] = '\0'; // remover '\n' final
    
    fflush(stdin);
    printf("Data prevista (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataPrevista);
    
    do {
    
	fflush(stdin);
    printf("ID do funcionario: ");
    scanf("%d", &nova.idFuncionario);
    if (!funcionarioExiste(nova.idFuncionario)) {
        printf("Funcionario nao encontrado! Tente novamente.\n");
    }
} while (!funcionarioExiste(nova.idFuncionario));
    
    fflush(stdin);
    
    printf("Data da operacao (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataOperacao);
    printf("Montante: ");
    scanf("%f", &nova.montante);
    printf("Observacoes: ");
    fflush(stdin);
    scanf(" %[^\n]", nova.observacoes);

    operacoes = realloc(operacoes, (totalOperacoes + 1) * sizeof(Operacao));
    operacoes[totalOperacoes++] = nova;
    salvarOperacoesEmArquivo();

    printf("Operacao inserida com sucesso!\n");
}

// Listar Operações

void listarOperacoes() {
    for (int i = 0; i < totalOperacoes; i++) {
        Operacao *op = &operacoes[i];
        printf("Interno: %d | Externo: %s | Tipo: %s | Data: %s | Montante: %.2f\n",
               op->numeroInterno, op->numeroExterno, op->tipoOperacao,
               op->dataOperacao, op->montante);
    }
}

//Pesquisar Operação

void pesquisarOperacoesComWildcards() {
    char termo[100];
    printf("Digite o termo de busca com wildcards (* e ?): ");
    getchar(); // Limpa o buffer
    fgets(termo, sizeof(termo), stdin);
    termo[strcspn(termo, "\n")] = '\0'; // Remove newline

    int encontrados = 0;
    for (int i = 0; i < totalOperacoes; i++) {
        if (comparaComWildcards(operacoes[i].numeroExterno, termo) ||
            comparaComWildcards(operacoes[i].tipoOperacao, termo) ||
            comparaComWildcards(operacoes[i].dataSaida, termo) ||
            comparaComWildcards(operacoes[i].dataChegada, termo) ||
            comparaComWildcards(operacoes[i].dataPrevista, termo) ||
            comparaComWildcards(operacoes[i].dataOperacao, termo) ||
            comparaComWildcards(operacoes[i].observacoes, termo)) {

            printf("\nNumero Interno: %d\n", operacoes[i].numeroInterno);
            printf("Numero Externo: %s\n", operacoes[i].numeroExterno);
            printf("ID do Posto: %d\n", operacoes[i].idPosto);
            printf("ID do Componente: %d\n", operacoes[i].idComponente);
            printf("ID da Empresa: %d\n", operacoes[i].idEmpresa);
            printf("Tipo de Operacao: %s\n", operacoes[i].tipoOperacao);
            printf("Data Saida: %s\n", operacoes[i].dataSaida);
            printf("Data Chegada: %s\n", operacoes[i].dataChegada);
            printf("Data Prevista: %s\n", operacoes[i].dataPrevista);
            printf("ID do Funcionario: %d\n", operacoes[i].idFuncionario);
            printf("Data Operacao: %s\n", operacoes[i].dataOperacao);
            printf("Montante: %.2f\n", operacoes[i].montante);
            printf("Observacoes: %s\n", operacoes[i].observacoes);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhuma operacao encontrada com o termo fornecido.\n");
    }
}



void pesquisarOperacaoPorNumero(){
    int escolha;
    printf("Numero:\n1. Interno\n2. Externo\nOpcao: ");
    fflush(stdin);
    scanf("%d", &escolha);

    if (escolha == 1) {
        int numero;
        printf("Digite o numero interno da operacao: ");
        scanf("%d", &numero);

        for (int i = 0; i < totalOperacoes; i++) {
            if (operacoes[i].numeroInterno == numero) {
                Operacao *op = &operacoes[i];
                printf("\n=== Operacao Encontrada ===\n");
                printf("Numero Interno: %d\n", op->numeroInterno);
                printf("Numero Externo: %s\n", op->numeroExterno);
                printf("ID Posto: %d\n", op->idPosto);
                printf("ID Componente: %d\n", op->idComponente);
                printf("ID Empresa: %d\n", op->idEmpresa);
                printf("Tipo de Operacao: %s\n", op->tipoOperacao);
                printf("Data Saida: %s\n", op->dataSaida);
                printf("Data Chegada: %s\n", op->dataChegada);
                printf("Data Prevista: %s\n", op->dataPrevista);
                printf("ID Funcionario: %d\n", op->idFuncionario);
                printf("Data da Operacao: %s\n", op->dataOperacao);
                printf("Montante: %.2f\n", op->montante);
                printf("Observacoes: %s\n", op->observacoes);
                return;
            }
        }

    } else if (escolha == 2) {
        char numero[30];
        printf("Digite o numero externo da operacao: ");
        scanf(" %[^\n]", numero);

        for (int i = 0; i < totalOperacoes; i++) {
            if (strcmp(operacoes[i].numeroExterno, numero) == 0) {
                Operacao *op = &operacoes[i];
                printf("\n=== Operacao Encontrada ===\n");
                printf("Numero Interno: %d\n", op->numeroInterno);
                printf("Numero Externo: %s\n", op->numeroExterno);
                printf("ID Posto: %d\n", op->idPosto);
                printf("ID Componente: %d\n", op->idComponente);
                printf("ID Empresa: %d\n", op->idEmpresa);
                printf("Tipo de Operacao: %s\n", op->tipoOperacao);
                printf("Data Saida: %s\n", op->dataSaida);
                printf("Data Chegada: %s\n", op->dataChegada);
                printf("Data Prevista: %s\n", op->dataPrevista);
                printf("ID Funcionario: %d\n", op->idFuncionario);
                printf("Data da Operacao: %s\n", op->dataOperacao);
                printf("Montante: %.2f\n", op->montante);
                printf("Observacoes: %s\n", op->observacoes);
                return;
            }
        }

    } else {
        printf("Opcao invalida.\n");
        return;
    }

    printf("Operacao nao encontrada.\n");
}

void pesquisarOperacao() {
    int opcao;
    printf("Pesquisar Operacao por:\n1. Numero (Interno/Externo)\n2. Wildcards\nOpcao: ");
    fflush(stdin);
    scanf("%d", &opcao);

    if (opcao == 1) {
        pesquisarOperacaoPorNumero();
    } else if (opcao == 2) {
        pesquisarOperacoesComWildcards();
    } else {
        printf("Opcao invalida.\n");
    }
}



// Alteração de operações

void alterarOperacao() {
    int numero;
    printf("Digite o numero interno da operacao a alterar: ");
    fflush(stdin);
    scanf("%d", &numero);

    for (int i = 0; i < totalOperacoes; i++) {
    	
        if (operacoes[i].numeroInterno == numero) {
            printf("Novo numero externo: ");
            fflush(stdin);
            scanf(" %[^\n]", operacoes[i].numeroExterno);
            
    do {
     printf("Novo ID do posto: ");
     fflush(stdin);
     scanf("%d", &operacoes[i].idPosto);
    
    if (!postoExiste(operacoes[i].idPosto)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
} while (!postoExiste(operacoes[i].idPosto));
    
   
   do {
    printf("Novo ID do componente: ");
    fflush(stdin);
    scanf("%d", &operacoes[i].idComponente);
    
    if (!componenteExiste(operacoes[i].idComponente)) {
        printf("Componente nao encontrado! Tente novamente.\n");
    }
} while (!componenteExiste(operacoes[i].idComponente));

   do {
    printf("Novo ID da empresa: ");
    fflush(stdin);
    scanf("%d", &operacoes[i].idEmpresa);
    
    if (!empresaExiste(operacoes[i].idEmpresa)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
   } while (!empresaExiste(operacoes[i].idEmpresa));
            
            fflush(stdin);      
                   
            printf("Novo tipo de operacao: ");
            scanf(" %[^\n]", operacoes[i].tipoOperacao);
            
            printf("Nova data de saida: ");
            scanf(" %[^\n]", operacoes[i].dataSaida);
            
            printf("Nova data de chegada (deixe em branco se ainda estiver fora): ");
    		getchar(); // limpar o '\n' pendente do scanf anterior
			fgets(operacoes[i].dataChegada, sizeof(operacoes[i].dataChegada), stdin);
			operacoes[i].dataChegada[strcspn(operacoes[i].dataChegada, "\n")] = '\0'; // remover '\n' final
            
			printf("Nova data prevista: ");
            scanf(" %[^\n]", operacoes[i].dataPrevista);
            
	do {
            printf("Novo ID do funcionario: ");
            fflush(stdin);
            scanf("%d", &operacoes[i].idFuncionario);
    if (!funcionarioExiste(operacoes[i].idFuncionario)) {
        printf("Funcionario nao encontrado! Tente novamente.\n");
    }
} while (!funcionarioExiste(operacoes[i].idFuncionario));
			
			fflush(stdin);
			
            printf("Nova data da operacao: ");
            scanf(" %[^\n]", operacoes[i].dataOperacao);
            printf("Novo montante: ");
            scanf("%f", &operacoes[i].montante);
            printf("Novas observacoes: ");
            fflush(stdin);
			scanf(" %[^\n]", operacoes[i].observacoes);

            printf("Operacao alterada com sucesso.\n");
            salvarOperacoesEmArquivo();
            return;
        }
    }

    printf("Operacao nao encontrada.\n");
}

// Eliminar Operações

void apagarOperacao() {
    int numero;
    printf("Digite o numero interno da operacao a apagar: ");
    fflush(stdin);
    scanf("%d", &numero);

    for (int i = 0; i < totalOperacoes; i++) {
        if (operacoes[i].numeroInterno == numero) {
            for (int j = i; j < totalOperacoes - 1; j++) {
                operacoes[j] = operacoes[j + 1];
            }

            totalOperacoes--;
            operacoes = realloc(operacoes, totalOperacoes * sizeof(Operacao));

            printf("Operacao apagada com sucesso.\n");
            salvarOperacoesEmArquivo();
            return;
        }
    }

    printf("Operacao nao encontrada.\n");
}



