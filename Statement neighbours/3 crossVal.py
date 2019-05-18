# Extract the characteristics and classes from the data
import numpy as np
import pandas as pd
import sklearn.model_selection
data = pd.read_csv('wine.data', header=None)
X = pd.read_csv('wine.data', header=None, usecols=list(range(1,14)))
Y = pd.read_csv('wine.data', header=None, usecols=[0]).values.reshape(len(X),)
# Cross validation part 1
crossV = sklearn.model_selection.KFold(n_splits=5, shuffle=True, random_state=42)

