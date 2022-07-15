from typing import List


class BubbleSorter:
  inversions_at_iteration: List[int] = []
  
  def run(l: List[int]):
    return
  
  def report(self):
    result = ''
    for i, inversion in enumerate(self.inversions_at_iteration):
      result += f'Inversions at [{i}]: {inversion}'
    return result
  

if __name__ == '__main__':
  sorter = BubbleSorter()
  array = [2, 3, 4, 1, -5, 10]
  print(sorter.run(array))