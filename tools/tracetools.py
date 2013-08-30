#traceTools.py
#Author: Sam Coulter
#This file contains library functions and classes for the llfi tracing and
#tracing analyses scripts

import sys
import os
import glob
import itertools

class diffBlock:
  def __init__(self, lines):
    origHeader, newHeader = lines[0].replace('@',' ').replace('+',' ').replace('-',' ').split()
    origsplit = origHeader.split(',')
    newsplit = newHeader.split(',')
    self.origStart = int(origsplit[0])
    self.newStart = int(newsplit[0])

    self.origLines = []
    self.newLines = []

    #Sometimes the diff is printed with some context (up to 3 lines) before the diff lines
    #These lines affect the starting point of the diff header, and so their count must be added
    #to the diff start point
    for line in lines[1:]:
      if "+ID:" not in line and "-ID" not in line:
        self.origStart += 1
        self.newStart += 1
      else:
        break

    for line in lines[1:]:
      if "-ID: " in line:
        self.origLines.append(diffLine(line))
      if "+ID: " in line:
        self.newLines.append(diffLine(line))

    self.origLength = len(self.origLines)
    self.newLength = len(self.newLines)

  #print some info for debugging
  def printdebug(self):
    print self.origStart, self.newStart
    print '\n'.join(self.origLines)
    print '\n'.join(self.newLines)

  #print the block analysis summary
  def printSummary(self, adj=0):
    origStart = self.origStart + adj
    newStart = self.newStart + adj
    DataDiffs = []
    CtrlDiffs = []

    izip = itertools.izip_longest(self.origLines, self.newLines)
    
    instance = diffInstance(0,0,0,0)
    for i, (g, f) in enumerate(izip):      
      if g and f:
        if g.ID == f.ID:
          if instance.type != 1:
            instance.summary()
            instance = diffInstance(1, origStart, newStart, i)
          instance.add("Data Diff: ID: " + str(g.ID) + " OPCode: " + str(g.OPCode) + \
           " Value: " + str(g.Value) + " \\ " + str(f.Value))
          instance.incOrigLength()
          instance.incNewLength()
        else:
          if instance.type != 2:
            instance.summary()
            instance = diffInstance(2, origStart, newStart, i)
          instance.add("Ctrl Diff: ID: " + str(g.ID) + " \\ " + str(f.ID))
          instance.incOrigLength()
          instance.incNewLength()
      if g and not f:
        if instance.type != 2:
            instance.summary()
            instance = diffInstance(2, origStart, newStart, i)
        instance.add("Ctrl Diff: ID: " + str(g.ID) + " \\ None")
        instance.incOrigLength()
      if f and not g:
        if instance.type != 2:
            instance.summary()
            instance = diffInstance(2, origStart, newStart, i)
        instance.add("Ctrl Diff: ID: " + "None \\ " + str(f.ID))
        instance.incNewLength()
    instance.summary()

class diffInstance:
  def __init__(self, insttype, origstart, newstart, adj):
    self.origStart = origstart + adj
    self.origLength = 0
    self.origEnd = 0
    self.newStart = newstart + adj
    self.newLength = 0
    self.newEnd = 0
    self.type = insttype
    self.lines = []

  def add(self, line):
    self.lines.append(line)

  def summary(self):
    if len(self.lines) > 0:
      self.origEnd = self.origStart + self.origLength
      self.newEnd = self.newStart + self.newLength
      print "\nDiff@ inst # " + str(self.origStart) + "\\" + str(self.newStart) \
      + " -> inst # " + str(self.origEnd) + "\\" + str(self.newEnd)
      print '\n'.join(self.lines)

  def incOrigLength(self):
    self.origLength += 1

  def incNewLength(self):
    self.newLength += 1



class diffReport:
  def __init__(self, lines, startPoint):
    self.startPoint = startPoint
    self.blocks = []

    i = 0
    length = 1
    start = None
    
    while (i < len(lines)):
      if "@@ " in lines[i]:
        if start != None:
          self.blocks.append(diffBlock(lines[start:start+length]))
          length = 1        
        start = i
      else:
        length += 1
      i += 1 
    #Dont forget the last block in the diff!
    if start != None:
      self.blocks.append(diffBlock(lines[start:start+length]))

  def printSummary(self):
    for block in self.blocks:
      block.printSummary(self.startPoint)

    

class diffLine:
  def __init__(self, rawLine):
    self.raw = rawLine
    elements = str(rawLine).split()
    #ID: 14\tOPCode: sub\tValue: 1336d337
    assert (elements[0] in ["ID:","-ID:","+ID:"] and elements[2] == "OPCode:" and  \
      elements[4] == "Value:"), "DiffLine constructor called incorrectly"
    self.ID = int(elements[1])
    self.OPCode = str(elements[3])
    self.Value = str(elements[5])

  def _print(self):
    print "ID:",self.ID, "OPCode", self.OPCode, "Value:", self.Value

  def __str__(self):
    return self.raw

class faultReport:
  def __init__(self, lines):
    self.instNumber = -1
    self.faultCount = -1
    self.faultID = -1
    self.faultOPCode = ''
    self.goldValue = -1
    self.faultValues = []
    self.diffs = []

    if lines[0] == "#FaultReport\n":
      header = lines[1].split()
      self.faultCount = int(header[0])
      self.instNumber = header[2]

      fault = lines[2].split()
      self.faultID = int(fault[1])
      self.faultOPCode = fault[3]
      self.goldValue = fault[5]
      for i in range(self.faultCount):
        self.faultValues.append(fault[7 + i])

      i = 3
      while (i < len(lines)):
        if "Diff" not in lines[i]:
          break
        else:
          string = str(lines[i])
          if "@" in lines[i]:
            string = "\n" + string
          self.diffs.append(string)
        i += 1

    else:
      print "ERROR: Not a properly formed faultReport"

  def union(self, other):
    if self.faultID == other.faultID:
      self.faultCount += other.faultCount
      self.diffs.extend(other.diffs)
      self.faultValues.extend(other.faultValues)

  def report(self):
    lines = []
    lines.append("#FaultReport\n")
    header = str(self.faultCount) + " @ " + str(self.instNumber) + "\n"
    lines.append(header)
    faultline = "ID: " + str(self.faultID) + " OPCode: " + str(self.faultOPCode)
    faultline += " Value: " + str(self.goldValue) + " / "
    for val in self.faultValues:
      faultline += " " + str(val)
    faultline += '\n'
    lines.append(faultline)
    lines.extend(self.diffs)
    return ''.join(lines)

  def getAffectedSet(self):
    affectedInsts = set()
    for diff in self.diffs:      
      if "@" in diff:
        continue
      else:
        split = diff.split()
        if "Data" in diff:
          affectedInsts.add(int(split[3]))
#        if "Ctrl" in diff:                   #Commenting out to remove ctrl diff
#          if split[5] != "None":             #affected instructions from being 
#            affectedInsts.add(int(split[5])) #coloured on the graph
    if (int(self.faultID) in affectedInsts):
      affectedInsts.remove(int(self.faultID))
    return affectedInsts

  def getAffectedEdgesSet(self):
    affectedEdges = set()

    i = 0
    while i+1 < len(self.diffs):
      csplit = self.diffs[i+1].split()
      if "Diff@" in self.diffs[i] and "Ctrl Diff" in self.diffs[i+1] and csplit[5] != "None":
        dsplit = self.diffs[i].split()    
        affectedEdges.add(int(csplit[5]))
      i += 1

    return affectedEdges

def parseFaultReportsfromFile(target):
  reports = []
  reportFile = open(target, 'r')
  fileLines = reportFile.readlines()

  #Remove blank lines from list
  i = 0
  length = len(fileLines)
  while i < length:
    if not fileLines[i].strip():
      fileLines.pop(i)
      length -= 1
    i += 1

  #Parse the faultReports
  i = 0
  fileLineCount = len(fileLines)
  
  while (i < fileLineCount):
    if "#FaultReport" in fileLines[i]:
      temp = []
      temp.append(fileLines[i])
      i += 1
      while ("#FaultReport" not in fileLines[i]):
        temp.append(fileLines[i])
        i += 1
        if i >= fileLineCount:
          break
      reports.append(faultReport(temp))
    else:
      i += 1
    if i >= fileLineCount:
      break

  return reports