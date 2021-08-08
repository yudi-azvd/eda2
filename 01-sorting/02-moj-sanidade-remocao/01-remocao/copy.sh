#!/usr/bin/bash

# O primeiro sed complicado que parece um programa:
# https://stackoverflow.com/questions/5071901/removing-lines-between-two-patterns-not-inclusive-with-sed

# Cria backup
cp remocao.c remocao.bak

# Remove tudo o que vem antes de "start-insertion" e tudo depois de "end-insertion"
sed -i -n '/start-insertion/{p; :a; N; /end-insertion/!ba; s/.*\n//}; p' remocao.c

# Copia tudo entre "start-copy" e "end-copy" de linkedlist.h
# | remove a primeira e última linha
# > "cola" em ll.tmp
sed -n '/^\/\/ start-copy/,/end-copy/p' linkedlist.h | sed '1d;$d' > ll.tmp

# Insere o conteúdo de ll.tmp depois de "start-insertion" em remocao.c
sed -i -e '/^\/\/ start-insertion/r ll.tmp' remocao.c

