#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"



Operacao *operacoes;
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
        operacoes = realloc(operacoes, (totalOperacoes + 1) * sizeof(Operacao));
        operacoes[totalOperacoes++] = temp;
    }

    fclose(arquivo);
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



/*--------------  Inserir Operações  --------------*/


void inserirOperacao() {
    Operacao nova;

    printf("Numero interno: ");
    scanf("%d", &nova.numeroInterno);
    printf("Numero externo: ");
    scanf(" %[^\n]", nova.numeroExterno);
    
    do {
    printf("ID do posto: ");
    scanf("%d", &nova.idPosto);
    
    if (!postoExiste(nova.idPosto)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
} while (!postoExiste(nova.idPosto));
    
   
   do {
    printf("ID do componente: ");
    scanf("%d", &nova.idComponente);
    
    if (!componenteExiste(nova.idComponente)) {
        printf("Componente nao encontrado! Tente novamente.\n");
    }
} while (!componenteExiste(nova.idComponente));

do {
    printf("ID da empresa: ");
    scanf("%d", &nova.idEmpresa);
    
    if (!empresaExiste(nova.idEmpresa)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
} while (!empresaExiste(nova.idEmpresa));
   
    
    
    printf("Tipo de operacao: ");
    scanf(" %[^\n]", nova.tipoOperacao);
    
    
    printf("Data de saida (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataSaida);
    printf("Data de chegada (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataChegada);
    printf("Data prevista (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataPrevista);
    
    do {
    printf("ID do funcionario: ");
    scanf("%d", &nova.idFuncionario);
    if (!funcionarioExiste(nova.idFuncionario)) {
        printf("Funcionario nao encontrado! Tente novamente.\n");
    }
} while (!funcionarioExiste(nova.idFuncionario));
    
    
    printf("Data da operacao (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataOperacao);
    printf("Montante: ");
    scanf("%f", &nova.montante);
    printf("Observacoes: ");
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

void pesquisarOperacao() {
    int escolha;
    printf("Pesquisar por:\n1. Numero Interno\n2. Numero Externo\nOpcao: ");
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




// Alteração de operações

void alterarOperacao() {
    int numero;
    printf("Digite o numero interno da operacao a alterar: ");
    scanf("%d", &numero);

    for (int i = 0; i < totalOperacoes; i++) {
    	
        if (operacoes[i].numeroInterno == numero) {
            printf("Novo numero externo: ");
            scanf(" %[^\n]", operacoes[i].numeroExterno);
            
    do {
     printf("Novo ID do posto: ");
     scanf("%d", &operacoes[i].idPosto);
    
    if (!postoExiste(operacoes[i].idPosto)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
} while (!postoExiste(operacoes[i].idPosto));
    
   
   do {
    printf("Novo ID do componente: ");
    scanf("%d", &operacoes[i].idComponente);
    
    if (!componenteExiste(operacoes[i].idComponente)) {
        printf("Componente nao encontrado! Tente novamente.\n");
    }
} while (!componenteExiste(operacoes[i].idComponente));

   do {
    printf("Novo ID da empresa: ");
    scanf("%d", &operacoes[i].idEmpresa);
    
    if (!empresaExiste(operacoes[i].idEmpresa)) {
        printf("Posto de trabalho nao encontrado! Tente novamente.\n");
    }
   } while (!empresaExiste(operacoes[i].idEmpresa));
            
                   
            printf("Novo tipo de operacao: ");
            scanf(" %[^\n]", operacoes[i].tipoOperacao);
            printf("Nova data de saida: ");
            scanf(" %[^\n]", operacoes[i].dataSaida);
            printf("Nova data de chegada: ");
            scanf(" %[^\n]", operacoes[i].dataChegada);
            printf("Nova data prevista: ");
            scanf(" %[^\n]", operacoes[i].dataPrevista);
            
	do {
            printf("Novo ID do funcionario: ");
            scanf("%d", &operacoes[i].idFuncionario);
    if (!funcionarioExiste(operacoes[i].idFuncionario)) {
        printf("Funcionario nao encontrado! Tente novamente.\n");
    }
} while (!funcionarioExiste(operacoes[i].idFuncionario));
			
			
            printf("Nova data da operacao: ");
            scanf(" %[^\n]", operacoes[i].dataOperacao);
            printf("Novo montante: ");
            scanf("%f", &operacoes[i].montante);
            printf("Novas observacoes: ");
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



