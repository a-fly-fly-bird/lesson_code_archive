from numpy.core.fromnumeric import size
from sklearn.datasets import make_moons
import numpy as np
import pandas as pd
# f = open(r'C:\Users\LEGION\Desktop\学习\机器学习\实验2\moons.csv', encoding='UTF-8')
# dataset = pd.read_csv(f, header=None)
# X = dataset[dataset.columns[0:2]].values.T
# Y = dataset[dataset.columns[2:3]].values.T
# print(Y)
X, y = make_moons(n_samples=100, noise=0.15, random_state=42)
print(X)
print(y)
np.savetxt(r'C:\Users\LEGION\Desktop\学习\机器学习\实验2\new.csv', X, delimiter = ',')
# import numpy as np
# n_x=4
# n_h=10
# n_y=3
# #np.random.seed(2)
# w1 = np.random.randn(n_h, n_x)
# b1 = np.zeros(shape=(n_h, 1))
# w2 = np.random.randn(n_y, n_h)
# b2 = np.zeros(shape=(n_y, 1))
# m=w2.shape[1]
# print(w2)
# print(m)
