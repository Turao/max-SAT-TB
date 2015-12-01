#include <iostream>
#include <sstream>
#include <stdint.h>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <deque>
#include <ctype.h>
#include <ctime>
#include <set>

#define DEBUG false
#define TAMANHO_TABU 25
#define ITERACOES_TABU 100
#define LIMITE_SEM_MELHORA 25
#define TEMPO_LIMITE 5

using namespace std;

//Funcoes
void solucaoInicial();
void satClausulas();
void redimensiona(int n, int m);
int totalClausulasSatisfeitas();
void resetLimite();
void incLimite();

//Debug
void imprimeBarra();
void imprimeMatriz();
void imprimeVariaveis(vector<bool> vetor);
void imprimeClausulas();
void imprimeTabu();
void imprimeParametros();

//Tabu
void listaCandidatos();
void geraCandidato(int var);
void testaCandidatos();
void insereTabu(vector<bool> vetor);
bool buscaTabu(vector<bool> vetor);

//Variaveis Globais
int melhorSolucao;
int itSemMelhora;

int tamanhoTabu;
int iteracoesTabu;
int limiteSemMelhora;
int tempoLimite;
bool debug;

vector<bool> variaveisB;	//Vetor booleano de variaveis
vector<bool> clausulasB;	//Vetor booleano de clausulas

vector<bool> candidato;		//Vetor de variaveis do candidato em análise
vector<bool> melhorCandidato;	//Vetor de variaveis do melhor candidato
vector<bool> melhor;		//Vetor de variaveis do melhor caso

set<int> candidatos;		//Conjunto de variáveis pertencentes às clausulas não satisfeitas (candidatas a troca de valor)

vector<vector<int> > matriz;	//Matriz de pertencimento das variáveis às clausulas

deque<vector<bool> > tabu;	//Tabela TABU
