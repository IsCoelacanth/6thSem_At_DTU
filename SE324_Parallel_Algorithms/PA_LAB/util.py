#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Mar 16 12:12:24 2018

@author: rinzler
"""
import random

def GetMatrix(m1):
    mat = []
    for i in range(m1):
        mat.append(random.sample(range(100),m1))
    return mat

def GetVector(m1):
    arr = random.sample(range(1000),m1)
    return arr