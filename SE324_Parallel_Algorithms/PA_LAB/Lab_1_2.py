import random
import time

def LinearSearch(arr,n):
    for i in range(len(arr)):
        if (arr[i] == n):
            return i
    return -1


def BinarySearch (arr, l, r, x):
    if r >= l:
 
        mid = l + (r - l)//2
        if arr[mid] == x:
            return mid
        elif arr[mid] > x:
            return BinarySearch(arr, l, mid-1, x)
        else:
            return BinarySearch(arr, mid+1, r, x)
    else:
       return -1

def MakeArr(n):
    return [i for i in range(n)]

def main():
    
    n = int(input("Enter the length of array to generate : "))
    i = int(input("Enter the factor by which to increase range : "))

    for i in range (0,i):
        arr = MakeArr(n*(10**i))
        que = random.randint(1,n*(10**i))
        start = time.time()
        index = LinearSearch(arr,que)
        end = time.time()
        print("Found at {0} in {1} using Linear Search".format(index,round(end-start,3)))
        start = time.time()
        index = BinarySearch(arr,0,len(arr)-1,que)
        end = time.time()
        print("Found at {0} in {1} using Binary Search".format(index,round(end-start,3)))

  
if __name__ == '__main__':
    main()
