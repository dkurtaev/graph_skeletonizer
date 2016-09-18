# Number of nodes is 10001
# Number of edges = 1000n
import argparse
import os
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(
    description='Run MST (minimal spanning tree) methods and plot performance')
parser.add_argument('-t', dest='tool', required=True,
                    help='Path to tool for run')
args = parser.parse_args()

outfile = './times_1000n_edges_var_max_w_%s.txt'
cmd = '%s -n %d -m %d -min_w %f -max_w %f -%s -q | xargs echo >> ' + outfile

n_nodes = 10001
for method in ['boruvka', 'kruskal']:
    open(outfile % method, 'wt').close()
    for max_w in range(2, 200):
        n_edges = 1000 * n_nodes
        os.system(cmd % (args.tool, n_nodes, n_edges, 1.0, max_w, method,
                         method))

plt.clf()
for method in ['boruvka', 'kruskal']:
    with open(outfile % method, 'rt') as file:
        times = [line.rstrip('\n') if line != '\n' else 0 for line in file]
        plt.plot(range(2, 200), times, label=method)

plt.xlabel('Number of nodes (n)')
plt.ylabel('Time in milliseconds')
plt.title('#nodes=10001, #edges=1000n')
plt.legend()
plt.grid(True)
plt.savefig('./times_1000n_edges_var_max_w.svg')
