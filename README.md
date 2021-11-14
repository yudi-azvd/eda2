# Estruturas de Dados e Algoritmos 2 - FGA0030
Repositório para a disciplina de Estruturas de Dados e Algoritmos 2
da Universidade de Brasília.


## Links úteis
[Página de EDA2](https://www.brunoribas.com.br/eda2/2021-1/#org9410b9f)

[Progresso das aulas e exercícios](https://github.com/yudi-azvd/eda2/issues/1)


## Baixe o repositório
    git clone --recurse-submodules https://github.com/yudi-azvd/eda2

A flag `--recurse-submodules` serve para inicializar os submódulos de `eda2`.
Até o momento em que escrevo isso, os submódulos usados aqui estão em 
`.gitmodules`.


## Dados
Em `resources/` devem existir alguns dados para testes. Esses dados você pode 
baixar [aqui](https://algs4.cs.princeton.edu/code/algs4-data.zip). Esses dados
são do site/livro [Algorithms, 4th Edition](https://algs4.cs.princeton.edu/home/),
criado por uns professores da Universidade de Princeton (o livro no site é
mais resumido que o livro de verdade).

É possível também fazer os cursos Algorithms I e II de Princeton no Coursera.

## Scripts úteis
Gerar uma entrada aleatória

    for((i=0;i<100000;i++)); do echo $RANDOM; done > aleatorio.in


Frequência de valores em uma coluna

    awk -F '\t' '{print $2}' * | sort | uniq -c | sort -nr

`uniq` precisa que os elementos repetidos estejam adjacentes. `sort` resolve 
isso.

## Benchmarking
Para testar os benchmarks do professor:

    cd 01-sorting/becnhmark-ordenacao

Exemplo de benchmarking para dois algoritmos de ordenação (selection sort normal
e recursivo) com time out de 6 segundos.

    TIMEOUT=6 BINARY="selectionsort selectionsortR" make printorder time.aleatorio


[Vídeo com mais exemplos e explicações](https://www.youtube.com/watch?v=W8XcTiAPaew).


## Snippets
[VSCode docs](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_transform-examples)

```cpp
"Header guards": {
  "prefix": "header_guards",
  "body": [
    "#ifndef ${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_INCLUDED",
    "#define ${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_INCLUDED",
    "",
    "$0",
    "",
    "#endif // ${TM_FILENAME_BASE/(.*)/${1:/upcase}/}"
  ],
  "description": "Header guards template"
}
```
