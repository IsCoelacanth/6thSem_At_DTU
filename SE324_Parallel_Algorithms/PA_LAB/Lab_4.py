from joblib import Parallel, delayed
import multiprocessing as MP
from math import sqrt
import time
def fibo(n):
    f = [0 for i in range(n+1)]
    f[1] = 1
 
    for i in range(2 , n+1):
        f[i] = f[i-1] + f[i-2]
    return f[n]

def main():
    ip = range(2,100)
    num_cores = MP.cpu_count()
    print(num_cores)
    s = time.time()
    res = Parallel(n_jobs=100, backend="threading")(delayed(sqrt)(i) for i in ip)
    e = time.time()

    print("Time taken parallely : ",e-s)
    # print(res)
    res = []
    s = time.time()
    for i in ip:
        res.append(sqrt(i))
    e = time.time()
    print("Time taken serially : ",e-s)

if __name__ == '__main__':
    main()
