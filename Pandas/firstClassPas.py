import pandas
outFile = open('output.txt', 'w', encoding='utf8')
data = pandas.read_csv('titanic.csv', index_col='PassengerId')
A = dict(data['Pclass'].value_counts())
answer = round((A[1] / (A[1] + A[2] + A[3])) * 10000) / 100
print(answer, end='', file=outFile)
