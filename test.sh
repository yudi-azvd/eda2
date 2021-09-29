#!/bin/bash

<<comment
Você pode executar esse script com:

watch -n 0.5 --color -t  ./test.sh 

Esse comando executa o script test.sh
a cada 0.5 segundo, colorido e sem o 
título. *Evite usar watch para programas
com algoritmos muito demorados*.


# Pra deixar esse script ainda mais top:
## Rodar script quando o binário mudar
- https://superuser.com/questions/181517/how-to-execute-a-command-whenever-a-file-changes
- https://github.com/inotify-tools/inotify-tools/wikihttps://github.com/inotify-tools/inotify-tools/wiki

## Medir tempo com redirecionamento
- https://unix.stackexchange.com/questions/12068/how-to-measure-time-of-program-execution-and-store-that-inside-a-variable

## Medir apenas o tempo real
TIMEFORMAT=%R
unset TIMEFORMAT # pra voltar ao normal
comment


# https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color

BOLD_FMT=$(tput bold)
NORMAL_FMT=$(tput sgr0)

input_files=($(find samples/*.in -type f))
expected_output_files=($(find samples/*.out.exp -type f))

total_input_files=${#input_files[@]}

diff_results=()
correct_count=0
fail_count=0
declare -A failed_tests

TIMEFORMAT=%R # Para pegar apenas o tempo real do comando `time`
for i in "${!input_files[@]}"; do
  number=$(echo ${input_files[i]} | cut -d '.' -f 1 | cut -d '/' -f 2)
  ./a.out < ${input_files[i]} > samples/$number.out
  time_taken="$(time (./a.out < ${input_files[i]} > samples/$number.out) 2>&1 1>/dev/null)"
  echo "⌚ time taken ${time_taken}s"
  diff_result=$(diff -w --suppress-common-lines --color=always samples/$number.out ${expected_output_files[i]})
  
  if [ -z "$diff_result" ]; then
    ((correct_count++))
  else
    failed_tests["${input_files[i]}"]=$(echo -e "$diff_result" | tail -n +2)
    ((fail_count++))
  fi
done
unset TIMEFORMAT

for failed_key in "${!failed_tests[@]}"; do 
  echo -e "${YELLOW}${BOLD_FMT}====================================${NORMAL_FMT}"
  echo -e "${YELLOW}diff for test case ${BOLD_FMT}$failed_key${NORMAL_FMT}:${NC}"
  echo -e "${failed_tests[$failed_key]}\n"
done

RESULT_COLOR=""

if [[ "$fail_count" -eq 0 ]] ; then
  RESULT_COLOR=${GREEN}
else
  RESULT_COLOR=${RED}
fi

echo -e "${RESULT_COLOR}===================================="
if [[ "$fail_count" -eq 0 ]] ; then
  echo -e "SUCCESS:"
else
  echo -e "FAIL:"
fi
echo -e "tests passed: $correct_count/$total_input_files"
echo -e "====================================${NC}"
