#!/usr/bin/python

import sys
import os
import glob
from traceTools import *

def traceOntoGraph(traceFile, graphFile, output=0):
  #save stdout so we can redirect it without mangling other python scripts
  oldSTDOut = sys.stdout
  if output != 0:
    sys.stdout = open(output, "w")

  faultReports = parseFaultReportsfromFile(traceFile)

  graphF = open(graphFile, 'r')
  graphLines = graphF.readlines()
  graphF.close()

  for rep in faultReports:
    affectedInsts = rep.getAffectedSet()
    for i in range(len(graphLines)):
      if ("llfiID_" + str(rep.faultID) + " [shape") in graphLines[i]:
        graphLines[i] = graphLines[i][:-3]
        graphLines[i] = graphLines[i] + ", color=\"red\"];\n"
      for x in affectedInsts:
        if ("llfiID_" + str(x) + " [shape") in graphLines[i]:
          graphLines[i] = graphLines[i][:-3]
          graphLines[i] = graphLines[i] + ", style=\"filled\", fillcolor=\"yellow\"];\n"

  print ''.join(graphLines)

  #restore stdout
  sys.stdout = oldSTDOut

if __name__ == "__main__":
  traceOntoGraph(sys.argv[1], sys.argv[2])