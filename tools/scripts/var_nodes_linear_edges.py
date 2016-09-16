# Number of nodes in [1, 1e+4 + 1]
# Number of edges = 100n and 1000n
import argparse
import os
import matplotlib.pyplot as plt

parser = argparse.ArgumentParser(
    description='Run MST (minimal spanning tree) methods and plot performance')
parser.add_argument('-t', dest='tool', required=True,
                    help='Path to tool for run')
args = parser.parse_args()

outfile = './times_%dn_edges_%s.txt'
cmd = '%s -n %d -m %d -min_w %f -max_w %f -%s -q | xargs echo >> ' + outfile

for scale in [100, 1000]:
    for method in ['boruvka', 'kruskal']:
        open(outfile % (scale, method), 'wt').close()
        for n_nodes in range(101, 10002, 100):
            n_edges = n_nodes * scale
            os.system(cmd % (args.tool, n_nodes, n_edges, 1.0, 1e+6, method,
                             scale, method))

    plt.clf()
    for method in ['boruvka', 'kruskal']:
        with open(outfile % (scale, method), 'rt') as file:
            times = [line.rstrip('\n') if line != '\n' else 0 for line in file]
            plt.plot(range(101, 10002, 100), times, label=method)

    plt.xlabel('Number of nodes (n)')
    plt.ylabel('Time in milliseconds')
    plt.title('w in [1, 1e+6], #edges=%dn' % scale)
    plt.legend()
    plt.grid(True)
    plt.savefig(outfile % (scale, 'plot'))
