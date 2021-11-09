# Ordenação com Heap

**R1** 
```
 v: vetor desordenado
pq: fila de prioridade vazia

for i in v:
  pq.insert(i)

for i in range(0, v.length): // [0, v.length-1]
  v[i] = pq.del_max()

v está ordenado em ordem decrescente  
```

Custo $N + N\log_2N$
- $N$ para inserir o vetor na fila
- $N \log_2 N$ para cada remoção


**R2**  Nesse
[link](https://github.com/bcribas/benchmark-ordenacao/blob/master/heapsort.c).
Mas ainda não entendi bem como funciona.