#include "maxsat.h"

int main(int argc, char* argv[]) {

	clock_t begin, end;	//Tempo de execução do programa
	clock_t lBegin, lEnd;	//Tempo de execução do laco TABU

	int totalVariaveis, totalClausulas;	//Total de variaveis "X" e total de clausulas "Y"
	int entrada;
	int iteracoes;

	string linha, descarte;
	double elapsed_secs;

	begin = clock();

	//Le os parametros passados pelo usuario para customizacao do algoritmo
	if(argc < 5){
		imprimeBarra();
		cout << "Assumindo valores padrao de parametros:" << endl;
		tamanhoTabu = TAMANHO_TABU;
		iteracoesTabu = ITERACOES_TABU;
		limiteSemMelhora = LIMITE_SEM_MELHORA;
		tempoLimite = TEMPO_LIMITE;
		debug = DEBUG;
	}
	else{
		imprimeBarra();
		cout << "Valores dos parametros:" << endl;
		tamanhoTabu = atoi(argv[1]);
		iteracoesTabu = atoi(argv[2]);
		limiteSemMelhora = atoi(argv[3]);
		tempoLimite = atoi(argv[4]);
		debug = (argv[5] == "true");
	}

	imprimeParametros();
	


	//Laço para ler os valores
	while (getline(cin,linha)) {
		if (linha[0] == 'p'){
			istringstream iss(linha);
			iss >> descarte >> descarte >> totalVariaveis >> totalClausulas;
			break;
			
		}
	}

	//Redimensiona os vetores e a matriz
	redimensiona(totalVariaveis,totalClausulas);

	//Le o restante do arquivo para popular a matriz
	for (int j = 0; j < totalClausulas; ++j){
		getline(cin,linha);
		istringstream iss(linha);
		while(iss >> entrada){
			if(entrada == 0){
			 break;
			}
			matriz[abs(entrada)-1][j] = entrada/abs(entrada);
		}
	}


	//Solução Inicial
	solucaoInicial();
	candidato = variaveisB;
	satClausulas();
	melhorSolucao = totalClausulasSatisfeitas();
	//Fim da Solução inicial


	//Leitura do argumentos passados para o programa


	
	//*** Laco da BUSCA TABU ***//
	iteracoes = 0;
	while( (iteracoes < iteracoesTabu) && (itSemMelhora < limiteSemMelhora) ){

		listaCandidatos();

		testaCandidatos();
	
		iteracoes++;
	}
	//Fim da busca TABU


	//Calcula tempo total de execucao do programa
	end = clock();
	elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;


	//Saída
	imprimeBarra();
	cout << "Este problema tem " << totalVariaveis << " variaveis e " << totalClausulas << " clausulas." << endl;

	if(debug){
		imprimeMatriz();		//DEBUG
		imprimeVariaveis(variaveisB);	//DEBUG
		imprimeVariaveis(melhor);	//DEBUG
		imprimeClausulas();		//DEBUG
		imprimeTabu();
	}
	
	cout << "Clausulas satisfeitas: " << melhorSolucao << "." << endl;
	cout << "Tempo total decorrido: " << elapsed_secs << "s." << endl;

	imprimeBarra();

	return 0;
		
}

// Calcula a solucao inicial, caso a variavel ocorra mais vezes 
void solucaoInicial(){
	int soma;

	//Contabiliza as ocorrencias da variavel
	for (int i = 0; i < matriz.size(); ++i){
		soma = 0;
		for (int j = 0; j < matriz[0].size(); ++j){
			soma += matriz[i][j];
		}
		if(soma > 0){
			variaveisB[i] = 1;
		}
		else{
			variaveisB[i] = 0;
		}
	}
}

//Verifica a satisfabilidade de todas as clausulas
void satClausulas(){
	
	for (int j = 0; j < matriz[0].size(); ++j){
		clausulasB[j] = 0;
		
		if(debug){
			cout << "Clausula: [" << j+1 << "] ";	//DEBUG
		}
		for (int i = 0; i < matriz.size(); ++i){
			if(matriz[i][j] == 1) {
				if(debug){
					cout << " X[" << i+1 << "]:" << variaveisB[i] << " ";	//DEBUG
				}
				clausulasB[j] = clausulasB[j] | candidato[i];
			}
			else if (matriz[i][j] == -1){
				if(debug){				
					cout << " X~[" << i+1 << "]:" << variaveisB[i] << " ";	//DEBUG
				}
				clausulasB[j] = clausulasB[j] | !candidato[i];
			}
		}
		if(debug){
			cout << " com valor: " << clausulasB[j] << endl;	//DEBUG
		}
	}
}

//Redimensiona Vetores e Matriz globais
void redimensiona(int n, int m){
	variaveisB.resize(n);
	clausulasB.resize(m);

	matriz.resize(n);
	for (int i = 0; i < n; ++i){
		matriz[i].resize(m);
	}
}

//Calcula o total de clausulas satisfeitas
int totalClausulasSatisfeitas(){
	int resposta = 0;
	for (int j = 0; j < clausulasB.size(); ++j){
		resposta += clausulasB[j];
	}
	return resposta;
}

//Gera a lista de variáveis pertencentes a clausulas de resultado 0
void listaCandidatos(){
	set<int>::iterator it;
	candidatos.clear();
	for (int j = 0; j < clausulasB.size(); ++j){
		if(clausulasB[j] == 0){
			if(debug){			
				cout << "Clausula negada:" << j+1 << "vars:";	//DEBUG
			}
			for (int i = 0; i < matriz.size(); ++i){
				if( (matriz[i][j] == 1) || (matriz[i][j] == -1) ){
					if(debug){
						cout << i+1 << " ";	//DEBUG
					}
					candidatos.insert(i+1);
				}
			}
			if(debug){
				cout << endl;	//DEBUG
			}
		}
	}
	if(debug){
		for(it=candidatos.begin(); it!=candidatos.end(); ++it){		//DEBUG
			cout << *it << " ";
		}
	}
}

//Gera uma solução candidata a partir da atual solução, alterando APENAS uma variável
void geraCandidato(int var){
	candidato = variaveisB;
	candidato[var-1] = !candidato[var-1];
}

//Testa se o candidato é o melhor dos candidatos atuais
void testaCandidatos(){

	int solucao;
	int melhorSolucaoCandidato;

	clock_t lBegin, lEnd;
	double tempoLaco;

	set<int>::iterator it;

	lBegin = clock();	//Comeca a contar o tempo do laco Tabu

	//Gera a Solução apartir de VariaveisB
	candidato = variaveisB;
	satClausulas();
	melhorSolucaoCandidato = totalClausulasSatisfeitas();

	melhorCandidato = candidato;

	//Altera uma a uma as variaveis candidatas a alteracao
	for(it=candidatos.begin(); it!=candidatos.end(); ++it){

		geraCandidato(*it);
		satClausulas();
		solucao = totalClausulasSatisfeitas();
		if( (solucao > melhorSolucaoCandidato) && !(buscaTabu(candidato)) ){
			melhorCandidato = candidato;
			melhorSolucaoCandidato = solucao;
			if(debug){
				cout << "Solucao melhor encontrada: "<< melhorSolucaoCandidato << endl;
			}
		}
		lEnd = clock();
		tempoLaco = double(lEnd - lBegin) / CLOCKS_PER_SEC;
		if(debug){
			cout << "Tempo do laco TABU: " << tempoLaco << "s." << endl;
		}
		if(tempoLaco > tempoLimite){
			if(debug){
				cout << "Laco terminado por tempo." << endl;
			}
			break;
		}
	}
	variaveisB = melhorCandidato;
	if(melhorSolucaoCandidato > melhorSolucao){
		melhor = melhorCandidato;
		melhorSolucao = melhorSolucaoCandidato;
	}
	insereTabu(melhorCandidato);
	
}

//Insere o melhor candidato na lista Tabu
void insereTabu(vector<bool> vetor){
	if(!buscaTabu(vetor)){
		tabu.push_back(vetor);
		if(tabu.size() > tamanhoTabu){
			tabu.pop_front();
		}
		resetLimite();
	}
	else{
		incLimite();
	}
}

//Verifica se o array candidato está na lista Tabu
bool buscaTabu(vector<bool> vetor){
	//for(int i = 0; i < tabu.size(); ++i){
	if(find(tabu.begin(), tabu.end(), vetor) != tabu.end()){
		return true;
	}
	else{
		return false;
	}
}

//Funcoes sobre o LIMITE de iteracoes sem melhora (sem acrescentar novo candidato na tabela TABU)
void resetLimite(){
	itSemMelhora = 0;
}
void incLimite(){
	itSemMelhora++;
	if(debug){
		cout << "Iteracoes sem melhora:" << itSemMelhora << endl;
	}
}


//Funcoes de DEBUG e impressao
//Imprime Barra Separadora
void imprimeBarra(){
	for (int i = 0; i < 80; ++i){
		cout << "=";
	}
	cout << endl;
}

//Imprime a matriz de pertencimento
void imprimeMatriz(){
	imprimeBarra();
	cout << "Representacao em matriz das entradas " << endl;

	for (int j = 0; j < matriz[0].size(); ++j){
		for (int i = 0; i < matriz.size(); ++i){
			cout << matriz[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Fim da matriz" << endl;
}

// Imprime o valor armazenado nas variáveis
void imprimeVariaveis(vector<bool> vetor){
	imprimeBarra();
	cout << "Valor das variaveis" << endl;

	for (int i = 0; i < vetor.size(); ++i){
		cout << "Variavel [" << i+1 << "]:" << vetor[i] << endl;
		
	}
		
	cout << "Fim das variaveis" << endl;
}

// Imprime o valor armazenado nas Clausulas
void imprimeClausulas(){
	imprimeBarra();
	cout << "Valor das Clausulas" << endl;

	for (int j = 0; j < clausulasB.size(); ++j){
		cout << "Clausula [" << j+1 << "]:" << clausulasB[j] << endl;
		
	}
		
	cout << "Fim das clausulas" << endl;
}

//Imprime a tabela TABU
void imprimeTabu(){
	imprimeBarra();
	cout << "Representacao da tabela TABU: " << tabu.size() << " elemento(s)." << endl;

	for (int i = 0; i < tabu.size(); ++i){
		for (int j = 0; j < tabu[0].size(); ++j){
			cout << tabu[i][j] << " ";
		}
		cout << endl;
	}
	cout << "Fim da TABU" << endl;
}

//Imprime Parametros do algoritmo BUSCA TABU
void imprimeParametros(){
		cout << "Tamanho da tabela: " << tamanhoTabu << endl;
		cout << "Numero maximo de iteracoes totais: " << iteracoesTabu << endl;
		cout << "Limite de iteracoes sem melhora de uma busca: " << limiteSemMelhora << endl;
		cout << "Tempo maximo de cada iteracao: " << tempoLimite << "s" << endl;
}
