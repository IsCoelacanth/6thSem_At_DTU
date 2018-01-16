import random
import time

def GetMatrix():
    mat = []
    for i in range(4):
        mat.append(random.sample(range(10),4))
    return mat

def Multiply(M1, M2):
    res = []
    for i in range(len(M1)):
        res.append([0 for j in range(len(M2[0]))])

    for i in range(4):
        for j in range(4):
            res[i][j] = 0
            for k in range(4):
                res[i][j] += M1[i][k]*M2[k][j]
    return res

def main():
    print("Generating Matrix 1 :")
    M1 = GetMatrix()
    for i in M1:
        print(i)
    print("Generatig Matrix 2 : ")
    M2 = GetMatrix()
    for i in M2:
        print(i)
    print("Multiplying M1 and M2")
    res = Multiply(M1, M2)
    print("The result is : ")
    for i in res:
        print(i)

if __name__ == '__main__':
    main()