# O HeapSort é estável?

**R** Não

```c
void pqsortsimple(int *v, int l, int r) {
  int k;
  PQinit((r-l+1));

  for(k = l; k <= r; k++)
    PQinsert(v[k]);
  for(k= r; k>= l; k--) 
    v[k]=PQdelmax();
}
```

```c
void heapsort(int *v, int l, int r) {
  int k,N=r-l+1;
  Item *pq= v+l-1;

  for(k = N/2; k>= 1;k--)
    fixDown(pq,k,N);
  while(N>1)
  {
    exch(pq[1],pq[N]);
    fixDown(pq,1,--N);
  }
}
```