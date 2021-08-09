# Casos de teste
Os casos abaixo descrevem a lista encadeada da direita para 
esquerda. Cada coluna é um nó. Cada linha representa os dados
do nó:

    [next]
    [prev]
    [addr]

Os números na primeira linha, 1 e 2, necessariamente, idicam
as posições dos ponteiros `ptr1` e `ptr2`, respectivamente.


## `sanidade-1.in`
O nó campo `next` de `c` aponta de volta para `b`. Loop de `ptr1` 
para `ptr1`.

    1         2
    b c d e f 0
    0 a b c d e
    a b c d e f
    
`sana`


## `sanidade-4.in`
O nó campo `next` de `c` aponta de volta para `b`. Loop de `ptr1` 
para `ptr1`.

      1   2
    b c b e 0
    0 a b c d
    a b c d e 
    
`insano`


## `sanidade-5.in`

      1    2
    b c ff e 0
    0 a b  c d
    a b c  d e 
`insano`
    

## `sanidade-6.in`
`ptr2` toma atalho pra `ptr1`, fazendo um caminho mais curto.

      1    2
    b c ff e 0
    0 a b  c d
    a b c  d e 
`insano`


## `sanidade-8.in`
3 nós de ptr1 para ptr2. 3 nós de `ptr2` para `ptr1` também, 
mas por um caminho difente.
      
      1   2
    f a e d 0
    0 d f a e
    d f a e c

`insano`