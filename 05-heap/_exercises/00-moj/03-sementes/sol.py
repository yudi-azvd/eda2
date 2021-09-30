#!/usr/bin/python3

from typing import List
from functools import cmp_to_key



class Seed:
  def __init__(self, code, score) -> None:
    self.code = code
    self.score = score
    return
  
  def __repr__(self):
    return f'{self.code} {self.score}'
  
  def __le__(self):
    return


def cmp_by_code(a: Seed, b: Seed):
  return a.code - b.code

def cmp_by_score(a: Seed, b: Seed):
  if a.score == b.score:
    return a.code - b.code
  return a.score - b.score

# filename = 'samples/016-bin-rev-bigreturn.in'
filename = 'non-exsite'
file = open(filename, 'r')
how_many_seeds = int(file.readline())
seeds: List[Seed] = []

for line in file:
  code, score = line.strip().split()
  seeds.append(Seed(int(code), int(score)))


# https://stackoverflow.com/questions/5213033/sort-a-list-of-lists-with-a-custom-compare-function
seeds = sorted(seeds, key=cmp_to_key(cmp_by_score))
seeds = seeds[0:how_many_seeds]
seeds = sorted(seeds, key=cmp_to_key(cmp_by_code))

print('\n'.join([str(s) for s in seeds]))