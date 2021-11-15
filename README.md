# Contador de Frequência de Palavras MPI

## 🎁 Sobre

Este projeto tem como objetivo principal atender a uma demanda avaliativa na disciplina PGCC011 (Computação de Alto Desempenho) do Programa de Pós-Graduação em Ciências da Computação (stricto sensu) da Universidade Estadual de Feira de Santana. Para tanto, o presente projeto deve contribuir na verificação do comportamento da escalabilidade de códigos seriais nas linguagens C, bem como as possíveis razões para as diferenças (ou não) de desempenho. Desta forma, foram desenvolvidos os códigos serial e paralelo na linguagem de programação C++ para cômputo da frequência de palavras em arquivos textos.

## 🚀 Começando

Os Arquivos necessários e todas as orientações para uso deste projeto, estão neste repositório.

### 📋 Pré-requisitos para compilação

Recomendamos que o sistema operacional e os pacotes, descritos acima, estejam na versão mais recente possível.

Siga os passos abaixo:

```
1. Crie uma pasta na raiz do seu sistema operacional.
2. Baixe os arquivos deste projeto na pasta criada.
3. Seus arquivos estão prontos para uso.
```

Abaixo, orientações de compilação:

**Pré-Requisitos**
Antes de começar, você vai precisar de um cluster em pleno funcionamento e os seguintes pacotes instalados: gcc e OpenMPI

### ⚙️ Executando

Para iniciar execute os seguintes comandos:

**Gerar executáveis C**

*Para o código serial:*
```
# Esta execução irá gerar o executável serial de nome contaPalavras.out
$ g++ contaPalavras.cpp -o contaPalavras -std=c++0x
```

*Para o código paralelo:*
```
# Esta execução irá gerar o executável paralelo de nome contaPalavrasMPI.ou
$ mpicxx contaPalavrasMPI.cpp -o contaPalavrasMPI.e -std=c++0x
```

**Como executar**

*Para o código serial em C (após gerar o executável):*
```
$ ./contaPalavras <nomedoarquivo.txt> <arquivosaida.txt>
```

*Para o código paralelo em C (após gerar o executável):*
```
$ mpirun -n <quantidadenodos> ./contaPalavrasMPI.e <nomedoarquivo.txt> <arquivosaida.txt>
```


### 🔩 Funcionamento

**Geral** <br />

Dado um arquivo texto e um inteiro **n**, exibir as **n** palavras mais comuns no arquivo (e o número de suas ocorrências)  em frequência decrescente.

Os códigos iniciam com a declaração de uma função de nome mapearPalavras, que recebe uma string contendo uma linha do arquivo a ser lido e um map<string, int> em que a string é a palavra e o int é a frequência dessa palavra. Após, temos a separação da linha em caracteres, fazendo sua divisão em palavras. Na função mapearPalavras são considerados os requisitos para validar a palavra (requisitos estipulados no problema da atividade). Por fim, a função retorna o mapa com as alterações feitas após o processamento da linha.

Além disso, no código em paralelo, temos seguintes funções auxiliares **ordenarMapa** (ordena o mapa), **unirMapas** (junta os mapas apenas no código em paralelo), **imprimirParaArquivo** (imprime o resultado para arquivo). 

Na função principal de cada código temos a seguinte ordem: 


*1. Declaração de variáveis*
```
Aqui declaramos as variáveis auxiliares, o mapa de tipo <string, int> e 
um inteiro de nome qntValores, que recebe o valor 'n' 
citado acima (para estipular a quantidade de palavras que o usuário deseja saber a frequência em ordem decrescente);
Também foi criado um "Datatype" mpi para o código em paralelo objetivando criar um objeto do tipo "Word".
```

*2. Abertura de um arquivo para processamento*
```
Usar no formato .txt;
```

*3. Passa cada linha do arquivo, para a função mapearPalavras (descrita acima)* 
```
No caso dos algoritimos em paralelo, ocorre uma distribuição das linhas para cada nó do cluster;
```

*3.1. (Somente para algoritmos em paralelo)*
```
Junta os mapas;
```

*4. Ordena o mapa*
```
Usa a função ordenarMapa;
```

*5. Gera um arquivo de saída*
```
O arquivo contém as 'n' palavras mais comuns no arquivo (e o número de suas ocorrências) em frequência decrescente. 
```

**Arquivos de E/S** <br />

Conforme descrito no item acima, os arquivos aceitos para o processamento são do formato .txt. 
Recomendamos que a codificação do arquivo.txt seja ANSI, pois o sistema foi implementado para identificação de caracteres apenas nesse formato.

Ao final da execução, os códigos devem gerar um arquivo de saída. 
Esse arquivo contém a frequência das n palavras encontradas, como no exemplo: "20 => casa"

## 📦 Arquivos

1. Algoritmo serial em C++
```
contaPalavras.cpp 
```
2. Versão paralelizada do item 1, em C++, usando OpenMPI
```
contaPalavrasMPI.cpp
```


## 🛠️ Construído em

* [C++](http://www.bloodshed.net/devcpp.html) 

## ✒️ Autores

<table>
  <tr>
    <td align="center"><a href="https://github.com/lamjunioor"><img style="border-radius: 15px 50px 30px 5px;" src="https://avatars.githubusercontent.com/u/42066765?v=4" width="100px;" alt=""/><br /><sub><b>Luciano Júnior</b></sub></a><br /> Documentação/Desenvolvimento</td>
    <td align="center"><a href="https://github.com/mmstec"><img style="border-radius: 15px 50px 30px 5px;" src="https://avatars.githubusercontent.com/u/26969915?v=4" width="100px;" alt=""/><br /><sub><b>Marcos Morais</b></sub></a><br />Documentação/Desenvolvimento</a></td>
  </tr>
</table>

## 🎁 Instituição de Ensino

* [UEFS - Universidade Estadual de Feira de Santana](https://www.uefs.br/) <br />
* [PGCC - Pós-Graduação em Ciências da Computação](https://pgcc.uefs.br/home) <br />
* PGCC011 - Computação de Alto Desempenho <br />
* Professor - [Angelo Amâncio Duarte](https://pgcc.uefs.br/sobre/docentes/angeloduarte) <br /> 

## 🚀 Citação

```
@MISC{contapalavras,
    author = {Luciano Junior, Marcos Morais},
    title = {{Contador de Frequencia de Palavras em MPI}},
    howpublished = "\url{https://github.com/mmstec/PGCC011-TB2}",
    year = {2021},
  }
```
## 📄 Licença

Este projeto está sob a licença - veja o arquivo [LICENSE.md](https://github.com/mmstec/PGCC011/blob/main/LICENSE.md) para detalhes.

