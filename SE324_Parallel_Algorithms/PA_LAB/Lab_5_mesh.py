# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import multiprocessing
import matplotlib.pyplot as plt
from util import GetMatrix
from Lab_2_matmult import Multiply
import time
def multiply(A, B,r_in, c_in, C):
    sum = 0
    for i in range(len(A)):
        sum += A[i] * B[i]
    C[c_in] = sum

def get_column(A, col_index):
    ans = []
    rows = len(A)
    for i in range(rows):
        ans.append(A[i][col_index])
    return ans


if __name__ == '__main__':
    
    st = int(input("Enter the starting size : "))
    ed = int(input("Enter the endibg size : "))
    s_x = []
    s_y = []
    p_x = []
    p_y = []
    for z in range(st, ed):
        
        A = GetMatrix(z)
        B = GetMatrix(z)
        C = []
        #Serial multiplication
        print("Generated Matrix A")
        for i in A:
            print(i)
        print("Generated Matrix B")
        for i in B:
            print(i)
        s = time.time()
        C = Multiply(A,B)
        e = time.time()
        print("Result Matrix C using serial multiplication")
        for i in C:
            print(i)
        s_x.append(z)
        s_y.append(e-s)
        
        # Parallel
        processes = []
        res = []
        output = []
        s  = time.time()
        for i in range(z):
            output.append([])
            processes.append([])
            res.append(multiprocessing.Array('i', z))
            for j in range(z):
                output.append(0)
                processes[i].append(
                    multiprocessing.Process(target=multiply, args=(A[i], get_column(B, j), i, j, res[i])))
                processes[i][j].start()

        for i in range(len(processes)):
            for j in range(len(processes[i])):
                processes[i][j].join()
        e = time.time()
        print("Result Matrix C using Mesh Multiplication")
        for i in res:
            print(i[:])
        p_x.append(z)
        p_y.append(e-s)

    for i in range(len(p_y)):
        p_y[i] = p_y[i] / 2*p_x[i]**2
    
    
    plt.plot(s_x,s_y, label="Serial Matrix Mult", color = 'red')
    plt.plot(p_x,p_y, label="Parallel Matrix Mult", color = 'blue')
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Comparision on parallel and serial merge sort")
    plt.legend()
    plt.show()
        
        