# Download a sample from the titanic.csv file using the Pandas package
import pandas
data = pandas.read_csv('titanic.csv', index_col='PassengerId')
# Leave the sample four features
del data['Survived']
del data['Name']
del data['SibSp']
del data['Parch']
del data['Ticket']
del data['Cabin']
del data['Embarked']
# Notice that the Sex attribute has string values
print(type(data['Sex'][1]))
