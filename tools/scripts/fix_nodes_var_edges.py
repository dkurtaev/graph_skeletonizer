# Number of nodes is 10001
# Number of edges in [0, 1e+7]
import argparse
import os
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(
    description='Run MST (minimal spanning tree) methods and plot performance')
parser.add_argument('-t', dest='tool', required=True,
                    help='Path to tool for run')
args = parser.parse_args()

outfile = './times_var_edges_%s.txt'
cmd = '%s -n %d -m %d -min_w %f -max_w %f -%s -q | xargs echo >> ' + outfile

n_nodes = 10001
for method in ['boruvka', 'kruskal']:
    open(outfile % method, 'wt').close()
    for n_edges in range(0, int(1e+7), int(1e+5)):
        os.system(cmd % (args.tool, n_nodes, n_edges, 1.0, 1e+6, method,
                         method))

plt.clf()
for method in ['boruvka', 'kruskal']:
    with open(outfile % method, 'rt') as file:
        times = [line.rstrip('\n') if line != '\n' else 0 for line in file]
        plt.plot(range(0, int(1e+7), int(1e+5)), times, label=method)

plt.xlabel('Number of edges')
plt.ylabel('Time in milliseconds')
plt.title('w in [1, 1e+6], #nodes=10001')
plt.legend()
plt.grid(True)
plt.savefig('./times_var_edges.svg')
