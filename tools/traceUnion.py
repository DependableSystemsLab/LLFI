#!/usr/bin/python

#traceUnion.py
#Author: Sam Coulter
#This script will take any number (1+) of fault tracing reports as input, and output
#a combined (union'd) faultreport to standard input, use pipe redirection to 
#save to file
#Example Usage:
#     ./traceUnion.py file1 file2 file3 ... fileN > finalFile

from traceTools import *

def traceUnion(argv, output=0):
  #save stdout so we can redirect it without mangling other python scripts
  oldSTDOut = sys.stdout

  if output != 0:
    sys.stdout = open(output, "w")


  reps = []
  for f in argv:
    reps.extend(parseFaultReportsfromFile(f))

  i = 0
  x = 1
  length = len(reps)
  print "length ", len(reps)
  while i < length:
    while x < length:
      if reps[i].faultID == reps[x].faultID:
        reps[i].union(reps[x])
        reps.pop(x)
        length = len(reps)
        print "length ", len(reps)
      x += 1
    i += 1



  for rep in reps:
    print rep.report()


  #restore stdout
  sys.stdout = oldSTDOut

if __name__ == "__main__":
    traceUnion(sys.argv[1:])