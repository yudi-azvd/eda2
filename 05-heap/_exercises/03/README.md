# Questão 3
(SW 9.17) Um vetor em ordem decrescente é um heap decrescente? Um vetor em 
ordem crescente é um heap crescente?   

**R**
Sim para os dois.

| estrutura | condição |
|-----------|----------|
| vetor em ordem decrescente | `v[i-1] > v[i]` |
| heap decrescente | `v[i] > v[i*2] && v[i] > v[i*2+1]` |