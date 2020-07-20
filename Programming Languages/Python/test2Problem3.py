# Phong Nguyenho - ph094398
import numpy as np
import scipy as sp
import pandas as pd
import matplotlib as mpl
import seaborn as sns

df = pd.read_csv("http://rcs.bu.edu/examples/python/data_analysis/Salaries.csv")

def testProblem3a():
	df_m = df[ df['sex'] == 'Male' ]
	return df_m.groupby('sex')[['salary']].mean()

def testProblem3b():
	df_f = df[ df['sex'] == 'Female' ]
	df_r = df_f[ df_f['rank'] == 'AsstProf' ]
	return df_r[['salary']].agg(['max'])

def testProblem3c():
	return df[['salary']].agg(['std'])
