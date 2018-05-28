# AIM: To implement and analyze serial Matrix-Vector multiplication 

## Introduction and theory

The task of matrix-vector multiplication is widely used in the field of computer science especially in the field of scientific computing. It is also used in cognitive tasks like those in machine learning and other AI activities .Thus the need of an efficient algorithm to multiply matrices and Vectors is essential. The standard serial algorithm is O(n2) w.r.t to the input and this is also the best possible time for serial implementations.

The task is as follows:

![task](../OutPuts/mtvc.PNG)

This can be parallelized using the SIMD Linear array approach, where there are M processors arranged as a linear array. Each item takes O(m+n-1) steps to reach the last node. This is the most cost optimal approach possible.

the arrangement of processors is:

![array](../OutPuts/array.PNG)

## Algorithm

```python
def Mat_Vec(M[m][n],v[n]):
1.	for i in to m do in parallel:
2.		out [i] = 0
3.		while Pi has 2 inputs a, b do
4.			out[i] += a * b
5. 			if i > 1 send u to Pi-1
6.	return res
```

Complexity: There is only 1 for loop thus O(n) for square matrix.

## Code

```python
import multiprocessing as mp
import threading as th
from util import GetMatrix, GetVector, MinMaxScale, mat_print
import time
from Lab_3_MatVec import Multiply
import matplotlib.pyplot as plt
import numpy as np

def mult(A, u, V, idx):
    sum = 0
    for i in range(len(u)):
        sum += A[i]*u[i]
    V[idx] = sum
def main():
    st = int(input("Enter the starting size : "))
    ed = int(input("Enter the endibg size : "))
    s_x = []
    s_y = []
    p_x = []
    p_y = []

    for z in range(st,ed):
        A = GetMatrix(z)
        u = GetVector(z)
        V = []
        print("Generated Matrix A")
        mat_print(A)
        print("Generated vector u")
        mat_print(u)
        s = time.time()
        C = Multiply(A,u)
        e = time.time()
        print("Result Vector V using serial multiplication")
        mat_print(C)
        s_x.append(z)
        s_y.append(e-s)

        Proc = []
        jobs = []
        V = []
        
        for i in range(z):
            V.append(0)
            thread = th.Thread(target=mult, args=(A[i],u, V, i))
            jobs.append(thread)
        s = time.time()
        for i in jobs:
            i.start()
        for i in jobs:
            i.join()
        e = time.time()
        p_x.append(z)
        p_y.append((e-s)/z)
        print("Result Matrix C using Mesh Multiplication")
        mat_print(V)
        
    # plt.plot(s_x,s_y, label="Serial Matrix Mult", color = 'red')
    s_fit = np.polyfit(s_x, s_y,deg=2)
    s_p = np.poly1d(s_fit)
    plt.plot(s_x,s_p(s_x), color = 'red', label="Serial Matrix Mult")
    p_fit = np.polyfit(p_x, p_y,deg=2)
    p_p = np.poly1d(p_fit)
    # plt.plot(p_x,p_y, label="Parallel Matrix Vector Mult", color = 'blue')
    plt.plot(p_x,p_p(p_x), color = 'blue', label="Parallel Matrix Vector Mult" )
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Comparision on parallel and serial matrix-vector mult")
    plt.legend()
    plt.show()
    s_up = [s_y[i]/p_y[i] for i in range(len(s_x))]
    s_fit = np.polyfit(s_x, s_up,deg=2)
    s_p = np.poly1d(s_fit)
    plt.plot(s_x, s_p(s_x), label="speed up")
    plt.legend()
    plt.show()

if __name__ == '__main__':
    main()
            
```



## Output

![output](../OutPuts/lineararray.png)

## Discussion

From the below graph we can see the algorithm indeed follows a N growth in time. and thus there is scope for parallelization to improve efficiency and run time.

![graph](../OutPuts/linarray.png)

and the speed up observed is:

![graph](../OutPuts/LinArrGraph.png)

## Findings and Learnings

1. The Matrix-Vector multiplication algorithm is a N2 algorithm w.r.t input size.
2. For the matrices and vectors to be multipliable their columns and rows need to be of same dimension.
3. for small inputs the serial implementation performs better due to the overheads of creating and assigning data to processes.

