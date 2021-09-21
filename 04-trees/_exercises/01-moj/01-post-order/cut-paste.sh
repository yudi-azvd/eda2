#!/usr/bin/bash

# Copia tudo entre "start-copy" e "end-copy" de post-order.c
# | remove a primeira e última linha
# > "cola" em post-order.submit.c
sed -n '/start-copy/,/end-copy/p' post-order.c | sed '1d;$d' > post-order.submit.c
