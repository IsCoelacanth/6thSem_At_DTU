from util import GetMatrix, GetVector, mat_print
import threading as th
import time
import math
from Lab_3_MatVec import Multiply
import matplotlib.pyplot as plt
import numpy as np

mx_th = 1
def tree_te_ply(vector, start, end, matrix, res):
    global mx_th
    mx_th = max(mx_th, th.active_count())
    if start > end:
        return

    if start == end:
        for i in range(len(matrix)):
            res[i] = vector[start] * matrix[i][start]
        return

    M = len(matrix)
    mid = math.floor((start + end) / 2)
    res1 = [0] * M
    res2 = [0] * M

    p1 = th.Thread(target=tree_te_ply, args=(vector, start, mid, matrix, res1))

    p2 = th.Thread(target=tree_te_ply, args=(vector, mid + 1, end, matrix, res2))

    p1.start()
    p2.start()
    p1.join()
    p2.join()

    for i in range(M):
        res[i] = res1[i] + res2[i]
    return

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
        print("Time taken : {}".format(e-s))
        mat_print(C)
        s_x.append(z)
        s_y.append(e-s)

        N = len(u)
        M = len(A)
        output = [0] * M
        strt = time.time()
        tree_te_ply(u, 0, N - 1, A, output)
        end = time.time()
        print("Result Vector V using tree multiplication")
        print("Time taken : {}".format(end-strt))
        mat_print(output)
        p_x.append(z)
        p_y.append((end-strt)/mx_th)
        
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
    plt.title("Comparision on parallel and serial matrix-vector tree mult")
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
