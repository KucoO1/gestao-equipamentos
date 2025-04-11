// data.h

#ifndef DATA_H
#define DATA_H

#define MAX 100

//Funcionarios
typedef struct {
    int id;
    char nome[50];
    char funcao[50];
    char descricao[100];
} Funcionario;

// Posto de Trabalho
typedef struct {
    int id;
    char nome[50];
    char local[50];
    char secao[50];
    char descricao[100];
    int idFuncionario;
} PostoTrabalho;

// Empresas
typedef struct {
    int id;
    char nome[50];
    char tipo[30]; // Fornecedor, Fabricante, Reciclagem...
    char contacto[50];
} Empresa;

// Componentes
typedef struct {
    int id;
    char designacao[50];
    char numeroSerie[30];
    char dataAquisicao[11];
    int garantiaMeses;
    int idFornecedor;
    int idFabricante;
    char tipo[30];
    char condicao[15]; // Novo, Usado...
    int idPosto;
    char observacoes[100];
} Componente;

// Operacao
typedef struct {
    int numeroInterno;
    char numeroExterno[30];
    int idPosto;
    int idComponente;
    int idEmpresa;
    char tipoOperacao[30]; // Reparação, Abatimento, Garantia...
    char dataSaida[11];
    char dataChegada[11];
    char dataPrevista[11];
    int idFuncionario;
    char dataOperacao[11];
    float montante;
    char observacoes[100];
} Operacao;

#endif
