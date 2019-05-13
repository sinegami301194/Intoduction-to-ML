import pandas # Import library
outFile = open('output.txt', 'w', encoding='utf8') # Open file for writing answer
data = pandas.read_csv('titanic.csv', index_col='PassengerId') # Reading data from file
A = list(data['Sex'].value_counts()) # Creating list with information about passengers
print(A[0], A[1], end='', file=outFile)
