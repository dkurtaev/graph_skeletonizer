# Runs algorithms with different sets of input parameters.
# NOTE: Script using relative path to tool, run this script from it's directory.
import os
import numpy as np
import matplotlib.pyplot as plt
import time

tool = '../../build/bin/skeletonizer'
cmd = '%s -n %d -m %d -min_w %f -max_w %f -%s -q | xargs echo >> %s'

outfile_names = ['./times_100n_edges_%s.txt',
                 './times_1000n_edges_%s.txt',
                 './times_0.1nn_edges_%s.txt',
                 './times_max_edges_%s.txt',
                 './times_var_edges_%s.txt']

n_set = np.arange(101, 10002, 100)
m_set = np.arange(0, int(1e+7), int(1e+5))
params = [[n_set, 100 * n_set],
          [n_set, 1000 * n_set],
          [n_set, 0.1 * n_set ** 2],
          [n_set, n_set * (n_set - 1) / 2],
          [[10001 for m in m_set], m_set]]

try:
    for method in ['boruvka', 'kruskal']:
        for i in range(len(outfile_names)):
            outfile = outfile_names[i] % method
            open(outfile, 'wt').close()

            for n_nodes, n_edges in zip(params[i][0], params[i][1]):
                os.system(cmd % (tool, n_nodes, n_edges, 1.0, 1e+6, method,
                                 outfile))
                time.sleep(0.01)
except KeyboardInterrupt:
    print 'Ehlo!'
