# Exercícios Hash

## 1. Veja o material sobre hash do Prof. Paulo Feofiloff

## 2. Você consegue aplicar as ideias de HASH nos exercícios Remoção e Sanidade?

## 3. Você consegue aplicar as ideias de HASH no exercício Eleição U.R.S.A.L?

## 4. Considere as técnicas de busca sequencial, busca binária e busca baseada em hashing:
Descreva as vantagens e desvantagens de cada uma dessas técnicas, indicando em que situações você usaria cada uma delas.
Qual é a eficiência de utilização da memória (relação entre o espaço necessário para dados e o espeço total necessário) para cada método?

## 5. Sobre Tabelas HASH:
**É possível criar uma função HASH em que é garantido que nunca haverá colisão? Porquê?** 

_R_: Sim. Se o número de chaves distintas for menor que o número de espaços
para itens da tabela. Usando a seguinte operação $ch \% 100$, ou seja, não haverá
colisão se $R < M$, sendo $R$ o universo de chaves e $M$ o tamanho do vetor.

**Quando existe colisão, quais estratégias podem ser utilizadas para contornar esse problema? Quando cada estratégia é melhor utilizada?**

_R_

- sondagem linear: quando há colisão, procurar à direita da posição por uma posição
com vaga.
- lista encadeada: um vetor de listas ligadas. Colisões mapeiam elementos para 
mesma posição do vetor. Esse elementos devem ser adicionados ao final de uma lista
encadeada.


## 6. Resolva os exerícios DESTA PROVA   
[Prova](https://www.brunoribas.com.br/aed1/provas/3/2018-2.pdf)
