# from typing_extensions import ParamSpec
import numpy as np
import pandas as pd

'''
e.g.
构建一个具有一个隐藏层的神经网络，大小为10
鸢尾花有四个特征，故输入层为4个特征
鸢尾花有三个类别，故输出层为3个特征(0,0,0)(0,1,0)(0,0,1)
'''


def sigmoid(x):
    x_ravel = x.ravel()  # 将numpy数组展平
    length = len(x_ravel)
    y = []
    for index in range(length):
        if x_ravel[index] >= 0:
            y.append(1.0 / (1 + np.exp(-x_ravel[index])))
        else:
            y.append(np.exp(x_ravel[index]) / (np.exp(x_ravel[index]) + 1))
    return np.array(y).reshape(x.shape)

# def sigmoid(x):
#     return 1.0 / (1 + np.exp(-x))

# 1.初始化参数,n_x=4,n_h=10,n_y=3


def initial(n_x, n_h, n_y):
    # w1为输入到隐层的权重，w2为隐层到输出的权重
    w1 = np.random.randn(n_h, n_x)
    b1 = np.zeros(shape=(n_h, 1))
    w2 = np.random.randn(n_y, n_h)
    b2 = np.zeros(shape=(n_y, 1))
    # 用字典存储参数
    parameters = {'w1': w1, 'b1': b1, 'w2': w2, 'b2': b2}

    return parameters

# 2.前向传播


def forward_pass(X, parameters):
    w1 = parameters['w1']
    b1 = parameters['b1']
    w2 = parameters['w2']
    b2 = parameters['b2']

    # 计算
    z1 = np.dot(w1, X)+b1
    a1 = sigmoid(z1)  # Sigmoid为激活函数
    z2 = np.dot(w2, a1)+b2
    a2 = sigmoid(z2)  # Sigmoid为激活函数

    # 通过字典储存参数
    forward_result = {'z1': z1, 'a1': a1, 'z2': z2, 'a2': a2}

    return forward_result

# 3.后向传播


def backward_pass(parameters, forward_result, X, Y):
    m = Y.shape[1]
    w2 = parameters['w2']
    a1 = forward_result['a1']
    a2 = forward_result['a2']

    # 计算
    dz2 = a2-Y  # 差值
    dw2 = (1/m)*np.dot(dz2, a1.T)
    db2 = (1/m)*np.sum(dz2, axis=1, keepdims=True)
    dz1 = np.multiply(np.dot(w2.T, dz2), 1-np.power(a1, 2))
    dw1 = (1/m)*np.dot(dz1, X.T)
    db1 = (1/m)*np.sum(dz1, axis=1, keepdims=True)

    change = {'dw1': dw1, 'db1': db1, 'dw2': dw2, 'db2': db2}

    return change

# 4.更新权值


def update_parameters(parameters, change, learning_rate=0.4):
    w1 = parameters['w1']
    b1 = parameters['b1']
    w2 = parameters['w2']
    b2 = parameters['b2']

    dw1 = change['dw1']
    db1 = change['db1']
    dw2 = change['dw2']
    db2 = change['db2']

    w1 -= learning_rate*dw1
    b1 -= learning_rate*db1
    w2 -= learning_rate*dw2
    b2 -= learning_rate*db2

    parameters = {'w1': w1, 'b1': b1, 'w2': w2, 'b2': b2}

    return parameters

# 5.模型评估


def predict(parameters, x_test, y_test):
    w1 = parameters['w1']
    b1 = parameters['b1']
    w2 = parameters['w2']
    b2 = parameters['b2']

    # 计算
    z1 = np.dot(w1, x_test)+b1
    a1 = sigmoid(z1)  # Sigmoid为激活函数
    z2 = np.dot(w2, a1)+b2
    a2 = sigmoid(z2)  # Sigmoid为激活函数

    # 结果的维度
    n_rows = y_test.shape[0]
    n_cols = y_test.shape[1]

    # 预测值结果存储
    output = np.empty(shape=(n_rows, n_cols), dtype=int)

    for i in range(n_rows):
        for j in range(n_cols):
            if a2[i][j] > 0.5:
                output[i][j] = 1
            else:
                output[i][j] = 0

    print('预测结果：')
    print(output)
    print('真实结果：')
    print(y_test)

    count = 0
    for k in range(0, n_cols):
        if output[0][k] == y_test[0][k] and output[1][k] == y_test[1][k]:
            count += 1
        # if output[0][k] == y_test[0][k] and output[1][k] == y_test[1][k] and output[2][k] == y_test[2][k]:
        #     count = count + 1
        # else:
        #     print(k)

    acc = count / int(y_test.shape[1]) * 100
    print('准确率：%.2f%%' % acc)

    return output

# 建立神经网络


def bp(X, Y, n_h, n_x, n_y, max_iterations):
    parameters = initial(n_x, n_h, n_y)
    for i in range(max_iterations):
        forword_result = forward_pass(X, parameters)
        change = backward_pass(parameters, forword_result, X, Y)
        parameters = update_parameters(parameters, change)

    return parameters


if __name__ == "__main__":
    # # 获取数据
    # f = open(r'C:\Users\LEGION\Desktop\学习\机器学习\实验2\iris_training.csv', encoding='UTF-8')
    # dataset = pd.read_csv(f, header=None)
    # X = dataset[dataset.columns[0:4]].values.T
    # Y = dataset[dataset.columns[4:7]].values.T
    # Y = Y.astype('uint8')  # 将string转化为8位无符号整数
    # # 训练
    # parameters = bp(X, Y, n_h=10, n_x=4, n_y=3, max_iterations=10000)
    # # 测试
    # f = open(r'C:\Users\LEGION\Desktop\学习\机器学习\实验2\iris_test.csv', encoding='UTF-8')
    # dataset = pd.read_csv(f, header=None)
    # X_test = dataset[dataset.columns[0:4]].values.T
    # Y_test = dataset[dataset.columns[4:7]].values.T
    # Y_test = Y_test.astype('uint8')  # 将string转化为8位无符号整数
    # result = predict(parameters, X_test, Y_test)
    # 获取数据
    f = open(r'C:\Users\LEGION\Desktop\学习\机器学习\实验2\moons.csv', encoding='UTF-8')
    dataset = pd.read_csv(f, header=None)
    X = dataset[dataset.columns[0:2]].values.T
    Y = dataset[dataset.columns[2:4]].values.T
    Y = Y.astype('uint8')  # 将string转化为8位无符号整数
    # 训练
    parameters = bp(X, Y, n_h=10, n_x=2, n_y=2, max_iterations=10000)
    # 测试
    f = open(r'C:\Users\LEGION\Desktop\学习\机器学习\实验2\moon_test.csv', encoding='UTF-8')
    dataset = pd.read_csv(f, header=None)
    X_test = dataset[dataset.columns[0:2]].values.T
    Y_test = dataset[dataset.columns[2:4]].values.T
    Y_test = Y_test.astype('uint8')  # 将string转化为8位无符号整数
    result = predict(parameters, X_test, Y_test)
