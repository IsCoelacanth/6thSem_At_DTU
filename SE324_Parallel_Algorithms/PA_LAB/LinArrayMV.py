import multiprocessing as mp
from util import GetMatrix, GetVector
import time
from Lab_3_MatVec import Multiply
import matplotlib.pyplot as plt
def mult(A, u, V):
    sum = 0
    for i in range(len(u)):
        sum += A[i]*u[i]
    V.value = sum

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
        # print("Generated Matrix A")
        # for i in A:
        #     print(i)
        # print("Generated vector u")
        # for i in u:
        #     print(i)
        s = time.time()
        C = Multiply(A,u)
        e = time.time()
        # print("Result Vector V using serial multiplication")
        # for i in C:
        #     print(i)
        s_x.append(z)
        s_y.append(e-s)

        Proc = []
        V = []
        s = time.time()
        for i in range(z):
            V.append(mp.Value('i',0))
            Proc.append(mp.Process(target=mult, args = (A[i], u, V[i])))
            Proc[i].start()
        for i in range(z):
            Proc[i].join()
        e = time.time()
        p_x.append(z)
        p_y.append((e-s)/z)
        # print("Result Matrix C using Mesh Multiplication")
        # for i in V:
        #     print(i.value)
        
    plt.plot(s_x,s_y, label="Serial Matrix Mult", color = 'red')
    plt.plot(p_x,p_y, label="Parallel Matrix Mult", color = 'blue')
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Comparision on parallel and serial merge sort")
    plt.legend()
    plt.show()

if __name__ == '__main__':
    main()
            