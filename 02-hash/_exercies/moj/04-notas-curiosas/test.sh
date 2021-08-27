#!/bin/bash

# https://stackoverflow.com/questions/5947742/how-to-change-the-output-color-of-echo-in-linux
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

input_files=($(find in/*.in -type f))
expected_output_files=($(find out/*.out.exp -type f))

total_input_files=${#input_files[@]}

diff_results=()

# gcc placas.c -O2 -static -lm

for i in "${!input_files[@]}"; do
  number=$(echo ${input_files[i]} | cut -d '.' -f 1 | cut -d '/' -f 2)
  ./a.out < ${input_files[i]} > out/$number.out
  diff_result=$(diff -w ${expected_output_files[i]} out/$number.out)
  
  if [ -z "$diff_result" ]; then
    echo -e "$number.out ... ${GREEN}OK${NC}"
  else
    diff_results+=("$diff_result")
    echo -e "$number.out ... ${RED}FAIL${NC}"
  fi
done
