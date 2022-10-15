import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

with open("res.txt") as file:
    raw_data = file.readlines()
    # data_transposed = data.T
    # data_transposed.columns = ["u_initial", "u_final"]

data = [[],[]]

for line in raw_data:
    values = [x.strip("\n") for x in line.split("\t")][:-2]
    data[raw_data.index(line)] = [float(x) for x in values]

x = np.linspace(0, 2, len(data[0]))
plt.figure()
plt.plot(x, data[0], label="Initial conditions")
plt.plot(x, data[1], label="Final values")
plt.legend(frameon=False)
plt.xlabel(r"$x$")
plt.ylabel(r"$u(x)$")
plt.show()
