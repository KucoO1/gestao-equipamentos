#ifndef POSTOS_H
#define POSTOS_H


extern PostoTrabalho* postos;
extern int totalPostos;

void inicializarPostos();
void adicionarPosto();
void listarPostos();
void pesquisarPosto();
void alterarPosto();
int postoEmUso(int idPosto);
void removerPosto();

#endif