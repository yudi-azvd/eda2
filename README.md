# Estruturas de Dados e Algoritmos 2
Repositório para a disciplina de Estruturas de Dados e Algoritmos 2
da Universidade de Brasília.


## Links úteis
[Página de EDA2](https://www.brunoribas.com.br/eda2/2021-1/#org9410b9f)


## Scripts úteis
Gerar uma entrada aleatória

    for((i=0;i<100000;i++)); do echo $RANDOM; done > aleatorio.in


Frequência de valores em uma coluna

    awk -F '\t' '{print $2}' * | sort | uniq -c | sort -nr

`uniq` precisa que os elementos repetidos estejam adjacentes. `sort` resolve 
isso.
