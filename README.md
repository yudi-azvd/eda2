# Estruturas de Dados e Algoritmos 2
Repositório para a disciplina de Estruturas de Dados e Algoritmos 2 (FGA0030)
da Universidade de Brasília.


## Links úteis
[Página de EDA2](https://www.brunoribas.com.br/eda2/2021-1/#org9410b9f)

[Progresso das aulas e exercícios](https://github.com/yudi-azvd/eda2/issues/1)

### Livro
Usado por mim: [Algorithms, 4th Edition](https://algs4.cs.princeton.edu/home/).

Solução de alguns exercícios: [lá embaixo](https://algs4.cs.princeton.edu/code/).


## Baixe o repositório
    git clone --recurse-submodules https://github.com/yudi-azvd/eda2

A flag `--recurse-submodules` serve para inicializar os submódulos de `eda2`.
Até o momento em que escrevo isso, os submódulos usados aqui estão em 
`.gitmodules`.

## Verificação automática com scripts de teste
Tanto o script `test.py` quanto o `test.sh` assumem algumas coisas:

- Existe um `a.out` no mesmo diretório, é o programa que vai ser testado
- Existe um subdiretório `samples/` com os arquivos dos casos de teste 
seguindo a seguinte organização:
    - `xx.in`: o arquivo de entrada
    - `xx.out.exp` o arquivo de saída esperada (é a resposta correta ou gabarito)

Você só precisa de um deles pra executar os testes automáticos. Vamos supor
que o escolhido é o `test.sh`.

Copie o script para o diretório onde o executável vai ser gerado e onde
vai ficar o subdiretório `samples/`. Deve ficar algo assim:

```
diretorio-do-exercicio/
├── samples/
│   ├── 00.in
│   ├── 00.out.exp
│   ├── 01.in
│   └── 01.out.exp
├── a.out
├── programa.c
└── test.sh
```

Certifique-se que o script tem permissão para execução. Se não tem, execute:

```sh
chmod +x test.sh
```

Rode os testes com 

```sh
./test.sh
```

Se o seu programa está correto de acordo com os casos de teste, você deve ver algo assim:

```
⌚ time taken 0,006s
⌚ time taken 0,001s
⌚ time taken 0,003s
⌚ time taken 0,001s
====================================
SUCCESS:
tests passed: 4/4
====================================
```

### Rastreio do Git
Se você executa esses testes em um repositório Git e não quer poluir o rastreio seguindo a estrutura recomendada, inclua o seguinte no seu `.gitignore`:

```sh
!*.out.exp
**/test.py
**/test.sh
!/test.py
!/test.sh
```

Assim, o Git vai ignorar todos os scripts de testes que não estiverem na raíz do repositório. Preferi assim porque eu podia modificar o script na raíz e copiá-lo pra onde eu quisesse sem 
o Git acusar mudanças desnecessárias.


## Dados
Em `resources/` devem existir alguns dados para testes. Esses dados você pode 
baixar [aqui](https://algs4.cs.princeton.edu/code/algs4-data.zip). Esses dados
são do site/livro [Algorithms, 4th Edition](https://algs4.cs.princeton.edu/home/),
criado por uns professores da Universidade de Princeton (o livro no site é
mais resumido que o livro de verdade).

É possível também fazer os cursos Algorithms I e II de Princeton no Coursera.

## Scripts úteis
Gerar uma entrada aleatória

    for((i=0;i<100000;i++)); do echo $RANDOM; done > aleatorio.in


Frequência de valores em uma coluna

    awk -F '\t' '{print $2}' * | sort | uniq -c | sort -nr

`uniq` precisa que os elementos repetidos estejam adjacentes. `sort` resolve 
isso.

Remover executáveis e resultados de executáveis (`samples/*.out`). Na raíz do 
repositório:

    find . -type f -name '*.out' -delete



## Benchmarking
Para testar os benchmarks do professor:

    cd 01-sorting/becnhmark-ordenacao

Exemplo de benchmarking para dois algoritmos de ordenação (selection sort normal
e recursivo) com time out de 6 segundos.

    TIMEOUT=6 BINARY="selectionsort selectionsortR" make printorder time.aleatorio


[Vídeo com mais exemplos e explicações](https://www.youtube.com/watch?v=W8XcTiAPaew).


## Snippets
[VSCode docs](https://code.visualstudio.com/docs/editor/userdefinedsnippets#_transform-examples)

```cpp
"Header guards": {
  "prefix": "header_guards",
  "body": [
    "#ifndef ${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_INCLUDED",
    "#define ${TM_FILENAME_BASE/(.*)/${1:/upcase}/}_H_INCLUDED",
    "",
    "$0",
    "",
    "#endif // ${TM_FILENAME_BASE/(.*)/${1:/upcase}/}"
  ],
  "description": "Header guards template"
}
```
