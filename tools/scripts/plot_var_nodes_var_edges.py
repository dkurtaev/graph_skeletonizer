# Plot data received from experiments.
# By X-axis number of nodes, by Y-axis time in milliseconds of algorithm's work.
# This script plotting data of experiments with number of nodes
# in range [101, 10001] and different number of edges dependencies:
# 100n, 1000n, 0.1n^2, n(n-1)/2.
import matplotlib.pyplot as plt
import numpy as np

outfile_names = ['./times_100n_edges_%s.txt',
                 './times_1000n_edges_%s.txt',
                 './times_0.1nn_edges_%s.txt',
                 './times_max_edges_%s.txt']

titles = ['#edges = 100n',
          '#edges = 1000n',
          '#edges = 0.1n^2',
          '#edges = n(n-1)/2']

n_set = np.arange(101, 10002, 100)

for i in range(len(outfile_names)):
    plt.clf()

    for method in ['boruvka', 'kruskal']:
        with open(outfile_names[i] % method, 'rt') as file:
            times = [int(l.rstrip('\n')) if l != '\n' else 0 for l in file]
        plt.plot(n_set, times, label=method)

    plt.xlabel('Number of nodes, n')
    plt.ylabel('Time in milliseconds')
    plt.title(titles[i])
    plt.legend(loc=2)
    plt.grid(True)
    plt.show()
