import pandas
outFile = open('output.txt', 'w', encoding='utf8')
data = pandas.read_csv('titanic.csv', index_col='PassengerId')
A = dict(data['Age'].value_counts())
Sum = data['Age'].sum()
Count = data['Age'].count()
Middle = (round((Sum / Count) * 100)) / 100
Median = data['Age'].median()
print(Middle, Median, end='', file=outFile)
