import random

def GetMatrix(m1,m2):
    mat = []
    for i in range(m1):
        mat.append(random.sample(range(50),m2))
    return mat

def GetVector(m1):
    mat = []
    mat = random.sample(range(50),m1)
    return mat

def Multiply(M1, M2):
    if( len(M1[0]) != len(M2)):
        print("Incompatible Matrices, returning Null")
        return None
    res = []
    for i in range(len(M1)):
        res.append(0)

    for i in range(len(M1)):
        res[i] = 0
        for j in range(len(M2)):
            res[i] += M1[i][j]*M2[j]
    return res

def main():
    print("Enter Dimensions of matrix A : ")
    m1,m2 = map(int, input().split())
    print("Generated Matrix 1 :")
    M1 = GetMatrix(m1,m2)
    for i in M1:
        print(i)
    print("Enter Dimensions of Vector  B : ")
    m1 = int(input())
    print("Generated Vector 2 : ")
    M2 = GetVector(m1)
    print(M2)
    print("Multiplying M1 and M2")
    res = Multiply(M1, M2)
    print("The result is : ")
    for i in res:
        print(i)

if __name__ == '__main__':
    main()