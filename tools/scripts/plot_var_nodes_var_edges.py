# Plot data received from experiments.
# By X-axis number of nodes, by Y-axis time in milliseconds of algorithm's work.
# This script plotting data of experiments with number of nodes
# in range [101, 10001] and different number of edges dependencies:
# 100n, 1000n, 0.1n^2, n(n-1)/2.
import matplotlib.pyplot as plt
import numpy as np

infile_names = ['./times_100n_edges_%s.txt',
                './times_1000n_edges_%s.txt',
                './times_0.1nn_edges_%s.txt',
                './times_max_edges_%s.txt']

titles = ['#edges = 100n',
          '#edges = 1000n',
          '#edges = 0.1n^2',
          '#edges = n(n-1)/2']

n_set = np.arange(101, 10002, 100)
n_edges = [100 * n_set,
           1000 * n_set,
           0.1 * n_set ** 2,
           n_set * (n_set - 1) / 2]

theoretical = {'boruvka': lambda n, m: m * np.log(n),
               'kruskal': lambda n, m: (m + n) * np.log(n)}

# Achieved time measurements.
plt.figure(figsize=(15, 15))
for i in range(len(infile_names)):
    plt.subplot(2, 2, i + 1)
    for method in ['boruvka', 'kruskal']:
        with open(infile_names[i] % method, 'rt') as file:
            times = [int(l.rstrip('\n')) if l != '\n' else 0 for l in file]
        plt.plot(n_set, times, label=method)

    plt.xlabel('Number of nodes, n')
    plt.ylabel('Time in milliseconds')
    plt.title(titles[i])
    plt.legend(loc=4)
    plt.grid(True)
plt.tight_layout()
plt.savefig('plot_times.svg')

# Theoretical estimation check.
plt.clf()
for i in range(len(infile_names)):
    plt.subplot(2, 2, i + 1)
    for method, theory in zip(['boruvka', 'kruskal'],
                              ['m*log(n)', '(m+n)*log(n)']):
        with open(infile_names[i] % method, 'rt') as file:
            times = [int(l.rstrip('\n')) if l != '\n' else 0 for l in file]
        times = np.array(times) / theoretical[method](n_set, n_edges[i])
        plt.plot(n_set, times, label='%s / %s' % (method, theory))

    plt.xlabel('Number of nodes, n')
    plt.ylabel('Time in milliseconds / theoretical estimation')
    plt.title(titles[i])
    plt.ticklabel_format(style='sci', axis='y', scilimits=(0, 0))
    plt.legend(loc=4)
    plt.grid(True)
plt.tight_layout()
plt.savefig('plot_theoretical_estim.svg')
