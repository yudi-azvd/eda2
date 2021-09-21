#!/usr/bin/bash

# Copia tudo entre "start-copy" e "end-copy" de pre-order.c
# | remove a primeira e última linha
# > "cola" em pre-order.submit.c
sed -n '/start-copy/,/end-copy/p' pre-order.c | sed '1d;$d' > pre-order.submit.c
