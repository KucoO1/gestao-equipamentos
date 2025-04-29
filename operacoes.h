#include "data.h"
#ifndef OPERACOES_H
#define OPERACOES_H

extern Operacao *operacoes;
extern int totalOperacoes;

void inserirOperacao();
void alterarOperacao();
void apagarOperacao();
void listarOperacoes();
void pesquisarOperacao();
void salvarOperacoesEmArquivo();
void carregarOperacoesDoArquivo();
void listarComponentesAtrasados();
void listarComponentesPorPosto();
void listarComponentesFora();
void listarComponentesNoPosto();
void PesquisarEmpresaComponente();

#endif