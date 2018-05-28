# AIM: To implement SIMD Matrix-Matrix multiplication using Hypercube architecture

## Introduction and Theory

Matrix-Matrix Multiplication can be parallelized using the hypercube architecture of SIMD models. This uses N3 processors where N is the input size of the two matrices. These are arranged into a 2(q) dimensional cube of processors. All of these are equidistant from each other to minimize the propagation losses.

The arrangement of the processors are as follows:

![arc](../OutPuts/cube.PNG)

This method has 3 steps:

1. distribute the data to all the n**3 processors, this takes log(n) time.
2. perform multiplication of the two numbers in each processor, this is a constant time operation.
3. Add up all the matrixes in the cubes to get the final Matrix, depending upon the implementation this can take O(n) or O(log(n)) time.

Thus theoretically the hypercube approach is the not most cost optimal and best possible method.

## Algorithm

```python
1. def CubeMMM(A, B, C):
2. 		Distribute A, B to n3 processors such that A(i,j,k) = ajk and B(i,j,k) = bik
3. 		Compute the products C(i,j,k) = A(i,j,k) * B(i,j,k)
4. 		The sums i=0simn-1 (C(i,j,k)).
    
```

## Code

```python
import threading as th
from util import GetMatrix, mat_print, MinMaxScale
import time
import matplotlib.pyplot as plt
import numpy as np
from Lab_2_matmult import Multiply

def mult(A, B, C, i, j, k):
    C[i][j][k] = A*B
    pass
def main():
    z = int(input("Enter the input size : ")
    A = GetMatrix(z)
    B = GetMatrix(z)
    V = []
    print("Generated Matrix A")
    mat_print(A)
    print("Generated Matrix V")
    mat_print(B)
    C = Multiply(A,B)       
    print ('Result using n3 algorithm')
    mat_print(C)
    C_p = [[[0 for i in range(z)]for j in range(z)] for k in range(z)]
    nproc = z**3
    procs = []
    for i in range(z):
        tprocs = []
        for j in range(z):
            tt_proc = []
            for k in range(z):
                tt_proc.append(th.Thread(target=mult, args = (A[j][i], B[i][k], C_p, i, j, k)))
                # print ('C[{}][{}][{}] = {}, {}'.format(i, j , k, A[j][i], B[i][k]), end = ' ')
            tprocs.append(tt_proc)
            # print()
        procs.append(tprocs)

    for _2 in procs:
        for _1 in _2:
            for i in _1:
                i.start()
    for _2 in procs:
        for _1 in _2:
            for i in _1:
                i.join()
    # Mult step done:
    C = [[0 for i in range(z)] for i in range(z)]
    for i in range(z):
        for j in range(z):
            # print('C[{}][{}] = sum('.format(i, j), end = ' ')
            for k in range(z):
                C[j][i] += C_p[k][j][i]
            #     print(C_p[k][j][i], end = ' ')
            # print()
    print ('Result using cube algorithm')
    mat_print(C)
                    

main()
```

## Output

![output](../OutPuts/mmc_out.png)

## Findings and learnings 

1. The parallel methods shows better performance at very high order of input
2. The initial overhead of process allocation and scheduling makes it impractical for small inputs
3. After n=10 the growth of parallel method is nearly constant which is expected.