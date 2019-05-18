# Download a sample from the titanic.csv file using the Pandas package
import pandas
import numpy as np
from sklearn.tree import DecisionTreeClassifier
outFile = open('output.txt', 'w', encoding='utf8')
data = pandas.read_csv('titanic.csv', index_col='PassengerId')
# Leave the sample four features
x_labels = ['Pclass', 'Fare', 'Age', 'Sex']
X = data.loc[:, x_labels]
# Notice that the Sex attribute has string values
X['Sex'] = X['Sex'].map(lambda sex: 1 if sex == 'male' else 0)
# Highlight target variable
y = data['Survived']
# Find all objects that have missing features and remove them from the selection
X = X.dropna()
y = y[X.index.values]
# Teach decision trees
clf = DecisionTreeClassifier(random_state=241)
clf.fit(X, y)
# Calculate the importance of signs and find the two signs with the greatest importance
importances = clf.feature_importances_
a = np.array(importances).argmax()
print(x_labels[a], end=' ', file=outFile)
importances[a] = 0
b = np.array(importances).argmax()
print(x_labels[b], end='', file=outFile)
