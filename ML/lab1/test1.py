from sklearn import datasets
from sklearn.cross_validation import train_test_split
from sklearn.linear_model import LogisticRegression
from sklearn.metrics import classification_report

iris = datasets.load_iris()
X_train=iris.data
Y_train=iris.target
print(type(X_train))
print(type(Y_train))
# X_train,X_test,Y_train,Y_test=train_test_split(X_train,Y_train,test_size=0.25,random_state=0,stratify=Y_train)
# regr=LogisticRegression()
# regr.fit(X_train,Y_train)

# print('Ceofficients:%s,intercept %s'%(regr.coef_,regr.intercept_))
# print('Score: %2f'%regr.score(X_test,Y_test))
# print(classification_report(Y_test,regr.predict(X_test)))