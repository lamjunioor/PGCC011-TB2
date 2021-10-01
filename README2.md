# Contador de Frequência de Palavras

## 🎁 Sobre

Este projeto tem como objetivo principal atender a uma demanda avaliativa na disciplina PGCC011 (Computação de Alto Desempenho) do Programa de Pós-Graduação em Ciências da Computação da Universidade Estadual de Feira de Santana. Para tanto, o presente projeto deve contribuir na verificação do comportamento da escalabilidade de códigos seriais nas linguagens C e em Python, bem como as possíveis razões para as diferenças (ou não) de desempenho. Desta forma, foram desenvolvidos códigos seriais, paralelos e modulares nas linguagens de programação C++ e Python v3 para cômputo da frequência de palavras em arquivos textos.

## 🚀 Começando

Os Arquivos necessários e todas as orientações para uso deste projeto, estão neste repositório.
Antes de começar, você vai precisar ter instalado em sua máquina o sistema Operaciol Linux e os seguintes pacotes:<br />
gcc; python3; python3-distutils:

### 📋 Pré-requisitos para compilação

Recomendamos que o sistema operacional e os pacotes, descritos acima, estejam na versão mais recente possível.

Siga os passos abaixo:

```
1. Crie uma pasta na raiz do seu sistema operacional.
2. Copie os arquivos que você baixou para a pasta criada.
3. Pronto, seus arquivos estão prontos para uso.
```

Abaixo, orientações de compilação :

```
contaPalavras.cpp  
--> Para compilar, execute g++ contaPalavras.cpp -o contaPalavras

contaPalavrasOMP.cpp  
--> Para compilar, execute g++ -fopenmp contaPalavrasOMP.cpp -o contaPalavrasOMP

contapalavras.py
--> explicar aqui

contaPalavrasModulo.py
--> explicar aqui

modulo.cpp
--> explicar aqui

```


### 🔩 Funcionamento

**Geral** <br />

Dado um arquivo texto e um inteiro **n**, exibir as **n** palavras mais comuns no arquivo (e o número de suas ocorrências)  em frequência decrescente.
Todos os códigos (com exceção do contaPalavrasModulo.py) possuem implementação similar. Eles iniciam com a declaração de uma função de nome mapearPalavras, que recebe uma string contendo uma linha do arquivo a ser lido e um map<string, int> em que a string é a palavra e o int é a frequência dessa palavra. Após isso, temos a separação da linha em caracteres, fazendo sua divisão em palavras. Na função mapearPalavras são considerados os requisitos para validar a palavra (requisitos estipulados no problema da atividade). Por fim, a função retorna o mapa com as alterações feitas após o processamento da linha.

Além disso, temos uma função de nome sort, que recebe o mapa após o processamento de todo o arquivo e realiza a ordenação dele de acordo com a frequência de cada palavra encontrada.

Na função principal de cada código temos a seguinte ordem: 
```
1. Declaração de variáveis - Aqui declaramos as variáveis auxiliares, o mapa de tipo <string, int> e um inteiro de nome qntValores, que recebe o valor **n** citado acima (para estipular a quantidade de palavras que o usuário deseja saber a frequência em ordem decrescente);
2. Abertura de um arquivo no formato .txt para o processamento;
3. Passa cada linha do arquivo, para a função mapearPalavras (descrita acima);
4. Ordena o mapa com a função sort (descrita acima);
5. Gera um arquivo de saída contendo as **n** palavras mais comuns no arquivo (e o número de suas ocorrências) em frequência decrescente.
```
**Arquivos de E/S** <br />

Conforme descrito no item acima, os arquivos aceitos para o processamento são do formato .txt. Nos códigos implementados utilizamos o nome do arquivo de entrada como “arquivo.txt” e recomendamos que os usuários que utilizarem nossos códigos submetam os arquivos com esse nome (para evitar precisar alterar o código). Além disso, recomendamos que a codificação do arquivo .txt seja ANSI, pois o sistema foi implementado para identificação de caracteres apenas nesse formato.

Ao final da execução, os códigos devem gerar um arquivo de saída nomeado “resultadoC.txt”, "resultadoOMP.txt", “resultadoPy.txt” ou “resultadoModulo.txt”, dependendo da versão do código executado.


### ⚙️ Executando

Nesta seção, é explicado como executar o projeto.

**Pré-Requisitos**


```
Gerar executáveis C
Gerar módulo Py
Como executar

```

## 📦 Arquivos

1. contaPalavras.cpp - Algoritmo serial em C++.
2. contaPalavrasOMP.cpp - Versão paralelizada do item 1, em C++, usando OpenMP
3. contaPalavras.py - Verão serial do item 1, em Python v3.
4. modulo.cpp - Versão modularizada do item 2 em Python.
5. contaPalavrasModulo.py - Algoritmo em Python usando o módulo (item 4).

## 🛠️ Construído com

* [C++](http://www.bloodshed.net/devcpp.html) 
* [PYTHON V3](https://www.python.org) 

## ✒️ Autores

* **Luciano Junior** - *Documentação/Desenvolvimento* - [desenvolvedor](https://github.com/mmstec)
* **Marcos Morais** - *Documentação/Desenvolvimento* - [desenvolvedor](https://github.com/mmstec)

Você também pode ver a lista de todos os [colaboradores](https://github.com/usuario/projeto/colaboradores) que participaram deste projeto.

## 🎁 Instituição de Ensino

* [UEFS - Universidade Estadual de Feira de Santana](https://www.uefs.br/) <br />
* [PGCC - Pós-Graduação em Ciências da Computação](https://pgcc.uefs.br/home) <br />
* UEFS - Computação de auto desempenho <br />
* PGCC011 - Computação de Alto Desempenho <br />
* Professor - [Angelo Amâncio Duarte](https://pgcc.uefs.br/sobre/docentes/angeloduarte) <br /> 

## 🚀 Citação

```
@MISC{contapalavras,
    author = {Luciano Junior, Marcos Morais},
    title = {{Contador de Frequencia de Palavras}},
    howpublished = "\url{https://github.com/mmstec/PGCC011/}",
    year = {2019},
  }
```
## 📄 Licença

Este projeto está sob a licença - veja o arquivo [LICENSE.md](https://github.com/mmstec/PGCC011/blob/main/LICENSE.md) para detalhes.

