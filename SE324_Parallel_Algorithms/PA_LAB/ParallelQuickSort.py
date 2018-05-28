import threading as th
import time
import matplotlib.pyplot as plt
import numpy as np
from util import getarr
import random
mx_th = 1
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
            global mx_th
            mx_th = max(mx_th, th.active_count())
            pi = partition(arr, low, high)
            p1 = th.Thread(target=quicksort, args=(arr,low,pi-1, 'p'))
            p2 = th.Thread(target=quicksort, args=(arr, pi+1, high, 'p'))

            p1.start()
            p2.start()
            p1.join()
            p2.join()

def main():
    global mx_th
    st = int(input("Enter the starting size : "))
    ed = int(input("Enter the endibg size : "))
    s_x = []
    s_y = []
    p_x = []
    p_y = []
    for z in range(st,ed):
        print(z)
        arr = getarr(z)
        print(arr)
        x = arr.copy()
        s_x.append(z)
        st = time.time()
        quicksort(x,0,len(x)-1)
        s_y.append(time.time()-st)
        print("Sorted using serial quicksort : ")
        print(x)

        y = arr.copy()
        p_x.append(z)
        st = time.time()
        quicksort(y, 0, len(y)-1, 'p')
        p_y.append((time.time() - st)/mx_th)
        print("Sorted using parallel quicksort : ")
        print(y)
        mx_th = 1
    s_fit = np.polyfit(s_x, s_y,deg=2)
    s_p = np.poly1d(s_fit)
    plt.plot(s_x,s_p(s_x), color = 'red', label="Serial quicksort")
    p_fit = np.polyfit(p_x, p_y,deg=2)
    p_p = np.poly1d(p_fit)
    # plt.plot(p_x,p_y, label="Parallel Matrix Vector Mult", color = 'blue')
    plt.plot(p_x,p_p(p_x), color = 'blue', label="Parallel quicksort" )
    plt.xlabel('Input size')
    plt.ylabel('Time')
    plt.title("Comparision on parallel and serial quicksort")
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