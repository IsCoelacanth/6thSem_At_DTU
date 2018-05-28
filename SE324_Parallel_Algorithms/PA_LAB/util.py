#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 16 12:12:24 2018

@author: rinzler
"""
import random

def getarr(m):
    return random.sample(range(10000000000),m)

def GetMatrix(m1):
    mat = []
    for i in range(m1):
        mat.append(random.sample(range(1000),m1))
    return mat

def GetVector(m1):
    arr = random.sample(range(10000),m1)
    return arr

def MinMaxScale(Arr):
    A = min(Arr)
    if A == 0:
        print ("Cannot scale")
        return Arr
    else:
        B = max(Arr)
        if B == A:
            print("Cannot scale")
            return Arr
        else:
            for i in range(len(Arr)):
                Arr[i] = (Arr[i] - A)/(B-A)
            return Arr

def mat_print(A):
    for i in A:
        print (i)
    print()