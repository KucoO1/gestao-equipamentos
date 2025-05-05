#include "data.h"
#ifndef EMPRESA_H
#define EMPRESA_H

// Variáveis globais a serem usadas por outros ficheiros
extern int totalEmpresas;
extern Empresa* empresas;

extern PropostaEmpresa* propostas;
extern int totalPropostas;


void inicializarEmpresas();
void adicionarEmpresa();
void listarEmpresas();
void pesquisarEmpresa();
void alterarEmpresa();
void removerEmpresa();
void finalizarEmpresas();


void adicionarProposta();
void alterarProposta();
void listarPropostas();
void removerProposta();
void compararPropostasPorComponente();
void carregarPropostasDoArquivo();
void salvarPropostasEmArquivo();
void finalizarOfertas();
void removerPropostasPorComponente(int idComponente);
void removerPropostasPorEmpresa(int idEmpresa);





#endif
