#include "data.h"
#ifndef EMPRESA_H
#define EMPRESA_H

// Variáveis globais a serem usadas por outros ficheiros
extern int totalEmpresas;
extern Empresa* empresas;

void inicializarEmpresas();
void adicionarEmpresa();
void listarEmpresas();
void pesquisarEmpresa();
void alterarEmpresa();
void removerEmpresa();
void finalizarEmpresas();

#endif
