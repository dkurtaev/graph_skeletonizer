# Number of nodes in [1, 1e+4 + 1]
# Number of edges = n * (n - 1) / 2 (maximal number of edges)
import argparse
import os
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(
    description='Run MST (minimal spanning tree) methods and plot performance')
parser.add_argument('-t', dest='tool', required=True,
                    help='Path to tool for run')
args = parser.parse_args()

outfile = './times_%.1fmax_edges_%s.txt'
cmd = '%s -n %d -m %d -min_w %f -max_w %f -%s -q | xargs echo >> ' + outfile

for scale in [1.0, 0.1]:
    for method in ['boruvka', 'kruskal']:
        open(outfile % (scale, method), 'wt').close()
        for n_nodes in range(101, 10002, 100):
            n_edges = scale * n_nodes * (n_nodes - 1) / 2
            os.system(cmd % (args.tool, n_nodes, n_edges, 1.0, 1e+6, method,
                             scale, method))

    for method in ['boruvka', 'kruskal']:
        with open(outfile % (scale, method), 'rt') as file:
            times = [line.rstrip('\n') if line != '\n' else 0 for line in file]
            plt.plot(range(101, 10002, 100), times, label=method)

    plt.xlabel('Number of nodes (n)')
    plt.ylabel('Time in milliseconds')
    plt.title('w in [1, 1e+6], #edges=%.1f*n(n-1)/2' % scale)
    plt.legend()
    plt.grid(True)
    plt.savefig('./times_%.1fmax_edges.svg' % scale)
