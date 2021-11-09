#ifndef CONVENTION_H_INCLUDED
#define CONVENTION_H_INCLUDED

typedef int Item;

#define Key(a) (a)

#define less(a, b) (Key(a) < Key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if (less(b, a)) exch(a, b); }

int issorted(Item* itens, int len) {
  int i=1; 
  for (; i < len; ++i)
    if (less(itens[i], itens[i-1]))
      return 0;
  return 1;
}

#endif