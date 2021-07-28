## Questão 9 - Ordenando um registro
Suponha que cada elemento de um vetor é um registro com dois campos, um inteiro 
e outro uma string:

    struct registro { int aa; char *bb; };

Escreva uma função que rearranje o vetor de modo que os campos `aa` fiquem em 
ordem crescente. Escreva outra função que rearranje o vetor de modo que os 
campos `bb` fiquem em ordem lexicográfica.

### Resposta
[Código](./sort-custom-struct.c).

`record_t` é o equivalente a `registro`.

Para executar:

    cd sorting ; gcc sort-custom-struct.c
    ./a.out < ../revisao/reprovado-1.in 


### Nota sobre `qsort`
[Estabilizando `qsort`](https://nullprogram.com/blog/2014/08/29/#:~:text=Since%20quicksort%20is%20an%20unstable,has%20no%20stable%20sort%20function.).