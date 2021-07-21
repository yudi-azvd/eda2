#ifndef CONVENTION_H_INCLUDED
#define CONVENTION_H_INCLUDED

typedef int Item;

#define Key(a) (a)

#define less(a, b) (Key(a) < Key(b))

#define exch(a, b) { Item t = a; a = b; b = t; }

#define cmpexch(a, b) { if (less(a, b)) exch(a, b); }


#endif