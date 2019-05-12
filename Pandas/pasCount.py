import pandas
outFile = open('output.txt', 'w', encoding='utf8')
data = pandas.read_csv('titanic.csv', index_col='PassengerId')
A = list(data['Sex'].value_counts())
print(A[0], A[1], end='', file=outFile)
