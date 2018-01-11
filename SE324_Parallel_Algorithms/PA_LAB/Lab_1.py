#To show the execution speed of sorting algos 
import random
import time

def GenerateList(r,n):
    
    arr = random.sample(range(1,r),n)
    return arr

def SelectSort(arr):
    
    for i in range(0,len(arr)):
        min_in = i
        for j in range(i+1,len(arr)):
            if(arr[j] < arr[min_in]):
                min_in = j
        arr[min_in], arr[i] = arr[i], arr[min_in]
    

def Part(arr, low, high):
    i = low - 1
    piv = arr[high]
    for j in range(low, high):
        if (arr[j] <= piv):
            i += 1
            arr[i], arr[j] = arr[j], arr[i]
    arr[i+1],arr[high] = arr[high], arr[i+1]
    return i+1

def QuickSort(arr, low, high):
    if(low < high):
        pi = Part(arr,low,high)
        QuickSort(arr,low,pi-1)
        QuickSort(arr,pi+1,high)


def main():
    
    r = 10000000000
    n = int(input("Enter the number of elements : "))
    inc = int(input("Enter the increments in elements : "))

    for i in range (0,inc):
        arr = GenerateList(r,n*(10**i))
        start = time.time()
        SelectSort(arr)
        end = time.time()
        print("sorted array of {0} elements in {1} using select sort".format(n*(10**i),round(end-start,3)))
        arr = GenerateList(r,n*(10**i))
        start = time.time()
        QuickSort(arr,0,len(arr)-1)
        end = time.time()
        print("sorted array of {0} elements in {1} using quick sort".format(n*(10**i),round(end-start,3)))

if __name__ == '__main__':
    main()
