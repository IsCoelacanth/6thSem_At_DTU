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
    st = int(input("Enter the starting size : "))
    ed = int(input("Enter the endibg size : "))
    s_x = []
    s_y = []
    p_x = []
    p_y = []

    for z in range(st,ed):
        A = GetMatrix(z)
        B = GetMatrix(z)
        V = []
        print("Generated Matrix A")
        mat_print(A)
        print("Generated Matrix V")
        mat_print(B)
        s = time.time()
        C = Multiply(A,B)
        e = time.time()        
        print ('Result using n3 algorithm')
        mat_print(C)
        s_x.append(z)
        s_y.append(e-s)
        C_p = [[[0 for i in range(z)]for j in range(z)] for k in range(z)]
        # print(C_p)
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

        e1 = time.time()
        for _2 in procs:
            for _1 in _2:
                for i in _1:
                    i.start()
        s1 = time.time()
        for _2 in procs:
            for _1 in _2:
                for i in _1:
                    i.join()
        # Mult step done:
        C = [[0 for i in range(z)] for i in range(z)]
        e2 = time.time()
        for i in range(z):
            for j in range(z):
                # print('C[{}][{}] = sum('.format(i, j), end = ' ')
                for k in range(z):
                    C[j][i] += C_p[k][j][i]
                #     print(C_p[k][j][i], end = ' ')
                # print()
        s2 = time.time()
        p_x.append(z)
        p_y.append(((s1-e1) + (s2-e2))/z**3)
        print ('Result using cube algorithm')
        mat_print(C)
    # s_y = MinMaxScale(s_y)
    # p_y = MinMaxScale(p_y)
    s_fit = np.polyfit(s_x, s_y,deg=2 )
    s_p = np.poly1d(s_fit)
    plt.plot(s_x,s_p(s_x), label="Serial Matrix Matrix Mult", color = 'red')
    plt.plot(p_x,p_y, label="Parallel Matrix Matrix Mult",color = 'blue')
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Comparision of parallel-hypercube and serial matrix multiplication")
    plt.legend()
    plt.show()
    s_up = [s_y[i]/p_y[i] for i in range(len(s_x))]
    plt.plot(s_x, s_up, label="speed up")
    plt.show()
                    

main()