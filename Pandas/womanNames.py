import pandas


outFile = open('output.txt', 'w', encoding='utf8')
data = pandas.read_csv('titanic.csv', index_col='PassengerId')


woman = list()
X = dict(data['Name'])
for i in range(1, data['Name'].count()):
    L = X[i].split()
    if 'Miss.' in L:
        woman.append(L[L.index('Miss.') + 1])
print(round(1 * 100) / 100, end='', file=outFile)
