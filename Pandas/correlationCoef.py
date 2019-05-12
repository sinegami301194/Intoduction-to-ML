import pandas
import math as m


outFile = open('output.txt', 'w', encoding='utf8')
data = pandas.read_csv('titanic.csv', index_col='PassengerId')


quotient = 0
denominator1 = 0
denominator2 = 0
X = dict(data['SibSp'])
Y = dict(data['Parch'])

X_middle = data['SibSp'].sum() / data['SibSp'].count()
Y_middle = data['Parch'].sum() / data['Parch'].count()

for i in range(1, data['SibSp'].count()):
    quotient += (X[i] - X_middle) * (Y[i] - Y_middle)
    denominator1 += (X[i] - X_middle) ** 2
    denominator2 += (Y[i] - Y_middle) ** 2
r = quotient / m.sqrt(denominator1 * denominator2)

print(round(r * 100) / 100, end='', file=outFile)
