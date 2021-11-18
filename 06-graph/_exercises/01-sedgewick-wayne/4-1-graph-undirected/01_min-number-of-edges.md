---
exercise: exercise-4.1.1
---

## 4.1.1

1. What is the maximum number of edges in a graph with V vertices and no parallel edges?

**R** 

Combinação 2 a 2 de V elementos, V sendo o número de vértices do grafo

E = V(V-1)/2

2. What is the minimum number of edges in a graph with V vertices, none of
which are isolated?

**R** 
### Par
Se V é par, basta formar duplas entre os vértices: Epar = V/2.

### Ímpar
Se V é ímpar e diferente de 1, basta formar um trio e formar duplas com o restante dos vértices. 

Um trio: E1 = 2

Duplas com o restante dos vértices: E2 = (V-3)/2

Eímpar = E1 + E2 = 2 + (V-3)/2

Eímpar = (V-1)/2

### Total
E = Eímpar + Epar

E = V-1