# Download a sample from the titanic.csv file using the Pandas package
import pandas
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
