from sklearn.model_selection import train_test_split
from sklearn import datasets
moon = datasets.make_moons()
moon_feature = moon[0]
moon_target = moon[1]
feature_train, feature_test, target_train, target_test = train_test_split(
    moon_feature, moon_target, test_size=0.33, random_state=10)
# iris = datasets.load_iris()
# iris_feature = iris['data']
# iris_target = iris['target']
# iris_target_name = iris['target_names']
# feature_train, feature_test, target_train, target_test = train_test_split(
#     iris_feature, iris_target, test_size=0.33, random_state=10)

# 构建决策树则需定义结点类


class Node:
    def __init__(self, dimension, threshold, isLeaf, left, right, species):
        self.dimension = dimension  # 划分维度
        self.threshold = threshold  # 划分阈值
        self.isLeaf = isLeaf  # 是否是叶节点
        self.left = left  # 左支（叶节点时为None）
        self.right = right  # 右支（叶节点时为None）
        self.species = species  # 分类（如果是叶节点）

    # def show(self):
    #     if self.isLeaf:
    #         print("若第",self.dimension,"个特征小于",self.threshold,"则种类为",self.species)
    #     else:
    #         print("该节点对第",self.dimension,"个特征进行分类，划分阈值为",self.threshold)


# 计算Gini值
def Gini(label):
    """
    计算gini指数
    :param label 为分类
    :return: gini值
    """
    gini = 1
    dic = {}
    for target in label:
        if target in dic.keys():
            dic[target] += 1
        else:
            dic[target] = 1
    for value in dic.values():
        tmp = value / len(label)
        gini -= tmp * tmp
    return gini


"""
因为鸢尾花特征数据均为连续值，因此要对连续值二分化
步骤：
1.将连续属性a的n个不同取值从小到大排序
2.选取相邻属性的值的平均值选为候选划分点
3.遍历候选划分点，选取使基尼系数最小的阈值作为划分点
"""


def Gini_index(feature, label, dimension):
    """
    获取属性a的基尼指数
    选择使划分之后基尼指数虽小的属性为最优划分属性
    :param feature：所有属性
    :param label：标记(为数组)
    :param dimension：维度
    :return: 最小的index和对应阈值threshold
    """
    attribute = feature[:, dimension]
    gini_index = 1
    threshold = 0
    # 排序
    attribute_sort = sorted(attribute)
    candidate = []
    # 二分
    for i in range(len(attribute_sort)-1):
        temp = (attribute_sort[i]+attribute_sort[i+1])/2
        if temp not in candidate:
            candidate.append(temp)
    # 寻找使基尼系数最小的候选值
    for thres_temp in candidate:
        index_small_list = []  # 记录比阈值小的属性值的index
        index_large_list = []  # 记录比阈值大的属性值的index
        for index in range(len(feature)):
            if attribute[index] < thres_temp:
                index_small_list.append(index)
            else:
                index_large_list.append(index)
        label_small_temp = label[index_small_list]  # 记录比阈值小的属性值
        label_large_temp = label[index_large_list]  # 记录比阈值小的属性值
        gini_index_temp = Gini(label_small_temp)*len(label_small_temp) / len(
            attribute) + Gini(label_large_temp)*len(label_large_temp)/len(attribute)
        if gini_index_temp < gini_index:
            gini_index = gini_index_temp
            threshold = thres_temp

    return gini_index, threshold


def find_dimension(feature, label):
    """
    寻找划分维度
    鸢尾花数据集有四个维度的数据，需确定选择哪个进行划分
    依次计算各维度下最小基尼系数，选取最小的为划分维度
    """
    dimension = 0
    threshold = 0
    gini_index_min = 1
    for d in range(len(feature[1])):
        gini_index, thres = Gini_index(feature, label, d)
        if gini_index < gini_index_min:
            gini_index_min = gini_index
            dimension = d
            threshold = thres
    return gini_index_min, threshold, dimension


def left_right(feature, label, threshold, dimension):
    """
    根据阈值和划分维度划分左子树和右子树
    """
    attribute = feature[:, dimension]
    index_small_list = []
    index_large_list = []
    for index in range(len(feature)):
        if attribute[index] < threshold:
            index_small_list.append(index)
        else:
            index_large_list.append(index)
    feature_small = feature[index_small_list]
    label_small = label[index_small_list]
    feature_large = feature[index_large_list]
    label_large = label[index_large_list]

    return feature_small, label_small, feature_large, label_large


def build_tree(feature, label):
    """
    构建决策树
    :param feature:所有属性list
    :param label:标记list
    :return: 决策树结点Node
    """
    if len(label) > 1:
        gini_index, threshold, dimension = find_dimension(feature, label)
        if gini_index == 0:
            # 若gini系数为0，说明都为一个类型，不需要划分，为叶节点
            return Node(dimension, threshold, True, None, None, label[0])
        else:
            feature_small, label_small, feature_large, label_large = left_right(
                feature, label, threshold, dimension)
            left = build_tree(feature_small, label_small)
            right = build_tree(feature_large, label_large)
            return Node(dimension, threshold, False, left, right, None)
    else:
        # 只有一个数据，为叶节点
        return Node(None, None, True, None, None, label[0])


def predict(root: Node, feature_line):
    """
    使用该方法进行预测
    :param root: 决策树根节点
    :param feature_line: 需要预测的属性值
    :return: 预测结构 label
    """
    node = root
    while not node.isLeaf:
        if feature_line[node.dimension] < node.threshold:
            node = node.left
        else:
            node = node.right
    return node.species


def score(root, feature, label):
    """
    模型得分评估
    :param root: 决策树根节点
    :param feature: 测试集属性list
    :param label: 测试集标记list
    :return: 正确率
    """
    correct = 0
    for index in range(len(feature)):
        type = predict(root, feature[index])
        if type == label[index]:
            correct += 1
    print('correct rate is', correct / len(feature))


def preorder(root: Node):
    if root.isLeaf is False:
        if root.left.isLeaf is False and root.right.isLeaf is False:
            print("该节点不是叶节点，分类标准为第", root.dimension, "个维度，划分阈值为", root.threshold,
                  "，若第", root.dimension, "个属性小于", root.threshold, "，则划分至左子树：")
            preorder(root.left)
            print("若第", root.dimension, "个属性大于", root.threshold, "，则划分至右子树：")
            preorder(root.right)
        elif root.left.isLeaf is True and root.right.isLeaf is False:
            print("该节点不是叶节点，分类标准为第", root.dimension, "个维度，划分阈值为", root.threshold, "，若第",
                  root.dimension, "个属性小于", root.threshold, "，则划分至左子树：种类为：", root.left.species)
            print("若第", root.dimension, "个属性大于", root.threshold, "，则划分至右子树：")
            preorder(root.right)
        elif root.left.isLeaf is False and root.right.isLeaf is True:
            print("该节点不是叶节点，分类标准为第", root.dimension, "个维度，划分阈值为", root.threshold,
                  "，若第", root.dimension, "个属性小于", root.threshold, "，则划分至左子树：",)
            preorder(root.left)
            print("若第", root.dimension, "个属性大于", root.threshold,
                  "，则划分至右子树：种类为：", root.left.species)


# print(feature_train)
# print(target_train)
res = build_tree(feature_train, target_train)
preorder(res)
# print(res.dimension,res.threshold,res.species,res.isLeaf)
# print(res.left.dimension,res.left.threshold,res.left.species,res.left.isLeaf)
score(res, feature_test, target_test)
