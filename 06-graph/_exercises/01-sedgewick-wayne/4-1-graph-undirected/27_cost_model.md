---
exercise: exercise-4.1.27
---

## 4.1.27

**R** 

### Integer
```
overhead: 16 bytes
 padding: 4 bytes
     int: 4 bytes
   TOTAL: 24 bytes
```

### Node (Bag)
```
overhead: 16 + 8 bytes // 8 extra para classe pai
    Item: 8 bytes
    next: 8 bytes
   TOTAL: 40 bytes
```

### Bag
```
(N: número de nós na Bag)
overhead: 16 bytes
 padding: 4 bytes
    Node: 40N
   first: 8 bytes
       n: 4 bytes
 Integer: 24N
   TOTAL: 16 + 4 + 40N + 8 + 4 + 24N
        : 32 + 64N bytes
```

### Graph
```
overhead: 16 bytes
 padding: 4 bytes
       V: 4 bytes
       E: 4 bytes
     adj: 8V bytes // V referências pra Bag
   adj[]: 
    Bag overhead: 16 bytes
     Bag padding: 4 bytes
     ?????

conteúdo de cada Bag

TOTAL: ?
```

Fonte:
[https://github.com/reneargento/algorithms-sedgewick-wayne/blob/master/src/chapter4/section1/Exercise27.txt](https://github.com/reneargento/algorithms-sedgewick-wayne/blob/master/src/chapter4/section1/Exercise27.txt)