#include "data.h"
#ifndef COMPONENTES_H
#define COMPONENTES_H


// Variáveis globais a serem usadas por outros ficheiros
extern Componente *componentes;
extern int totalComponentes;

extern Subcomponente *subcomponentes;
extern int totalSubcomponentes;

void salvarConfiguracaoComponentes();
void carregarConfiguracaoComponentes();
void salvarComponentesEmArquivo();
void carregarComponentesDoArquivo();
void finalizarComponentes();

void inicializarComponentes();
void alterarLimiteComponentes();
void adicionarComponente();
void listarComponentes();
void pesquisarComponente();

void alterarComponente();
void trocarPostoComponente();
void removerComponente();

void salvarSubcomponentesEmArquivo();
void carregarSubcomponentesDoArquivo();
void finalizarSubcomponentes();

void adicionarSubcomponente();
void alterarSubcomponente();
void listarSubcomponentesDeComponente();
void removerSubcomponente();

#endif
