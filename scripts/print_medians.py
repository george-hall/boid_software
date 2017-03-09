import sys
import matplotlib as mp

if len(sys.argv) != 2:
    print "usage:", sys.argv[0], "<file>"
    sys.exit(1)

d = {}

with open(sys.argv[1]) as f:
    for line in f:
        num_iters = line.split()[0]
        if num_iters not in d.keys():
            d[num_iters] = [int(line.split()[-1])]
        else:
            d[num_iters].append(int(line.split()[-1]))

for i,l in d.items():
    print i, sorted(l)[len(l)/2]
