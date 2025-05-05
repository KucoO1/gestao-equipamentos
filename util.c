// util.c

#include <stdio.h>
#include "data.h"
#include "interface.h"
#include "funcionarios.h"
#include "postos.h"
#include "empresas.h"
#include "operacoes.h"
#include "componentes.h"
#include <stdlib.h>


int comparaComWildcards(const char *texto, const char *padrao) {
    while (*padrao) {
        if (*padrao == '*') {
            padrao++;
            if (!*padrao) return 1;
            while (*texto) {
                if (comparaComWildcards(texto, padrao)) return 1;
                texto++;
            }
            return 0;
        } else if (*padrao == '?' || *padrao == *texto) {
            texto++;
            padrao++;
        } else {
            return 0;
        }
    }
    return *texto == '\0';
}



void componenteComMaisPropostas() {
    if (totalPropostas == 0) {
        printf("Nenhuma proposta registada.\n");
        return;
    }

    int *contagens = calloc(totalComponentes, sizeof(int));
    for (int i = 0; i < totalPropostas; i++) {
        for (int j = 0; j < totalComponentes; j++) {
            if (propostas[i].idComponente == componentes[j].id) {
                contagens[j]++;
            }
        }
    }

    int max = 0, idx = -1;
    for (int i = 0; i < totalComponentes; i++) {
        if (contagens[i] > max) {
            max = contagens[i];
            idx = i;
        }
    }

    if (idx != -1) {
        printf("Componente com mais propostas: %s (%d propostas)\n", componentes[idx].designacao, max);
    }

    free(contagens);
}


void empresaComMaisPropostas() {
    if (totalPropostas == 0) return;

    int *contagens = calloc(totalEmpresas, sizeof(int));
    for (int i = 0; i < totalPropostas; i++) {
        for (int j = 0; j < totalEmpresas; j++) {
            if (propostas[i].idEmpresa == empresas[j].id) {
                contagens[j]++;
            }
        }
    }

    int max = 0, idx = -1;
    for (int i = 0; i < totalEmpresas; i++) {
        if (contagens[i] > max) {
            max = contagens[i];
            idx = i;
        }
    }

    if (idx != -1) {
        printf("Empresa com mais propostas: %s (%d propostas)\n", empresas[idx].nome, max);
    }

    free(contagens);
}


void propostaComMenorTempoEntrega() {
    if (totalPropostas == 0) {
        printf("Nenhuma proposta registrada.\n");
        return;
    }

    int idx = 0;
    for (int i = 1; i < totalPropostas; i++) {
        if (propostas[i].tempoEntregaDias < propostas[idx].tempoEntregaDias) {
            idx = i;
        }
    }

    printf("Proposta com menor tempo de entrega: ID %d | Tempo: %d dias | Empresa: %d | Componente: %d\n",
           propostas[idx].id, propostas[idx].tempoEntregaDias,
           propostas[idx].idEmpresa, propostas[idx].idComponente);
}

void propostaComMelhorCustoBeneficio() {
    if (totalPropostas == 0) {
        printf("Nenhuma proposta registrada.\n");
        return;
    }

    float pesoTempo = 1.0; // peso pode ser ajustado
    int idxMelhor = 0;
    float melhorPontuacao = propostas[0].preco + propostas[0].tempoEntregaDias * pesoTempo;

    for (int i = 1; i < totalPropostas; i++) {
        float pontuacao = propostas[i].preco + propostas[i].tempoEntregaDias * pesoTempo;
        if (pontuacao < melhorPontuacao) {
            melhorPontuacao = pontuacao;
            idxMelhor = i;
        }
    }

    printf("Proposta com melhor custo-beneficio: ID %d | Preco: %.2f | Tempo: %d dias | Pontuacao: %.2f\n",
           propostas[idxMelhor].id,
           propostas[idxMelhor].preco,
           propostas[idxMelhor].tempoEntregaDias,
           melhorPontuacao);
}


void estatisticasGerais() {
    printf("\n===== ESTATISTICAS GERAIS =====\n");

    printf("Total de Componentes: %d\n", totalComponentes);
    printf("Total de Subcomponentes: %d\n", totalSubcomponentes);
    printf("Total de Empresas: %d\n", totalEmpresas);
    printf("Total de Operacoes: %d\n", totalOperacoes);
    printf("Total de Propostas: %d\n", totalPropostas);

    componenteComMaisPropostas();
    empresaComMaisPropostas();
    propostaComMenorTempoEntrega();
    propostaComMelhorCustoBeneficio();

    printf("=================================\n");
    system("pause");
}



