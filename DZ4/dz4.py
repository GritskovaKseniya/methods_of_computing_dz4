from findRoots import findRoots
from utils import readMatrixFromFile
import matplotlib.pyplot as plt
import numpy as np

from math import exp, sin, pi

matrix = readMatrixFromFile('input.txt')

# Выделяем столбец свободных членов
col = [row[len(matrix)] for row in matrix]

# Удаляем столбец свободных членов из матрицы
for i in range(len(matrix)):
    matrix[i] = matrix[i][:-1]

coff = findRoots(matrix, col)

coff_1 = coff[:4]
coff_2 = coff[4:]

def f(x):
    return pow(1 - x**4, 0.333333)

def S_1(x):
    return coff_1[0] * x**3 \
        + coff_1[1] * x**2 \
        + coff_1[2] * x \
        + coff_1[3]

def S_2(x):
    return coff_2[0] * x**3 \
        + coff_2[1] * x**2 \
        + coff_2[2] * x \
        + coff_2[3]



x = np.linspace(-0.00001, 0.9) # создаём область, в которой будет отображаться график

f_y = [f(x) for x in x]
S_y = [S_1(x) if x < 0.45 else S_2(x) for x in x]

plt.plot(x, f_y, label='f')
plt.plot(x, S_y, label = 'S')
plt.legend()
plt.show()


