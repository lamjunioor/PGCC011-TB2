/*
 *------------------------------------------------------------------------------------------
 * Programa C++ para calcular a frequ�ncia de palavras em um arquivo texto.
 * Nome: contaPalavras98.cpp
 * Vers�o: serial
 *------------------------------------------------------------------------------------------
 * Autores:
 *    	Luciano   		<lucianoamjunior@gmail.com>
 *    	Marcos Morais 	<marcosmoraisjr@yahoo.com.br>
 * 		State University of Feira de Santana 
 * 		Feira de Santana - BA, Brazil
 * 		PGCC011 - Self-Performance Computing
 * 		Professor Angelo Am�ncio Duarte 
 * 		PhD in Computer Science, UAB, Spain
 *------------------------------------------------------------------------------------------
 * Instru��es:
 * 		compilar com: g++ contaPalavras.cpp -o contaPalavras -std=c++0x
 * 		executar com: ./contaPalavras _arquivo.txt resultado.txt
 *------------------------------------------------------------------------------------------
 * Este programa � um software livre; voc� pode redistribu�-lo e / ou modific�-lo
 * sob os termos da GNU General Public License conforme publicada pela
 * Free Software Foundation; seja a vers�o 2 da Licen�a, ou 
 * qualquer vers�o posterior, desde que cite os autores.
 *------------------------------------------------------------------------------------------
*/

#include <bits/stdc++.h>
#include <locale>
#include <initializer_list>

using namespace std;

// Procedimento para computar a frequ�ncia de cada palavra
// uso: mapearPalavras(linha, mapa)
std::map<std::string, int> mapearPalavras(string linha, map<string, int> M){
	// String para armazenar a palavra
	string palavra = "";
	char c;
	for (int i = 0; (unsigned)i < linha.size(); i++){
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
// uso: ordenarMapa (mapa)
std::multimap<int, string> ordenarMapa(map<string, int>& M){
  
    //Declara um multimap para realizar a ordenação
    multimap<int, string> MM;
  
    // Insere cada par (chave-valor) do
    // mapa M no multimap MM como um par (valor-chave)
    map<string, int>::iterator it;
    for (it = M.begin(); it != M.end(); it++){
        MM.insert({ it->second, it->first });
    }
  
    return MM;
}

// Procedimento para imprimir em arquivo
// uso: printToFile(MapaOrdenado,20,argv[2])
void imprimirParaArquivo(multimap<int, string> MapaOrdenado, int qntValores, int numLinhas, char arqOrigem[], char arqDestino[]) {
	
	char qtd[30];
	int i=0;
	FILE *arq = freopen(arqDestino,"w",stdout);
	std::multimap<int,string>::reverse_iterator grupopalavra;
	std::cout << "\n";
	std::cout << " ARQUIVO MAPEADO: " << arqOrigem << "\n";
	std::cout << " --------+" << "-----------------------------------------" << '\n';
	std::cout << " LINHAS  | " << numLinhas                                  << "\n";
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
	
// fun��o principal
int main(int argc, char* argv[]) {
	
	if(argc != 3) {
        	std::cerr << "\nSintaxe: " << argv[0] 
			          << " arquivo.txt resultado.txt \n\n" 
					  << std::endl;
			return 1;
    }
	setlocale(LC_ALL,"Portuguese");
	map<string, int> Mapa;
	multimap<int, string> MapaOrdenado;
  	FILE *arq;
  	char Linha[1000];
  	char *result;
  	int i;
  	int qntValores;
  	int contLinha = 0;
  	
	// Abre um arquivo TEXTO para LEITURA
	arq = fopen(argv[1], "rt");
  	
	// Se houve erro na abertura
  	if (arq == NULL){
     	printf("Problemas na abertura do arquivo\n");
     	return 0;
  	}
  	
  	while (!feof(arq)){
	  // o 'fgets' l� at� 1000 caracteres ou at� o '\n'
	  result = fgets(Linha, 1000, arq);
      if (result){  // Se foi poss�vel ler
	  	Mapa = mapearPalavras(result, Mapa);
	  	contLinha++;
	  }
  	}
  	fclose(arq);
	
	// Chama procedimento para organizar as palavras no mapa
    MapaOrdenado=ordenarMapa(Mapa);
    // Chama procedimento para imprimir o resultado em arquivo
	imprimirParaArquivo( MapaOrdenado, 20 , contLinha, argv[1] , argv[2] );
		
    // Gerar Arquivo de Sa�da:
  	/*std::multimap<int,string>::reverse_iterator rit;
  	rit=MapaOrdenado.rbegin();
  	freopen(argv[2],"w",stdout);
  	for (i=0; i<qntValores; i++){
    	//Garante que qntValores n�o for maior que quantidade de palavras no arquivo
		if(MapaOrdenado.size()<=(unsigned)i){
        	break;
    	}else{
	    	std::cout << rit->first << " => " << rit->second << '\n';
	    	++rit;
    	}
  	}*/
	return 0;
}
