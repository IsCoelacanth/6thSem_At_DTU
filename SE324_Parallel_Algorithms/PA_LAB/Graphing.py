import time
import matplotlib.pyplot as plt
# from Lab_2_matmult import *
# from Lab_3_MatVec import *
import numpy as np
import random
from Lab_3 import *

def MeasureMatMul():
    dim = []
    tim = []

    for i in range (2,25):
        A = Lab_2_matmult.GetMatrix(i,i)
        B = Lab_2_matmult.GetMatrix(i,i)
        t1 = time.time()
        tmp = Lab_2_matmult.Multiply(A,B)
        t2 = time.time()
        dim.append(i)
        tim.append(t2-t1)

    plt.plot(dim,tim, label = "matmul")
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Complexity of N3 matrix multiplication")
    plt.legend()
    plt.show()

# MeasureMatMul()

def minmaxscale(m):
    mn = min(m)
    mx = max(m)
    mnmx = mx-mn
    for i in range(len(m)):
        m[i] = (m[i]-mn)/mnmx
    return m

def MeasureMatVec():
    dim = []
    tim = []

    for i in range (2,50):
        A = GetMatrix(i,i)
        # print(A)
        B = GetVector(i)
        # print(B)
        res = []
        for i in range(len(A)):
            res.append(0)
        t1 = time.time()
        for i in range(len(A)):
            res[i] = 0
            for j in range(len(B)):
                res[i] += A[i][j]*B[j]
        
        # tmp = Multiply(A,B)
        # print(tmp)
        t2 = time.time()
        dim.append(i)
        tim.append(t2-t1)
    # dim = minmaxscale(dim)
    tim = minmaxscale(tim)
    fit = np.polyfit(dim,tim,deg=2)
    p = np.poly1d(fit)
    plt.scatter(dim,tim)
    plt.plot(dim,p(dim), label = "Mat-Vec", color='red')
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Complexity of Standard matrix-vector multiplication")
    plt.legend()
    plt.show()
# MeasureMatVec()

def GraphL3():
    s_x = []
    s_y = []
    p_x = []
    p_y = []
    for i in range(100,100000,100):
        arr = random.sample(range(100000),i)
        start = time.time()
        arr_sorted = merge_sort(arr)
        end = time.time() - start
        s_x.append(i)
        s_y.append(end)

        start = time.time()
        arr_sorted = paraller_merge_sort(arr)
        end = time.time() - start
        p_x.append(i)
        p_y.append(end)
    
    plt.plot(s_x,s_y, label="Serial Merge sort", color = red)
    plt.plot(p_x,p_y, label="Parallel Merge sort")
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Comparision on parallel and serial merge sort")
    plt.legend()
    plt.show()

GraphL3()


        