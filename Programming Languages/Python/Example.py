#Import Python Libraries
import numpy as np
import scipy as sp
import pandas as pd
import matplotlib as mpl
import seaborn as sns

df = pd.read_csv("http://rcs.bu.edu/examples/python/data_analysis/Salaries.csv")
df.head()

#Check a particular column type
df['salary'].dtype

#Check types for all the columns
df.dtypes

print (df.head())
print (df.dtypes)