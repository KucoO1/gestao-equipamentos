#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data.h"
#include "operacoes.h"
#include "componentes.h"
#include "util.h"
#include "math.h"

int numeroDeEmpresas;
int totalEmpresas = 0;
Empresa* empresas = NULL;

PropostaEmpresa* propostas = NULL;
int totalPropostas = 0;


//-------------------------------------- Base de dados (arquivos em txt) ----------------------------------------

void salvarConfiguracaoEmpresas() {
    FILE *arquivo = fopen("configEmpresas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao salvar a configuracao de empresas.\n");
        return;
    }
    fprintf(arquivo, "%d\n", numeroDeEmpresas);
    fclose(arquivo);
}

void carregarConfiguracaoEmpresas() {
    FILE *arquivo = fopen("configEmpresas.txt", "r");
    if (arquivo == NULL) {
        printf("Digite o numero maximo de empresas: ");
        scanf("%d", &numeroDeEmpresas);
        salvarConfiguracaoEmpresas();
    } else {
        fscanf(arquivo, "%d", &numeroDeEmpresas);
        fclose(arquivo);
    }
}

void salvarEmpresasEmArquivo() {
    FILE *arquivo = fopen("empresas.txt", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    for (int i = 0; i < totalEmpresas; i++) {
        fprintf(arquivo, "%d;%s;%s;%s\n",
                empresas[i].id,
                empresas[i].nome,
                empresas[i].tipo,
                empresas[i].contacto);
    }

    fclose(arquivo);
}

void carregarEmpresasDoArquivo() {
    FILE *arquivo = fopen("empresas.txt", "r");
    if (arquivo == NULL) return;

    totalEmpresas = 0;
    while (fscanf(arquivo, "%d;%[^;];%[^;];%[^\n]\n",
                  &empresas[totalEmpresas].id,
                  empresas[totalEmpresas].nome,
                  empresas[totalEmpresas].tipo,
                  empresas[totalEmpresas].contacto) == 4) {
        totalEmpresas++;
    }

    fclose(arquivo);
}

void inicializarEmpresas() {
    carregarConfiguracaoEmpresas();
    empresas = (Empresa*) malloc(numeroDeEmpresas * sizeof(Empresa));
    if (empresas == NULL) {
        printf("Erro ao alocar memoria para empresas.\n");
        exit(1);
    }
    carregarEmpresasDoArquivo();
}

void alterarLimiteEmpresas() {
    printf("Digite o novo limite de empresas: ");
    scanf("%d", &numeroDeEmpresas);
    empresas = (Empresa*) realloc(empresas, numeroDeEmpresas * sizeof(Empresa));
    if (empresas == NULL) {
        printf("Erro ao realocar memoria.\n");
        exit(1);
    }
    salvarConfiguracaoEmpresas();
    printf("Limite de empresas alterado com sucesso!\n");
}

void finalizarEmpresas() {
    salvarEmpresasEmArquivo();
    free(empresas);
    empresas = NULL;
}

void salvarPropostasEmArquivo() {
    FILE *f = fopen("propostas.txt", "w");
    if (!f) return;

    for (int i = 0; i < totalPropostas; i++) {
        fprintf(f, "%d;%d;%d;%.2f;%d;%s;%s\n",
            propostas[i].id,
            propostas[i].idComponente,
            propostas[i].idEmpresa,
            propostas[i].preco,
            propostas[i].tempoEntregaDias,
            propostas[i].dataProposta,
            propostas[i].observacoes);
    }

    fclose(f);
}

void carregarPropostasDoArquivo() {
    FILE *f = fopen("propostas.txt", "r");
    if (!f) return;

    PropostaEmpresa temp;
    while (fscanf(f, "%d;%d;%d;%f;%d;%10[^;];%99[^\n]\n",
                  &temp.id, &temp.idComponente, &temp.idEmpresa,
                  &temp.preco, &temp.tempoEntregaDias,
                  temp.dataProposta, temp.observacoes) == 7) {
        propostas = realloc(propostas, (totalPropostas + 1) * sizeof(PropostaEmpresa));
        propostas[totalPropostas++] = temp;
    }

    fclose(f);
}

void finalizarOfertas() {
    salvarPropostasEmArquivo();
    free(propostas);
    propostas = NULL;
}




//--------------------------------------------------------------------------------------------------------------

void adicionarEmpresa() {
    if (totalEmpresas >= numeroDeEmpresas) {
        printf("Limite de empresas atingido.\n");
        return;
    }

    Empresa e;
    e.id = totalEmpresas;

    fflush(stdin);
    printf("Nome da empresa: ");
    gets(e.nome);

    printf("Tipo (Fornecedor, Fabricante, etc.): ");
    gets(e.tipo);
    
    fflush(stdin);
    printf("Contacto: ");
    gets(e.contacto);

    empresas[totalEmpresas] = e;
    totalEmpresas++;
    salvarEmpresasEmArquivo();
    printf("Empresa adicionada com sucesso!\n");
}

void listarEmpresas() {
    system("cls");
    printf("\n======= EMPRESAS =========\n");

    if (totalEmpresas == 0) {
        printf("Nenhuma empresa cadastrada.\n");
        return;
    }

    for (int i = 0; i < totalEmpresas; i++) {
        printf("ID: %d\nNome: %s\nTipo: %s\nContacto: %s\n\n",
               empresas[i].id,
               empresas[i].nome,
               empresas[i].tipo,
               empresas[i].contacto);
    }
}



void pesquisarEmpresaNome() {
    char nome[50];

    fflush(stdin);
    printf("Digite o nome da empresa: ");
    gets(nome);

    for (int i = 0; i < totalEmpresas; i++) {
        if (strcmp(empresas[i].nome, nome) == 0) {
            printf("\nEncontrado:\nID: %d\nNome: %s\nTipo: %s\nContacto: %s\n",
                   empresas[i].id,
                   empresas[i].nome,
                   empresas[i].tipo,
                   empresas[i].contacto);
            return;
        }
    }

    printf("Empresa nao encontrada.\n");
}

void pesquisarEmpresasComWildcards() {
    char termo[100];
    int encontrou = 0;

    printf("Digite o termo de pesquisa (use * e ? como wildcards): ");
    fflush(stdin);
    scanf(" %[^\n]", termo);

    printf("\nResultados da pesquisa:\n");
    for (int i = 0; i < totalEmpresas; i++) {
        if (comparaComWildcards(empresas[i].nome, termo) ||
            comparaComWildcards(empresas[i].tipo, termo) ||
            comparaComWildcards(empresas[i].contacto, termo)) {
            
            printf("ID: %d | Nome: %s | Tipo: %s | Contacto: %s\n",
                   empresas[i].id,
                   empresas[i].nome,
                   empresas[i].tipo,
                   empresas[i].contacto);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhuma empresa encontrada com esse termo.\n");
    }
}


void pesquisarEmpresa(){
	
    int escolha;
    printf("Pesquisar por:\n1. Nome\n2. WildCards\nOpcao: ");
    fflush(stdin);
    scanf("%d", &escolha);
    
    if(escolha == 1)
    {
    	pesquisarEmpresaNome();
    	return;
	}
	else if(escolha == 2)
	{

		pesquisarEmpresasComWildcards();
		return;	
		
	}
	else {
        printf("Opcao invalida.\n");
        return;
    }

	
}

void alterarEmpresa() {
    int id;
    printf("ID da empresa a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalEmpresas; i++) {
        if (empresas[i].id == id) {
            fflush(stdin);
            printf("Novo nome: ");
            gets(empresas[i].nome);

            printf("Novo tipo: ");
            gets(empresas[i].tipo);
            
            fflush(stdin);
            printf("Novo contacto: ");
            gets(empresas[i].contacto);

            salvarEmpresasEmArquivo();
            printf("Empresa alterada com sucesso.\n");
            return;
        }
    }
    printf("Empresa nao encontrada.\n");
}


int empresaEstaEmOperacoes(int idEmpresa) {
    for (int i = 0; i < totalOperacoes; i++) {
        if (operacoes[i].idEmpresa == idEmpresa) {
            return 1; 
        }
    }
    return 0; 
}


void removerPropostasPorComponente(int idComponente) {
    int encontrou = 0;
    for (int i = 0; i < totalPropostas; i++) {
        if (propostas[i].idComponente == idComponente) {
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) return;

    int i = 0;
    while (i < totalPropostas) {
        if (propostas[i].idComponente == idComponente) {
            for (int j = i; j < totalPropostas - 1; j++) {
                propostas[j] = propostas[j + 1];
            }
            totalPropostas--;
        } else {
            i++;
        }
    }

    salvarPropostasEmArquivo();
    printf("Propostas associadas ao componente %d removidas.\n", idComponente);
}


void removerPropostasPorEmpresa(int idEmpresa) {
    int encontrou = 0;
    for (int i = 0; i < totalPropostas; i++) {
        if (propostas[i].idEmpresa == idEmpresa) {
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) return;

    int i = 0;
    while (i < totalPropostas) {
        if (propostas[i].idEmpresa == idEmpresa) {
            for (int j = i; j < totalPropostas - 1; j++) {
                propostas[j] = propostas[j + 1];
            }
            totalPropostas--;
        } else {
            i++;
        }
    }

    salvarPropostasEmArquivo();
    printf("Propostas associadas a empresa %d removidas.\n", idEmpresa);
}


void removerEmpresa() {
    int id;
    printf("ID da empresa a remover: ");
    fflush(stdin);
    scanf("%d", &id);

  if(empresaEstaEmOperacoes(id)) {
        printf("Erro: Esta empresa esta associada a uma ou mais operacoes. Nao pode ser removida.\n");
        return;
    }
    else
    {
       for (int i = 0; i < totalEmpresas; i++) 
	   {
	   	 removerPropostasPorEmpresa(id);
	   	
        if (empresas[i].id == id) {
            for (int j = i; j < totalEmpresas - 1; j++) {
                empresas[j] = empresas[j + 1];
            }
            totalEmpresas--;
            salvarEmpresasEmArquivo();
            printf("Empresa removida com sucesso.\n");
            return;
        }
      }
	}

    
    printf("Empresa nao encontrada.\n");
}


//------------------  Propostas (preço/tempo) -----------------------------------

int componenteExisteP(int idComponente) {
    for (int i = 0; i < totalComponentes; i++) {
        if (componentes[i].id == idComponente) {
            return 1;
        }
    }
    return 0;
}

int empresaExisteP(int idEmpresa) {
    for (int i = 0; i < totalEmpresas; i++) {
        if (empresas[i].id == idEmpresa) {
            return 1;
        }
    }
    return 0;
}


void adicionarProposta() {
	
    PropostaEmpresa nova;

     do {
        printf("ID do componente: ");
        scanf("%d", &nova.idComponente);
        if (!componenteExisteP(nova.idComponente)) {
            printf("Componente nao encontrado.\n");
        }
    } while (!componenteExisteP(nova.idComponente));


    do {
        printf("ID da empresa: ");
        scanf("%d", &nova.idEmpresa);
        if (!empresaExisteP(nova.idEmpresa)) {
            printf("Empresa nao encontrada.\n");
        }
    } while (!empresaExisteP(nova.idEmpresa));
    
    fflush(stdin);

    nova.id = totalPropostas;

    printf("Preco proposto: ");
    scanf("%f", &nova.preco);

    printf("Tempo estimado (em dias): ");
    scanf("%d", &nova.tempoEntregaDias);
    
    fflush(stdin);

    printf("Data da proposta (dd/mm/aaaa): ");
    scanf(" %[^\n]", nova.dataProposta);

    printf("Observacoes: ");
    scanf(" %[^\n]", nova.observacoes);

    propostas = realloc(propostas, (totalPropostas + 1) * sizeof(PropostaEmpresa));
    propostas[totalPropostas++] = nova;
    
    salvarPropostasEmArquivo();

    printf("Proposta registrada com sucesso!\n");
}


void alterarProposta() {
    int id;
    printf("ID da proposta a alterar: ");
    scanf("%d", &id);

    for (int i = 0; i < totalPropostas; i++) {
        if (propostas[i].id == id) {
            printf("Novo preco: ");
            scanf("%f", &propostas[i].preco);
            printf("Novo tempo de entrega: ");
            scanf("%d", &propostas[i].tempoEntregaDias);
            fflush(stdin);
            printf("Nova data da proposta: ");
            scanf(" %[^\n]", propostas[i].dataProposta);
            printf("Novas observacoes: ");
            scanf(" %[^\n]", propostas[i].observacoes);
            salvarPropostasEmArquivo();
            printf("Proposta atualizada.\n");
            return;
        }
    }

    printf("Proposta nao encontrada.\n");
}

void listarPropostas() {
    if (totalPropostas == 0) {
        printf("Nenhuma proposta registrada.\n");
        return;
    }

    for (int i = 0; i < totalPropostas; i++) {
        printf("ID: %d | Componente: %d | Empresa: %d | Preco: %.2fkz | Tempo: %d dias | Data: %s\nObs: %s\n\n",
               propostas[i].id, propostas[i].idComponente, propostas[i].idEmpresa,
               propostas[i].preco, propostas[i].tempoEntregaDias,
               propostas[i].dataProposta, propostas[i].observacoes);
    }
}



void removerProposta() {
    int id;
    printf("ID da proposta a remover: ");
    scanf("%d", &id);

    for (int i = 0; i < totalPropostas; i++) {
        if (propostas[i].id == id) {
            for (int j = i; j < totalPropostas - 1; j++) {
                propostas[j] = propostas[j + 1];
            }
            totalPropostas--;
            salvarPropostasEmArquivo();
            printf("Proposta removida.\n");
            return;
        }
    }

    printf("Proposta nao encontrada.\n");
}


// Comparar propostas com base em preço e tempo
void compararPropostasPorComponente() {
    int idComponente;
    printf("ID do componente: ");
    scanf("%d", &idComponente);

    if (!componenteExisteP(idComponente)) {
        printf("Componente nao encontrado.\n");
        return;
    }

    PropostaEmpresa *melhor = NULL;

    for (int i = 0; i < totalPropostas; i++) {
        if (propostas[i].idComponente == idComponente) {
            if (melhor == NULL) {
                melhor = &propostas[i];
            } else {
                float precoAtual = propostas[i].preco;
                float precoMelhor = melhor->preco;
                float diferenca = fabs(precoAtual - precoMelhor);

                if (precoAtual < precoMelhor) {
                    melhor = &propostas[i];
                } else if (diferenca / precoMelhor <= 0.05) { // diferença <= 5%
                    if (propostas[i].tempoEntregaDias < melhor->tempoEntregaDias) {
                        melhor = &propostas[i];
                    }
                }
            }
        }
    }

    if (melhor) {
        printf("\n--- Melhor Proposta ---\n");
        printf("ID: %d | Empresa: %d | Preco: %.2f | Entrega: %d dias\n",
               melhor->id, melhor->idEmpresa, melhor->preco, melhor->tempoEntregaDias);
        printf("Data Proposta: %s\n", melhor->dataProposta);
        printf("Observacoes: %s\n", melhor->observacoes);
    } else {
        printf("Nenhuma proposta encontrada para este componente.\n");
    }
}




