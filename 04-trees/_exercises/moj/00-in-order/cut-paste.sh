#!/usr/bin/bash

# Copia tudo entre "start-copy" e "end-copy" de in-order.c
# | remove a primeira e última linha
# > "cola" em in-order.submit.c
sed -n '/start-copy/,/end-copy/p' in-order.c | sed '1d;$d' > in-order.submit.c
