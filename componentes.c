#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "postos.h"
#include "empresas.h"
#include "operacoes.h"
#include "util.h"

int numeroDeComponentes;
int totalComponentes = 0;

Componente* componentes = NULL;

Subcomponente *subcomponentes = NULL;
int totalSubcomponentes = 0;


void salvarConfiguracaoComponentes() {
    FILE *arquivo = fopen("config_componentes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a configuracao dos componentes.\n");
        return;
    }
    fprintf(arquivo, "%d\n", numeroDeComponentes);
    fclose(arquivo);
}

void carregarConfiguracaoComponentes() {
    FILE *arquivo = fopen("config_componentes.txt", "r");
    if (arquivo == NULL) {
        printf("Digite o numero maximo de componentes: ");
        scanf("%d", &numeroDeComponentes);
        salvarConfiguracaoComponentes();
    } else {
        fscanf(arquivo, "%d", &numeroDeComponentes);
        fclose(arquivo);
    }
}

void salvarComponentesEmArquivo() {
    FILE *arquivo = fopen("componentes.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de componentes para escrita.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        fprintf(arquivo, "%d;%s;%s;%s;%d;%d;%d;%s;%s;%d;%s\n",
                componentes[i].id,
                componentes[i].designacao,
                componentes[i].numeroSerie,
                componentes[i].dataAquisicao,
                componentes[i].garantiaMeses,
                componentes[i].idFornecedor,
                componentes[i].idFabricante,
                componentes[i].tipo,
                componentes[i].condicao,
                componentes[i].idPosto,
                componentes[i].observacoes);
    }

    fclose(arquivo);
}

void carregarComponentesDoArquivo() {
    FILE *arquivo = fopen("componentes.txt", "r");
    if (arquivo == NULL) {
        return;
    }

    totalComponentes = 0;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^;];%d;%d;%d;%[^;];%[^;];%d;%[^\n]\n",
                  &componentes[totalComponentes].id,
                  componentes[totalComponentes].designacao,
                  componentes[totalComponentes].numeroSerie,
                  componentes[totalComponentes].dataAquisicao,
                  &componentes[totalComponentes].garantiaMeses,
                  &componentes[totalComponentes].idFornecedor,
                  &componentes[totalComponentes].idFabricante,
                  componentes[totalComponentes].tipo,
                  componentes[totalComponentes].condicao,
                  &componentes[totalComponentes].idPosto,
                  componentes[totalComponentes].observacoes) == 11) {
        totalComponentes++;
    }

    fclose(arquivo);
}

void finalizarComponentes() {
    salvarComponentesEmArquivo();
    free(componentes);
    componentes = NULL;
}


void inicializarComponentes() {
    carregarConfiguracaoComponentes();
    componentes = (Componente*)malloc(numeroDeComponentes * sizeof(Componente));
    carregarComponentesDoArquivo();
}

// Guardar e carregar subcomponentes do arquivo (para persistência)
void salvarSubcomponentesEmArquivo() {
    FILE *f = fopen("subcomponentes.txt", "w");
    if (!f) return;
    for (int i = 0; i < totalSubcomponentes; i++) {
        fprintf(f, "%d;%d;%s;%s;%s;%s\n",
                subcomponentes[i].id,
                subcomponentes[i].idComponentePai,
                subcomponentes[i].designacao,
                subcomponentes[i].numeroSerie,
                subcomponentes[i].condicao,
                subcomponentes[i].observacoes);
    }
    fclose(f);
}

void carregarSubcomponentesDoArquivo() {
    FILE *f = fopen("subcomponentes.txt", "r");
    if (!f) return;
    Subcomponente temp;
    while (fscanf(f, "%d;%d;%49[^;];%29[^;];%10[^;];%14[^;];%99[^\n]\n",
                  &temp.id, &temp.idComponentePai, temp.designacao, temp.numeroSerie,
                   temp.condicao, temp.observacoes) == 6) {
        subcomponentes = realloc(subcomponentes, (totalSubcomponentes + 1) * sizeof(Subcomponente));
        subcomponentes[totalSubcomponentes++] = temp;
    }
    fclose(f);
}

// Liberar memória ao sair
void finalizarSubcomponentes() {
    free(subcomponentes);
    subcomponentes = NULL;
}






void alterarLimiteComponentes() {
    printf("Digite o novo limite de componentes: ");
    scanf("%d", &numeroDeComponentes);
    componentes = (Componente*)realloc(componentes, numeroDeComponentes * sizeof(Componente));
    salvarConfiguracaoComponentes();
    printf("Limite de componentes alterado com sucesso!\n");
}

int postoDeTrabalhoExiste(int idPosto) {
    for (int i = 0; i < totalPostos; i++) {
        if (postos[i].id == idPosto) {
            return 1; // Posto encontrado
        }
    }
    return 0; // Posto não encontrado
}


void adicionarComponente() {
    if (totalComponentes >= numeroDeComponentes) {
        printf("Limite de componentes atingido.\n");
        return;
    }

    Componente c;
    c.id = totalComponentes;

    fflush(stdin);
    printf("Designacao: ");
    gets(c.designacao);

    printf("Numero de Serie: ");
    gets(c.numeroSerie);
    
    fflush(stdin);

    printf("Data de Aquisicao (dd/mm/yyyy): ");
    gets(c.dataAquisicao);

    printf("Garantia (em meses): ");
    scanf("%d", &c.garantiaMeses);
    fflush(stdin);

    printf("ID do Fornecedor: ");
    scanf("%d", &c.idFornecedor);
    fflush(stdin);

    printf("ID do Fabricante: ");
    scanf("%d", &c.idFabricante);
    fflush(stdin);

    printf("Tipo: ");
    gets(c.tipo);
     
    printf("Condicao (Novo/Usado): ");
    gets(c.condicao);

    		do {
    		
			fflush(stdin);
    		printf("ID do Posto de Trabalho: ");
    		scanf("%d", &c.idPosto);
    
   			 if (!postoDeTrabalhoExiste(c.idPosto)) {
      				  printf("Posto de trabalho nao encontrado! Tente novamente.\n");
   				 }
			} while (!postoDeTrabalhoExiste(c.idPosto));
    
    
    
    
    fflush(stdin);

    printf("Observacoes: ");
    gets(c.observacoes);

    componentes[totalComponentes] = c;
    totalComponentes++;

    salvarComponentesEmArquivo();
    printf("Componente adicionado com sucesso!\n");
}

void listarComponentes() {
    system("cls");
    printf("\n======= COMPONENTES ==========\n");
    if (totalComponentes == 0) {
        printf("Nenhum componente cadastrado.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        printf("ID: %d\nDesignacao: %s\nNumero de Serie: %s\nData de Aquisicao: %s\nGarantia (meses): %d\nID Fornecedor: %d\nID Fabricante: %d\nTipo: %s\nCondicao: %s\nID Posto: %d\nObservacoes: %s\n\n",
               componentes[i].id,
               componentes[i].designacao,
               componentes[i].numeroSerie,
               componentes[i].dataAquisicao,
               componentes[i].garantiaMeses,
               componentes[i].idFornecedor,
               componentes[i].idFabricante,
               componentes[i].tipo,
               componentes[i].condicao,
               componentes[i].idPosto,
               componentes[i].observacoes);
    }
}

void pesquisarComponentePorNome() {
    char designacao[50];

    fflush(stdin);
    printf("Digite a designacao do componente: ");
    gets(designacao);

    for (int i = 0; i < totalComponentes; i++) {
        if (strcmp(componentes[i].designacao, designacao) == 0) {
            printf("Encontrado:\nID: %d\nDesignacao: %s\nNumero de Serie: %s\nData de Aquisicao: %s\nGarantia (meses): %d\nID Fornecedor: %d\nID Fabricante: %d\nTipo: %s\nCondicao: %s\nID Posto: %d\nObservacoes: %s\n",
                   componentes[i].id,
                   componentes[i].designacao,
                   componentes[i].numeroSerie,
                   componentes[i].dataAquisicao,
                   componentes[i].garantiaMeses,
                   componentes[i].idFornecedor,
                   componentes[i].idFabricante,
                   componentes[i].tipo,
                   componentes[i].condicao,
                   componentes[i].idPosto,
                   componentes[i].observacoes);
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}

void pesquisarComponentesComWildcards() {
    char termo[100];
    printf("Digite o termo de busca com wildcards (* e ?): ");
    fflush(stdin);
    scanf(" %[^\n]", termo);

    int encontrados = 0;
    for (int i = 0; i < totalComponentes; i++) {
        if (comparaComWildcards(componentes[i].designacao, termo) ||
            comparaComWildcards(componentes[i].numeroSerie, termo) ||
            comparaComWildcards(componentes[i].dataAquisicao, termo) ||
            comparaComWildcards(componentes[i].tipo, termo) ||
            comparaComWildcards(componentes[i].condicao, termo) ||
            comparaComWildcards(componentes[i].observacoes, termo)) {

            printf("\nID: %d\n", componentes[i].id);
            printf("Designacao: %s\n", componentes[i].designacao);
            printf("Numero de Serie: %s\n", componentes[i].numeroSerie);
            printf("Data de Aquisicao: %s\n", componentes[i].dataAquisicao);
            printf("Garantia (meses): %d\n", componentes[i].garantiaMeses);
            printf("Fornecedor (ID): %d\n", componentes[i].idFornecedor);
            printf("Fabricante (ID): %d\n", componentes[i].idFabricante);
            printf("Tipo: %s\n", componentes[i].tipo);
            printf("Condicao: %s\n", componentes[i].condicao);
            printf("Posto (ID): %d\n", componentes[i].idPosto);
            printf("Observacoes: %s\n", componentes[i].observacoes);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf("Nenhum componente encontrado com o termo fornecido.\n");
    }
}



void pesquisarComponente() {
    int escolha;
    printf("Pesquisar por:\n1. Designacao\n2. WildCards\nOpcao: ");
    fflush(stdin);
    scanf("%d", &escolha);

    if (escolha == 1) {
        pesquisarComponentePorNome(); 
    } else if (escolha == 2) {
        pesquisarComponentesComWildcards();
    } else {
        printf("Opcao invalida.\n");
    }
}



void alterarComponente() {
    int id;
    
    fflush(stdin);
    printf("ID do componente a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == id) {
            fflush(stdin);
            printf("Nova Designacao: ");
            gets(componentes[i].designacao);

            printf("Novo Numero de Serie: ");
            gets(componentes[i].numeroSerie);
            
            fflush(stdin);
            printf("Nova Data de Aquisicao: ");
            gets(componentes[i].dataAquisicao);

            printf("Nova Garantia (em meses): ");
            scanf("%d", &componentes[i].garantiaMeses);
            fflush(stdin);

            printf("Novo ID Fornecedor: ");
            scanf("%d", &componentes[i].idFornecedor);
            fflush(stdin);

            printf("Novo ID Fabricante: ");
            scanf("%d", &componentes[i].idFabricante);
            fflush(stdin);

            printf("Novo Tipo: ");
            gets(componentes[i].tipo);

            printf("Nova Condicao: ");
            gets(componentes[i].condicao);
            
            	 do {
            
			fflush(stdin);
    		printf("Novo ID Posto de Trabalho: ");
            scanf("%d", &componentes[i].idPosto);
    
   			 if (!postoDeTrabalhoExiste(componentes[i].idPosto)) {
      				  printf("Posto de trabalho nao encontrado! Tente novamente.\n");
   				 }
			} while (!postoDeTrabalhoExiste(componentes[i].idPosto));

            fflush(stdin);

            printf("Novas Observacoes: ");
            gets(componentes[i].observacoes);

            printf("Componente alterado com sucesso.\n");
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}


void trocarPostoComponente() {
    int id, novoIdPosto;

    printf("Digite o ID do componente que deseja transferir: ");
    fflush(stdin);
	scanf("%d", &id);

    // Verifica se o componente existe
    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == id) {
            printf("Componente encontrado. Posto atual: %d\n", componentes[i].idPosto);
            
            // Pede o novo ID do posto
            printf("Digite o novo ID do posto de trabalho: ");
            scanf("%d", &novoIdPosto);

            // Verifica se o novo posto existe
            if (postoDeTrabalhoExiste(novoIdPosto)) {
                componentes[i].idPosto = novoIdPosto;
                salvarComponentesEmArquivo();
                printf("Componente transferido com sucesso para o posto %d.\n", novoIdPosto);
            } else {
                printf("Posto de trabalho com ID %d nao encontrado.\n", novoIdPosto);
            }
            return;
        }
    }

    printf("Componente com ID %d nao encontrado.\n", id);
}

int ComponenteEmUso(int idComponente) {
    for (int i = 0; i < totalOperacoes; i++) {
        if (operacoes[i].idComponente == idComponente) {
            return 1; 
        }
    }
    return 0; 
}

void removerSubcomponentesDoComponente(int idComponentePai) {
    int i = 0;
    while (i < totalSubcomponentes) {
        if (subcomponentes[i].idComponentePai == idComponentePai) {
            // Remove o subcomponente deslocando os outros
            for (int j = i; j < totalSubcomponentes - 1; j++) {
                subcomponentes[j] = subcomponentes[j + 1];
            }
            totalSubcomponentes--;
            // Redimensiona o vetor (opcional, mas recomendado)
            subcomponentes = realloc(subcomponentes, totalSubcomponentes * sizeof(Subcomponente));
            // Não incrementa i, pois há novo subcomponente na posição atual
        } else {
            i++;
        }
    }
    salvarSubcomponentesEmArquivo();
}



void removerComponente() {
    int id;
    printf("ID do componente a remover: ");
    fflush(stdin);
    scanf("%d", &id);

    if (ComponenteEmUso(id)) {
        printf("Este componente esta associado a uma ou mais operacoes e nao pode ser removido.\n");
        return;
    }

    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == id) {
            // Remove subcomponentes associados
            removerSubcomponentesDoComponente(id);
            removerPropostasPorComponente(id);

            // Remove o componente
            for (int j = i; j < totalComponentes - 1; j++) {
                componentes[j] = componentes[j + 1];
            }
            totalComponentes--;
            componentes = realloc(componentes, totalComponentes * sizeof(Componente));
            salvarComponentesEmArquivo(); // Se tiveres essa função

            printf("Componente e seus subcomponentes removidos com sucesso.\n");
            return;
        }
    }

    printf("Componente nao encontrado.\n");
}



//-------------- Subcomponentes ------------------------


// Função para verificar se um componente existe (usada para validar o componente pai)

int componentePaiExiste(int idComponente) {
    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == idComponente) return 1;
    }
    return 0;
}

void adicionarSubcomponente() {
    Subcomponente novo;

    do {
        fflush(stdin);
        printf("ID do componente pai: ");
        scanf("%d", &novo.idComponentePai);

        if (!componentePaiExiste(novo.idComponentePai)) {
            printf("Componente pai nao encontrado.\n");
        }
    } while (!componentePaiExiste(novo.idComponentePai));

    fflush(stdin);

    novo.id = totalSubcomponentes;

    printf("Designacao: ");
    scanf(" %[^\n]", novo.designacao);

    printf("Numero de Serie: ");
    scanf(" %[^\n]", novo.numeroSerie);

    printf("Condicao: ");
    scanf(" %[^\n]", novo.condicao);

    printf("Observacoes: ");
    scanf(" %[^\n]", novo.observacoes);


    subcomponentes = realloc(subcomponentes, (totalSubcomponentes + 1) * sizeof(Subcomponente));
    subcomponentes[totalSubcomponentes++] = novo;

    salvarSubcomponentesEmArquivo();
    printf("Subcomponente adicionado com sucesso!\n");
}


void alterarSubcomponente() {
    int id;
    printf("ID do subcomponente a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalSubcomponentes; i++) {
        if (subcomponentes[i].id == id) {
            fflush(stdin);
            printf("Nova designacao: ");
            scanf(" %[^\n]", subcomponentes[i].designacao);

            
            printf("Novo numero de serie: ");
            scanf(" %[^\n]", subcomponentes[i].numeroSerie);

            fflush(stdin);
            printf("Nova condicao: ");
            scanf(" %[^\n]", subcomponentes[i].condicao);
            
             fflush(stdin);
            printf("Novas observacoes: ");
            scanf(" %[^\n]", subcomponentes[i].observacoes);

            salvarSubcomponentesEmArquivo();
            printf("Subcomponente atualizado com sucesso.\n");
            return;
        }
    }

    printf("Subcomponente com ID %d nao encontrado.\n", id);
}



// Listar subcomponentes de um componente
void listarSubcomponentesDeComponente() {
	
	int idComponentePai;
    printf("ID do componente principal: ");
    fflush(stdin);
	scanf("%d", &idComponentePai);
	
    printf("\nSubcomponentes do componente ID %d:\n", idComponentePai);
    int encontrou = 0;
    for (int i = 0; i < totalSubcomponentes; i++) {
        if (subcomponentes[i].idComponentePai == idComponentePai) {
            printf("ID: %d | Designacao: %s | Serie: %s | Condicao: %s\n",
                   subcomponentes[i].id,
                   subcomponentes[i].designacao,
                   subcomponentes[i].numeroSerie,
                   subcomponentes[i].condicao);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("Nenhum subcomponente encontrado.\n");
}

void removerSubcomponente() {
    int id;
    printf("ID do subcomponente a remover: ");
    scanf("%d", &id);

    int encontrado = 0;

    for (int i = 0; i < totalSubcomponentes; i++) {
        if (subcomponentes[i].id == id) {
            encontrado = 1;
            for (int j = i; j < totalSubcomponentes - 1; j++) {
                subcomponentes[j] = subcomponentes[j + 1];
            }
            totalSubcomponentes--;
            subcomponentes = realloc(subcomponentes, totalSubcomponentes * sizeof(Subcomponente));
            salvarSubcomponentesEmArquivo();
            printf("Subcomponente removido com sucesso.\n");
            break;
        }
    }

    if (!encontrado) {
        printf("Subcomponente com ID %d nao encontrado.\n", id);
    }
}


