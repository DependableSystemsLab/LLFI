#!/usr/bin/env python2

#traceOntoGraph.py
#Author: Sam Coulter
#This script will take 1 trace Union file as input, and 1 llfi program dot graph
#it will apply the tracing information to the graph so that fault injected instructions
#are bordered in red, and fault affected instructions have a yellow fill
#Usage:
#     ./traceOntoGraph.py myTraceReportFile myProgramGraph.dot > myNewGraph.dot

import sys
import os
import glob
from tracetools import *

AFFECTED_FILL_COLOR = "yellow"
FAULT_INJECTED_BORDER_COLOR = "red"

prog = os.path.basename(sys.argv[0])

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
    affectedEdges = rep.getAffectedEdgesSet()
    for i in range(len(graphLines)):
      if ("llfiID_" + str(rep.faultID) + " [shape") in graphLines[i]:
        graphLines[i] = graphLines[i][:-3]
        graphLines[i] = graphLines[i] + ", color=\""+FAULT_INJECTED_BORDER_COLOR+"\"];\n"
      for x in affectedInsts:
        if ("llfiID_" + str(x) + " [shape") in graphLines[i]:
          graphLines[i] = graphLines[i][:-3]
          graphLines[i] = graphLines[i] + ", style=\"filled\", fillcolor=\""+AFFECTED_FILL_COLOR+\
          "\"];\n"
      for (s, e) in  affectedEdges:
        summation = sum(1 for line in graphLines if ("llfiID_" + str(s) + " -> " + "llfiID_" in line) and "blue" not in line)
        if summation == 2:
          if ("llfiID_" + str(s) + " -> " + "llfiID_" + str(e)+";") in graphLines[i]:
            graphLines[i] = graphLines[i][:-2]
            graphLines[i] = graphLines[i] + " [color=\"red\"" \
            + ", style=\"dashed\"];\n"


  print ''.join(graphLines)

  #restore stdout
  sys.stdout = oldSTDOut

if __name__ == "__main__":
  if len(sys.argv) >= 2 and (sys.argv[1] == '-h' or sys.argv[1] == '--help'):
    print >> sys.stderr, ("%(prog)s applies the program trace difference summary to program static control-data-flow graph to visualize it\n\n"
    "running option: %(prog)s <trace difference report> <program dot-formatted CDFG>" %{"prog": prog})
  elif len(sys.argv) >= 3:
    traceOntoGraph(sys.argv[1], sys.argv[2])
  else:
    print >> sys.stderr, "Error: running option: %(prog)s <trace difference report> <program dot-formatted CDFG>" %{"prog": prog}
    exit(1)

