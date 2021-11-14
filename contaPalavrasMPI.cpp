/*
 *------------------------------------------------------------------------------------------
 * Programa C++ para calcular a frequência de palavras em um arquivo texto usando MPI.
 * Nome: contaPalavrasMPI.cpp
 * Versào: 13.11.2021
 *------------------------------------------------------------------------------------------
 * Autores:
 *    	Luciano   		<lucianoamjunior@gmail.com>
 *    	Marcos Morais 	<marcosmoraisjr@yahoo.com.br>
 * 		State University of Feira de Santana 
 * 		Feira de Santana - BA, Brazil
 * 		PGCC011 - Self-Performance Computing
 * 		Professor Angelo Amâncio Duarte 
 * 		PhD in Computer Science, UAB, Spain
 *------------------------------------------------------------------------------------------
 * Instruções:
 * 		compilar com: mpicxx contaPalavrasMPI.cpp -o contaPalavrasMPI.e -std=c++0x
 * 		executar com: mpirun -n 5 ./contaPalavrasMPI.e _vers.txt resultado.txt
 *------------------------------------------------------------------------------------------
 * Este programa é um software livre; você pode redistribuí-lo e / ou modificá-lo
 * sob os termos da GNU General Public License conforme publicada pela
 * Free Software Foundation; seja a versão 2 da Licença, ou 
 * qualquer versão posterior, desde que cite os autores.
 *------------------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
#include <mpi.h>
#define MAX_WORD_LENGTH 30

using namespace std;

#pragma region Region_variaveis 
	int nprocs; 
	int myRank;
	// estrutura  para guardar a palavras e a frequência
	struct Word {
		char word[MAX_WORD_LENGTH];
		int freq;
	};
#pragma endregion Region_variaveis

#pragma region Region_Funcoes
	// Procedimento para computar a frequência de cada palavra
	// uso: mapearPalavras(linha, m)
	std::map<std::string, int> mapearPalavras(string linha, map<string, int> M){
		// String para armazenar a palavra
		string palavra = "";
		char c;
		for (int i = 0; i < linha.size(); i++){
			c=tolower(linha[i]);
	    	// Verifique se o caractere atual
	        // é  um espaço em branco então
	        // significa que temos uma palavra
			if (c == ' '){
				if (palavra.size()>1){
					// Se a palavra atual
		            // não for encontrado, insira
		            // palavra atual com frequência 1
					if (M.find(palavra) == M.end()){
						M.insert(make_pair(palavra, 1));
						palavra = "";
					}
					// atualiza a frequêcia
					else{
						M[palavra]++;
						palavra = "";
					}
				}
				else{
					palavra = "";
				}
			}
	        // Se o caractere atual for uma das opções abaixo,adicionar na palavra     
	        if((c>=97 && c<=122)||(c>=-32 && c<=-1)){//Aqui temos os numerais dos caracteres de letras e acentuações na tabela ASCII
	           palavra += c;            
	        }
	                   
		}
		if (palavra.size()>1){
			// Armazenando a última palavra da string
			if (M.find(palavra) == M.end())
				M.insert(make_pair(palavra, 1));
			// Atualiza a frequencia 
			else
				M[palavra]++;
			return M;
		}else{
			return M;
		}
	}
	
	// procedimento para ordenar as palavras computadas no arquivo
	// uso: ordenarMapa(map, m)
	std::multimap<int, string> ordenarMapa(map<string, int>& M){
	  
	    //Declara um multimap para realizar a ordenação
	    multimap<int, string> MM;
	  
	    //Estabelece um iterator para o mapa
	    map<string, int>::iterator it;
	
	    // Insere cada par (chave-valor) do
	    // mapa M no multimap MM como um par (valor-chave)
	    for (it=M.begin(); it!=M.end(); it++) {
	        MM.insert({ it->second, it->first });
	    }
	  
	    return MM;
	}
	
	// Procedimento para unificar mapas
	// uso: unirMapas(Mapas, MapasJunto, nprocs)
	std::map<string, int> unirMapas(map<string, int> M[], map<string, int> MM, int N){	
			
		int i;  
		for(i=0; i<N-1; i++){
			
		    map<string, int>::iterator it;
			
			for(it = M[i].begin(); it != M[i].end(); it++) {
				if (MM.find(it->first) == MM.end()){
		        	MM.insert({it->first, it->second});
				}else{
					MM[it->first] += it->second;
				}
		    }
		}
		return MM;
	}

	// Procedimento para imprimir em arquivo
	// uso: imprimirParaArquivo(MapaOrdenado, qntValores, contLinha, argv[1], argv[2])
	void imprimirParaArquivo(multimap<int, string> MapaOrdenado, int qntValores, int numLinhas, char arqOrigem[], char arqDestino[]) {
		
		char qtd[30];
		int i=0;
		FILE *arq = freopen(arqDestino,"w",stdout);
		std::multimap<int,string>::reverse_iterator grupopalavra;
		std::cout << "\n";
		std::cout << " ARQUIVO MAPEADO: " << arqOrigem << "\n";
		std::cout << " --------+" << "-----------------------------------------" << '\n';
		std::cout << " LINHAS  | " << numLinhas                                  << '\n';
		std::cout << " --------+" << "-----------------------------------------" << '\n';
		std::cout << " FREQ.   |" << " PALAVRA(S)                              " << '\n';
		std::cout << " --------+" << "-----------------------------------------" << '\n';
		
		grupopalavra=MapaOrdenado.rbegin();

		if (arq == NULL){
			printf(" Problemas gerar o arquivo '%s'.\n", arqDestino);
		}
		else
		{
			for (i=0; i<qntValores; i++){
				
				if(MapaOrdenado.size()<=(unsigned)i) 
				{ 
			    	break;
				}
				else
				{
					sprintf(qtd, " %07d", grupopalavra->first);
			    	std::cout << qtd << " | " << grupopalavra->second << '\n';
			    	++grupopalavra;
				}
			}
			std::cout << " --------+" << "-----------------------------------------" << '\n';
			std::cout << " LIMITE  | " << i << " GRUPOS DE PALAVRAS                " << '\n';	
			std::cout << " --------+" << "-----------------------------------------" << '\n';
		}
	}
	
	// Procedimento para converter o tempo em Hora, Minuto, e Segundos.
	int converteHMS(double tempo) {
		int segundos, h, m, s, resto;
		segundos = tempo;
		
		h = segundos / 3600;
		resto = segundos % 3600;
		m = resto / 60;
		s = resto % 60;
		printf("%d:%d:%d\n", h, m, s);
		
		return 0;
	}
#pragma endregion Region_Funcoes

// bloco de código principal
#pragma region Region_Main
int main(int argc, char* argv[]) {
	
	// Início do bloco MPI 
	MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);	// pega o número de nodos	
	MPI_Comm_rank(MPI_COMM_WORLD, &myRank); // pega o rank
  	MPI_Status status;
  	
	// garante a passagem de argumentos corretamente
	if(argc != 3) {
        	std::cerr << "\nSintaxe: mpirun -n 4" << argv[0] 
			          << " arquivo.txt resultado.txt \n\n" 
					  << std::endl;
	        MPI_Abort(MPI_COMM_WORLD,1);
			return 1;
    }
	
	setlocale(LC_ALL,"Portuguese");
  
	// Variáveis 
	map<string, int> Mapa; // mapa
	map<string, int> MapaJunto;	// mapa unificado
	multimap<int, string> MapaOrdenado;	// mapa ordenado
  	FILE *arq; 
  	char *result; 
  	char Linha[1000];
  	int i = 0;
  	int contProc = 1;
  	int contLinha = 0;
	int cont = 0;
	int number_of_keys;
	int sizesMaps[nprocs-1];  
	int sizeLinha;
	
	// Variáveis usadas na criaçao do datatype
	int blocklen[2] = { MAX_WORD_LENGTH, 1};   
	map<string, int> Mapas[nprocs-1];
	MPI_Aint disp[2];  
	disp[0] = sizeof(int); 
  	disp[1] = 0; 
	MPI_Datatype WordType; 
  	MPI_Datatype type[2] = { MPI_CHAR, MPI_INTEGER }; 
  	MPI_Type_create_struct(2, blocklen, disp, type, &WordType); 
  	MPI_Type_commit(&WordType); 
  	
	// variáveis para calculo de tempo_inicial, tempo_final;
	time_t tempo_inicial, tempo_final;
	
	if(myRank==0){
		
	    // pegando tempo inicial do RANK 0
		time(&tempo_inicial);
        
		// abertura do arquivo 
	  	arq = fopen(argv[1], "rt");
	  	
		// Se ocorrer erro na abertura...
		if (arq == NULL){
			printf(" Problemas na abertura do arquivo\n");
		    return 0;
		}
		
		// vamos contar a quantidade de linhas
		while (!feof(arq)){	
			// o 'fgets' lê até 1000 caracteres ou até o '\n'
			result = fgets(Linha, 1000, arq);  
	      	if (result){ 	
	      		contLinha++;
			}
		}
	  	fclose(arq);

		// rank 0 >> envia a quantidade de linhas
		for(i=0; i<nprocs-1; i++){
			MPI_Send(&contLinha, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD);
		}
	}
	
	if(myRank!=0){
		// works >> recebem a quantidade de linhas
		MPI_Recv(&contLinha, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
	}
	
	if(myRank==0){	  	
		// RANK0 >> Abre um arquivo texto...
  		arq = fopen(argv[1], "rt");
	  	
		// Se ocorrer erro na abertura...
	  	if (arq == NULL){
	     	printf(" Problemas na abertura do arquivo\n");
	     	return 0;
	  	}
	  	while (!feof(arq)){
			// o 'fgets' lê até 1000 caracteres ou até o '\n'
      		result = fgets(Linha, 1000, arq);
			if (result){
				
				//Se contProc <> nprocs e não for o último nó 
				if(contProc!=(nprocs-1)){
	
					if((((contProc-1) * ((int)(contLinha/(nprocs-1))))<=cont) && ((contProc * ((int)(contLinha/(nprocs-1))))> cont)){
						
						sizeLinha=strlen(result); // pega o tamanho da linha
						
						//RANK0 >> envia tamanho da linha para work >>
						MPI_Send(&sizeLinha, 1, MPI_INT, contProc, 1, MPI_COMM_WORLD);
						for (i=0; i<sizeLinha; i++){
							//RANK0 >> envia linha para work >>
							MPI_Send(&result[i], 1, MPI_CHAR, contProc, 2, MPI_COMM_WORLD);
						}
					}else{
						contProc++;
						sizeLinha=strlen(result);
						
						//RANK0 >> envia tamanho da linha para work >>
						MPI_Send(&sizeLinha, 1, MPI_INT, contProc, 1, MPI_COMM_WORLD);
						for (i=0; i<sizeLinha; i++){
							
							//RANK0 >> envia linha i para work >>
							MPI_Send(&result[i], 1, MPI_CHAR, contProc, 2, MPI_COMM_WORLD);
						}
					}
				}else{
					sizeLinha=strlen(result);
					
					//RANK0 >> envia tamanho da linha para works >>
					MPI_Send(&sizeLinha, 1, MPI_INT, contProc, 1, MPI_COMM_WORLD);
					for (i=0; i<sizeLinha; i++){
						
						//RANK0 >> envia linha i para works >>
						MPI_Send(&result[i], 1, MPI_CHAR, contProc, 2, MPI_COMM_WORLD);
					}
				}
				cont++;		
			}
  	    }
  		fclose(arq);
	}

	if(myRank!=0){
		
		// pegando tempo inicial do WORKS
		time(&tempo_inicial);
		
		string aux;
		char c;
		if(myRank!=(nprocs-1)){

			//calculando a divisão...
			int divisao=(int)contLinha/(nprocs-1);

			for(cont=0; cont<divisao; cont++){
				//WORKS >> recebe tamanho da linha
				MPI_Recv(&sizeLinha, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
				for (i=0; i<sizeLinha; i++){
					//WORKS >> recebe a linha
					MPI_Recv(&c, 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD, &status);
					aux += c;
				}
		  		
				//WORKS >> mapeiam a linha (separa as palavras e calcula a frequência)
				Mapa = mapearPalavras(aux, Mapa);
		  		aux=""; //limpa a variável auxiliar
			}
		}else{
			cont=((int)contLinha/(nprocs-1))*(nprocs-2);
			for(cont; cont<contLinha; cont++){
				//WORKS >> recebe o tamanho da linha 
				MPI_Recv(&sizeLinha, 1, MPI_INT, 0, 1, MPI_COMM_WORLD, &status);
				for (i=0; i<sizeLinha; i++){
					//WORKS>> recebe a linha como char 
					MPI_Recv(&c, 1, MPI_CHAR, 0, 2, MPI_COMM_WORLD, &status);
					aux += c;
				}
				//WORKS >> mapeiam a linha (separa as palavras e calcula a frequência)
		  		Mapa = mapearPalavras(aux, Mapa);
		  		aux="";
			}
		}
		
		//pega a quantidade de chaves do mapa
		number_of_keys=Mapa.size();
		//WORKS >> envia a quantidade de chaves
		MPI_Send(&number_of_keys, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	
	if(myRank==0){
		for(i=0; i<nprocs-1; i++){
			//RANK0 >> recebe chaves
			MPI_Recv(&number_of_keys, 1, MPI_INT, i+1, 0, MPI_COMM_WORLD, &status);
			//armazena chaves em um vetor 
			sizesMaps[i]=number_of_keys;
		}		
	}

	if(myRank!=0){
		
		// WORKS >> Cria um vetor de tipo Word para enviar os dados do mapa para o rank 0
		std::vector<Word> words(number_of_keys);
		map<string, int>::iterator it;
		i=0;
		
		for (it=Mapa.begin(); it!=Mapa.end(); it++) {
			strcpy(words[i].word, it->first.c_str());
			words[i].freq = it->second;
			i++;
		}
		
		// WORKS >> envia vetor para rank 0
		for(i=0; i<number_of_keys; i++){
			MPI_Send(&words[i], 1, WordType, 0, 2, MPI_COMM_WORLD);
		}
		
		///////////////////////////////////////////////////////////////////////// 
		//  Calculando tempo...
		time(&tempo_final);
		double tempo = (double)(tempo_final - tempo_inicial) ;
		std::cout << " Rank      " << myRank << std::endl;
		std::cout << " Tempo (I) " << tempo_inicial << std::endl;
		std::cout << " Tempo (F) " << tempo_final << std::endl;
		std::cout << " Tempo (T) " << tempo << " segundos." << std::endl;
	    /////////////////////////////////////////////////////////////////////////
	}
	
	if(myRank==0){
		
		for(i=0; i<nprocs-1; i++){
			//RANK0 >>> cria um vetor do tamanho do mapa do rank i
			std::vector<Word> words(sizesMaps[i]);
			
			for(int j=0; j<sizesMaps[i]; j++){
				//RANK0 >>> recebe os dados mapeados...
				MPI_Recv(&words[j], 1, WordType, i+1, 2, MPI_COMM_WORLD, &status);
			} 

			for(int j=0; j<sizesMaps[i]; j++){
				//RANK0 >>> insere os dados no vetor de mapas[i]
				Mapas[i].insert(std::pair<string,int>(words[j].word, words[j].freq)); 
			}
		}
		
		// Chama funcao para unificar os mapas
		MapaJunto = unirMapas( Mapas, MapaJunto, nprocs );
		// Chama funcao para organizar as palavras no mapa
		MapaOrdenado = ordenarMapa( MapaJunto );
		// Chama procedimento para imprimir o resultado em arquivo
		imprimirParaArquivo( MapaOrdenado, 20 , contLinha, argv[1] , argv[2] ); 
		
		///////////////////////////////////////////////////////////////////////// 
		//  Calculando tempo...
		time(&tempo_final);
		
		double tempo = (double)(tempo_final - tempo_inicial) ;
		std::cout << " Rank      " << myRank << std::endl;
		std::cout << " Tempo (I) " << tempo_inicial << std::endl;
		std::cout << " Tempo (F) " << tempo_final << std::endl;
		std::cout << " Tempo (T) " << tempo << " segundos." << std::endl;
		std::cout << " Tempo (C) " << converteHMS(tempo) << std::endl;
	    /////////////////////////////////////////////////////////////////////////
	}
	
	MPI::Finalize();
	return 0;
}
#pragma endregion Region_Main
