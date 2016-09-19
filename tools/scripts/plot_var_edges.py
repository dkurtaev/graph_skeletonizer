# Plot data received from experiments.
# By X-axis number of nodes, by Y-axis time in milliseconds of algorithm's work.
# This script plotting data of experiments with number of nodes is 10001
# and number of edges in interval [0, 1e+7] with step 1e+5
import matplotlib.pyplot as plt
import numpy as np

infile_name = './times_var_edges_%s.txt'

n_edges = np.arange(1, int(1e+7), int(1e+5))
n_nodes = np.array([10001 for e in n_edges])

theoretical = {'boruvka': lambda n, m: m * np.log(n) / np.log(2),
               'kruskal': lambda n, m: (2 * m + n) * np.log(n) / np.log(2)}

# Achieved time measurements.
plt.figure(figsize=(15, 7))
plt.subplot(1, 2, 1)
for method in ['boruvka', 'kruskal']:
    with open(infile_name % method, 'rt') as file:
        times = [int(l.rstrip('\n')) if l != '\n' else 0 for l in file]
    plt.plot(n_edges, times, label=method)

plt.xlabel('Number of edges, m')
plt.ylabel('Time in milliseconds')
plt.title('#nodes = 10001')
plt.legend(loc=4)
plt.grid(True)
plt.tight_layout()

# Theoretical estimation check.
plt.subplot(1, 2, 2)
for method, theory in zip(['boruvka', 'kruskal'],
                          ['m*log(n)', '(2m+n)*log(n)']):
    with open(infile_name % method, 'rt') as file:
        times = [int(l.rstrip('\n')) if l != '\n' else 0 for l in file]
    times = np.array(times) / theoretical[method](n_nodes, n_edges)
    plt.plot(n_edges, times, label='%s / %s' % (method, theory))

plt.xlabel('Number of edges, m')
plt.ylabel('Time in milliseconds / theoretical estimation')
plt.ticklabel_format(style='sci', axis='y', scilimits=(0, 0))
plt.title('#nodes = 10001')
plt.legend(loc=4)
plt.grid(True)
plt.tight_layout()

plt.savefig('plot_var_edges.svg')
