---
exercise: exercise-4.1.2
---

Draw, in the style of the figure in the text (page 524), the adjacency lists 
built by Graph’s input stream constructor for the file `tinyGex2.txt` depicted at 
left. 

```
tinyGex2.txt:
12
16
 8 4
 2 3
 1 11
 0 6
 3 6
10 3
 7 11
 7 8
11 8
 2 0
 6 2
 5 2
 5 10
 3 10
 8 1
 4 1
```

**R**
```
 0: 6 2
 1: 11 8 4
 2: 3 0 6 5 10
 3: 2 6 10
 4: 8 1
 5: 2 10
 6: 0 3 2
 7: 11 8
 8: 4 7 11 1
 9: 
10: 3 5
11: 1 7 8
```