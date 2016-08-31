#!/usr/bin/python

import sys

if len(sys.argv) < 2:
  fname = 'input.txt'
else:
  fname = sys.argv[1]

fin = open(fname)
for line in fin:
  line = line.strip()
  print line

