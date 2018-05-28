# AIM: To implement and analyze parallel quick sort 

## Introduction and theory

### Quicksort

Quicksort is a sorting algorithm whose worst-case running time is ![img](http://staff.ustc.edu.cn/~csli/graduate/algorithms/images/bound.gif)(*n*2) on an input array of *n* numbers. In spite of this slow worst-case running time, quicksort is often the best practical choice for sorting because it is remarkably efficient on the average: its expected running time is ![img](http://staff.ustc.edu.cn/~csli/graduate/algorithms/images/bound.gif)(*n* lg *n*), and the constant factors hidden in the ![img](http://staff.ustc.edu.cn/~csli/graduate/algorithms/images/bound.gif)(*n* lg *n*) notation are quite small. It also has the advantage of sorting in place (see page 3), and it works well even in virtual memory environments.

Quicksort, like merge sort, applies the divide-and-conquer paradigm. It has a three step process

**Divide: **The array *A*[*p . . r*\] is partitioned (rearranged) into two nonempty subarrays *A*[*p . . q*] and *A*[*q* + 1 . . *r*] such that each element of *A*[*p . . q*] is less than or equal to each element of *A*[*q* + 1 . . *r*]. The index *q* is computed as part of this partitioning procedure.

**Conquer: **The two subarrays *A*[*p . . q*\] and *A*[*q* + 1 . . *r*] are sorted by recursive calls to quicksort.

**Combine: **Since the subarrays are sorted in place, no work is needed to combine them: the entire array *A*[*p . . r*\] is now sorted.

### Parallel Quicksort

The parallel quick sort algorithm works by parallelizing the divide, and the partitioning steps. this makes the O(n) partition time an O(1) operation. The resulting algorithm is then O(logn).

The pivot selection is left to be something *unintuitive* because the creation and propagation of a random key would add a-lot of time overhead to the parallel algorithm.

## Algorithm

```python
QUICKSORT(A; p; r)
    1 if p < r
    2 q = PARTITION(A; p; r)
    3 QUICKSORT(A; p; q - 1)
    4 QUICKSORT(A; q + 1; r)
```

```
PARTITION(A; p; r)
  1 x = A[r]
  2 i =  p - 1
  3 for j = p to r - 1
    4 if A[j] <= x
      5 i = i + 1
      6 exchange A[i] with A[j]
    7 exchange A[i + 1] with A[r]
  8 return i + 1
```



Complexity: There is only cost i.e the data propagation  O(logn).

## Code

```python
import threading as th
import time
import matplotlib.pyplot as plt
import numpy as np
from util import getarr
import random

def partition(arr, low, high):
    i = low - 1
    piv = arr[high]
    for j in range(low, high):
        if arr[j] <= piv:
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1], arr[high] = arr[high], arr[i+1]
    return i+1

def quicksort(arr, low, high, mode='s'):
    if mode == 's':
        if low < high:
            pi = partition(arr, low, high)
            quicksort(arr, low, pi-1)
            quicksort(arr, pi+1, high)
    elif mode == 'p':
        if low < high:
            pi = partition(arr, low, high)
            p1 = th.Thread(target=quicksort, args=(arr,low,pi-1, 'p'))
            p2 = th.Thread(target=quicksort, args=(arr, pi+1, high, 'p'))

            p1.start()
            p2.start()
            p1.join()
            p2.join()

def main():
    z = int(input("Enter the data size : "))
    arr = getarr(z)
    print(arr)
    x = arr.copy()
    quicksort(x,0,len(x)-1)
    print("Sorted using serial quicksort : ")
    print(x)
    y = arr.copy()
    st = time.time()
    quicksort(y, 0, len(y)-1, 'p')
    print("Sorted using parallel quicksort : ")
    print(y, (time.time() - st)/mx_th)    
if __name__ == '__main__':
    main()
            
```



## Output

![output](../OutPuts/send_parallel_qs_out.png)

## Findings and Learnings

1. The parallel quicksort algorithm works efficiently for very large inputs.
2. There is direct relation between the number of processors and the speedup.
3. Using a random pivot adds additional overhead and makes the parallel approach unfavorable.

