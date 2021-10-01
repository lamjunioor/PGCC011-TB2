// Programa C++ para calcular a frequência
// de cada palavra na string dada
#include <bits/stdc++.h>
#include <locale>
#include <omp.h>

using namespace std;

// Função para imprimir a frequência de cada palavra
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
			if (palavra.size()>1)
			{
				// Se a palavra atual
	            // não for encontrado, insira
	            // palavra atual com frequência 1
				if (M.find(palavra) == M.end())
				{
					M.insert(make_pair(palavra, 1));
					palavra = "";
				}
				// atualiza a frequêcia
				else
				{
					M[palavra]++;
					palavra = "";
				}
			}
			else{
				palavra = "";
			}
		}
        // Se o caractere atual for uma das opções abaixo,adicionar na palavra     
        if((c>=97 && c<=122)||(c>=-32 && c<=-1))
		{//Aqui temos os numerais dos caracteres de letras e acentuações na tabela ASCII
           palavra += c;            
        }
                   
	}
	if (palavra.size()>1)
	{
		// Armazenando a última palavra da string
		if (M.find(palavra) == M.end())
			M.insert(make_pair(palavra, 1));
		// Atualiza a frequencia 
		else
			M[palavra]++;
		return M;
	}
	else
	{
		return M;
	}
}

std::multimap<int, string> sort(map<string, int>& M){
  
    //Declara um multimap para realizar a ordenação
    multimap<int, string> MM;
  
    // Insere cada par (chave-valor) do
    // mapa M no multimap MM como um par (valor-chave)
    for (auto& it : M) {
        MM.insert({ it.second, it.first });
    }
  
    return MM;
}

// função principal
int main(){
	setlocale(LC_ALL,"Portuguese");
	omp_set_num_threads(4); // determina o número de threads
	//printf("%d", omp_get_num_threads());
	map<string, int> Mapas[4];
	map<string, int> MapaJunto;
	multimap<int, string> MapaOrdenado;
  	FILE *arq;
  	char Linha[1000];
  	char *result;
  	int i;
  	int qntValores;
  	// Abre um arquivo TEXTO para LEITURA
  	arq = fopen("arquivo.txt", "rt");
  	// Se houve erro na abertura
  	if (arq == NULL){
     	printf("Problemas na abertura do arquivo\n");
     	return 0;
  	}
  	
  	
  	#pragma omp parallel
	{
	  	while (!feof(arq))
		{
			// Lê uma linha 
			result = fgets(Linha, 1000, arq);  // o 'fgets' lê até 999 caracteres ou até o '\n'
			if (result)
			{
		    	// Se foi possível ler
	      		Mapas[omp_get_thread_num()] = mapearPalavras(result, Mapas[omp_get_thread_num()]);
			}
  	    }
	}
   
	fclose(arq);

	for(i=0; i<4; i++){
		for (auto& it : Mapas[i]) 
		{
			if (MapaJunto.find(it.first) == MapaJunto.end())
			{
        		MapaJunto.insert({ it.first, it.second });
			}
			else
			{
				MapaJunto[it.first]+=it.second;
			}
		}
	}	

	MapaOrdenado=sort(MapaJunto);
	qntValores= 20; //PERSONALIZAR QUANTIDADE DE VALORES A SEREM IMPRESSOS
    	
    // Gerar Arquivo de Saída:
  	std::multimap<int,string>::reverse_iterator rit;
  	rit=MapaOrdenado.rbegin();
  	freopen("resultadoOMP.txt","w",stdout);
  	for (i=0; i<qntValores; i++)
	{
    	//Garante que qntValores não é maior que quantidade de palavras no arquivo
		if(MapaOrdenado.size()<=(unsigned)i)
		{
        	break;
    	}
		else
		{
			//imprime a quantidade de palavras e a palavra
    		std::cout << rit->first << " => " << rit->second << '\n';
    		++rit;
    	}
  	}	
	return 0;
}
