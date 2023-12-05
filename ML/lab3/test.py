from sklearn import datasets
from sklearn.model_selection import train_test_split
from sklearn.metrics import r2_score
import numpy as np

# 最小二乘损失
def err(dataSet):
    return np.var(dataSet[:,-1])*dataSet.shape[0]  #均方差*数据总条数

def splitDataSet(dataSet, feature, value):
    dataSet1=dataSet[dataSet[:,feature]<=value]
    dataSet2=dataSet[dataSet[:,feature]>value]
    return dataSet1,dataSet2
    
# 选择最好的特征划分数据集，min_sample每次划分后每部分最少的数据条数，epsilon误差下降阈值，值越小划分的决策树越深
def chooseBestFeature(dataSet,min_sample=4,epsilon=0.5):
    features=dataSet.shape[1]-1   # x特征列数量
    total_Err=err(dataSet) # 整个数据集的损失
    minErr=np.inf
    best_column = 0 # 划分最优列
    best_value = 0  # 划分最优的值
    nowErr=0       # 当前平方误差
    if len(np.unique(dataSet[:,-1].T.tolist())) == 1: # 数据全是一类的情况下 返回
        return None, np.mean(dataSet[:,-1])
    for feature in range(0,features): # 按x特征列循环
        for row in range(0,dataSet.shape[0]): # 遍历每行数据，寻找最优划分
            dataSet1,dataSet2=splitDataSet(dataSet, feature,dataSet[row,feature]) # 获得切分后的数据
            if len(dataSet1) < min_sample or len(dataSet2) < min_sample:  # 按行遍历时总会有一些划分得到的集合不满足最小数据条数约束，跳过此类划分
                continue
            nowErr=err(dataSet1)+err(dataSet2) # 计算当前划分的平方误差
            if nowErr<minErr: # 判断获得最优切分值
                minErr=nowErr
                best_column=feature
                best_value=dataSet[row,feature]
    if (total_Err - minErr) < epsilon: # 当前误差下降较小时，返回
        return None, np.mean(dataSet[:,-1])
    # 当前最优划分集合
    dataSet1,dataSet2=splitDataSet(dataSet, best_column,best_value)
    if len(dataSet1) < min_sample or len(dataSet2) < min_sample: # 如果划分的数据集很小，返回
        return None, np.mean(dataSet[:,-1])
    return best_column,best_value
    
def createTree(dataSet):
    best_column,best_value=chooseBestFeature(dataSet)
    if best_column == None:  # 所有列均遍历完毕，返回
        return best_value
    Tree = {}  # 决策树 
    Tree['spCol'] = best_column # 最优分割列
    Tree['spVal'] = best_value  # 最优分割值
    left_Set, right_Set = splitDataSet(dataSet, best_column,best_value) # 按当前最优分割列级值划分为左右2枝
    Tree['left'] = createTree(left_Set)  # 迭代继续划分左枝
    Tree['right'] = createTree(right_Set) # 迭代继续划分右枝
    return Tree

if __name__ == '__main__':
    flowers = datasets.load_iris()
    #按3：1划分训练数据和测试数据
    ftraindata, ftestdata, ftrainlabel, ftestlabel = train_test_split(flowers.data, flowers.target, test_size=0.25)
    dataSet=np.column_stack((ftraindata,ftrainlabel))      #合并
    tree=createTree(dataSet) 
    a={}
    numlist=[]
    for i in range(len(ftestdata)):
        temp_tree=tree
        while type(temp_tree)==type(a):
            temp=ftestdata[i]
            k=temp_tree['spCol']
            if temp[k]<=temp_tree['spVal']:
                temp_tree=temp_tree['left']
            else:
                temp_tree=temp_tree['right']
        numlist.append(temp_tree)
    print(tree)
    print(r2_score(np.array(numlist),ftestlabel))