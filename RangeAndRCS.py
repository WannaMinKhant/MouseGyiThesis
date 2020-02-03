import math
import os
import time
import numpy as np
import csv

Ae = 1.069*10**-4
Ptx = 0.01
pm = 0.05011872336
G = 8.6
S = 3.16227766*10**-14

result = [[0 for i in range(200)] for j in range(100)]




def Range(sigma,P):
	range = ((P * G * Ae * sigma)/ ((4* math.pi)**2*S))**0.25
	print(range)
	return range

for i in range(200):
	for k in range(100):
		Ptx = Ptx + 0.001
		result[k][i] = Range(i,Ptx)
	
with open('range_file.csv', mode='w') as csv_file:
    csv_writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
    csv_writer.writerows(result)
