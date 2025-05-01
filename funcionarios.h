// interface.h
#include "data.h"

#ifndef FUNCIONARIOS_H
#define FUNCIONARIOS_H

extern Funcionario* funcionarios;
extern int totalFuncionarios;

int menuPrincipal();

void salvarConfiguracao();
void carregarConfiguracao();
void salvarFuncionariosEmArquivo();
void carregarFuncionariosDoArquivo();
void finalizarFuncionarios();

void inicializarFuncionarios();
void alterarLimiteFuncionarios();
void adicionarFuncionario();
void listarFuncionarios();
void pesquisarFuncionario();
void alterarFuncionario();
void removerFuncionario();
#endif