import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

with open("res.txt") as file:
    raw_data = file.readlines()

data = [[],[]]

for line in raw_data:
    values = [x.strip("\n") for x in line.split("\t")][:-2]
    data[raw_data.index(line)] = [float(x) for x in values]

x = np.linspace(0, 2, len(data[0]))
plt.figure()
plt.plot(x, data[0], label="Initial conditions")
plt.plot(x, data[1], label="Final values")
plt.legend(ncols=2, bbox_to_anchor=(0.5,1.15), loc="upper center")
plt.xlabel(r"$x$")
plt.ylabel(r"$u(x)$")
plt.show()
