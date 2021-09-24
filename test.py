#!/usr/bin/python3

import os
import glob
import time

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
NC='\033[0m' # No Color
FMT_BOLD='\033[1m'

class TestCase:
  def __init__(self):
    self.input_file = ''
    self.sucess = False
    self.time_duration = 0
    self.diff_result = ''

def main():
  input_files = sorted([f for f in glob.glob('samples/*.in')])
  total_test_cases = len(input_files)
  expected_output_files = sorted([f for f in glob.glob('samples/*.out.exp')])
  test_cases: list[TestCase] = []
  correct_test_cases_count = 0
  all_success = True

  for i, input_file in enumerate(input_files):
    test_case = TestCase()
    filename, _ = os.path.splitext(input_file)
    output_file = f'{filename}.out'

    start_time = time.perf_counter()
    os.system(f'./a.out < {input_file} > {output_file}')
    end_time = time.perf_counter()
    
    test_case.time_duration = end_time - start_time

    diff_exit_status = os.system(f'diff -aw --color=always {output_file} {expected_output_files[i]} > diff.tmp')

    test_case.input_file = input_file
    diff_file = open('diff.tmp', 'r')
    # test_case.diff_result = ''.join(diff_file.readlines()[1:]) # remover a primeira linha
    test_case.diff_result = diff_file.read()
    diff_file.close()
    
    if os.WIFEXITED(diff_exit_status):
      exit_code = os.WEXITSTATUS(diff_exit_status)
      if exit_code == 0:
        correct_test_cases_count += 1
        test_case.sucess = True
      else:
        test_case.sucess = False
        all_success = False

    test_cases.append(test_case)
  
  test_suite_result = ''
  RESULT_COLOR = ''
  sucessed_tc = [tc for tc in test_cases if tc.sucess]
  failed_tc = [tc for tc in test_cases if not tc.sucess]

  for stc in sucessed_tc:
    print(f'{stc.time_duration:7.4f}s | {GREEN}OK{NC} {stc.input_file}')
  print()

  for ftc in failed_tc:
    print(f'{FMT_BOLD}{YELLOW}========================{NC}')
    print(f'{ftc.time_duration:7.4f}s {YELLOW}diff for test case {FMT_BOLD}{ftc.input_file}{NC}')
    print(f'{ftc.diff_result}')

  if all_success:
    RESULT_COLOR = GREEN
    test_suite_result = 'SUCCESS'
  else:
    test_suite_result = 'FAIL'
    RESULT_COLOR = RED


  print(f'\n{RESULT_COLOR}=================================')
  print(f'{test_suite_result}')
  print(f'tests passed {correct_test_cases_count}/{total_test_cases} {correct_test_cases_count/total_test_cases*100:.1f}%')
  print(f'=================================')
  return

if __name__ == '__main__':
  main()
        


