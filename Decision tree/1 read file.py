# Download a sample from the titanic.csv file using the Pandas package
import pandas
data = pandas.read_csv('titanic.csv', index_col='PassengerId')
