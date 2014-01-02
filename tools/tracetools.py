#!/usr/bin/env python2

#traceTools.py
#Author: Sam Coulter
#This file contains library functions and classes for the llfi tracing and
#tracing analyses scripts

import sys
import os
import glob
import itertools
import difflib


debugFlag = 0

def debug(text, level=5):
  global debugFlag
  if debugFlag == level:
    print text

goldenRemovedCount = []
faultyRemovedCount = []

class diffBlock:
  def __init__(self, lines):

    debug("\n\tCreating a diffBlock")

    origHeader, newHeader = lines[0].replace('@',' ').replace('+',' ').replace('-',' ').split()
    origsplit = origHeader.split(',')
    newsplit = newHeader.split(',')
    self.origStart = int(origsplit[0])
    self.newStart = int(newsplit[0])

    self.preDiff = None
    self.postDiff = None

    self.origLines = []
    self.newLines = []

    if "+" not in lines[1] and "-" not in lines[1]:
      if "S" in lines[1]: #See ugly hack in the diffReport init
        lines[1] = lines[1][2:]
      self.preDiff = lines.pop(1)
      self.origStart += 1
      self.newStart += 1

    if "+" not in lines[-1] and "-" not in lines[-1]:
      self.postDiff = lines.pop(len(lines)-1)

    for line in lines[1:]:
      if "-" in line:
        self.origLines.append(line)
      if "+" in line:
        self.newLines.append(line)

    debug("\tDiffblock lines")
    debug("\t" + "\n\t".join(lines))

    self.origLength = len(self.origLines)
    self.newLength = len(self.newLines)

    debug("\t" + "\n\t".join(self.origLines))
    debug("\t" + "\n\t".join(self.newLines))

  #print some info for debugging
  def printdebug(self):
    print self.origStart, self.newStart
    print '\n'.join(self.origLines)
    print '\n'.join(self.newLines)

  #print the block analysis summary
  def getSummary(self, adj=0):
    origStart = self.origStart + adj
    newStart = self.newStart + adj
    DataDiffs = []
    CtrlDiffs = []
    instanceList = []

    izip = itertools.izip_longest(self.origLines, self.newLines)

    instance = diffInstance(0,0,0,0)
    for i, (g, f) in enumerate(izip):
      g = diffLine(g)
      f = diffLine(f)
      if g and f:
        if g.ID == f.ID:
          if instance.type != 1:
            if (instance.summary != None):
              instanceList.append(instance.summary())
            instance = diffInstance(1, findAdjustedPosition(origStart, goldenRemovedCount), \
              findAdjustedPosition(newStart, faultyRemovedCount), i)
          instance.add("Data Diff: ID: " + str(g.ID) + " OPCode: " + str(g.OPCode) + \
           " Value: " + str(g.Value) + " \\ " + str(f.Value))
          instance.incOrigLength()
          instance.incNewLength()
    if (instance.summary != None):
      instanceList.append(instance.summary())
    return instanceList[1]

class ctrlDiffBlock(diffBlock):
  def getRange(self):
    debug("Printing ctrlDiffBlock Range")
    debug(str(self.origStart) + " " + str(self.origLength) + " " + str(self.newStart) + " " + str(self.newLength))
    return self.origStart, self.origLength, \
    self.newStart, self.newLength

  def getSummary(self, adj=0):
    origStart = self.origStart + adj
    newStart = self.newStart + adj
    DataDiffs = []
    CtrlDiffs = []
    instanceList = []

    debug("ctrlDiffBlock getSummaryCall: " + str(adj))

    izip = itertools.izip_longest(self.origLines, self.newLines)

    instance = diffInstance(0,0,0,0)
    for i, (g, f) in enumerate(izip):
      if g and f:
        if instance.type != 2:
          if (instance.summary != None):
            instanceList.append(instance.summary(self.preDiff, self.postDiff))
          instance = diffInstance(2, origStart, newStart, i)
        instance.add("Ctrl Diff: ID: " + str(g[1:]) + " \\ " + str(f[1:]))
        instance.incOrigLength()
        instance.incNewLength()
      if g and not f:
        if instance.type != 2:
            if (instance.summary != None):
              instanceList.append(instance.summary(self.preDiff, self.postDiff))
            instance = diffInstance(2, origStart, newStart, i)
        instance.add("Ctrl Diff: ID: " + str(g[1:]) + " \\ None")
        instance.incOrigLength()
      if f and not g:
        if instance.type != 2:
            if (instance.summary != None):
              instanceList.append(instance.summary(self.preDiff, self.postDiff))
            instance = diffInstance(2, origStart, newStart, i)
        instance.add("Ctrl Diff: ID: " + "None \\ " + str(f[1:]))
        instance.incNewLength()
    if (instance.summary != None):
      instanceList.append(instance.summary(self.preDiff, self.postDiff))
    return instanceList[1]

def removeRangeFromLines(goldenLines, faultyLines, (gStart, gLength, fStart, fLength), adj = 0):
  global goldenRemovedCount
  global faultyRemovedCount

  debug("\n\nRemovingRangeFromLines()")

  i = 0
  debug("GLen "+ str(gLength))
  debug("GStart " + str(gStart))
  while (i < gLength):
    goldenLines[gStart+i-1] = ""
    i += 1
    debug(str(i))
  goldenRemovedCount.append((gStart + adj, gLength))
  i = 0
  debug("FLen " +str(fLength))
  debug("FStart " + str(fStart))
  debug("FLines")
  debug("\n".join(faultyLines))
  while (i < fLength):
    faultyLines[fStart+i-1] = ""
    i += 1
    debug(str(i))
  faultyRemovedCount.append((fStart + adj, fLength))
  debug("\nGolden after removal::::")
  debug('\n'.join(goldenLines))
  debug("\nFaulty After removal::::")
  debug('\n'.join(faultyLines))
  return goldenLines, faultyLines

def findAdjustedPosition(position, remArray):
  i = 0
  while i < len(remArray):
    location, count = remArray[i]
    if position >= location:
      position = position + count
    else:
      return position
    i += 1
  return position


class diffInstance:
  def __init__(self, insttype, origstart, newstart, adj):
    debug("\t\tCreating a diffInstance")
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

  def summary(self, preDiff=None, postDiff=None):
    if len(self.lines) > 0:
      self.origEnd = self.origStart + self.origLength
      self.newEnd = self.newStart + self.newLength
      header = "\nDiff@ inst # " + str(self.origStart) + "\\" + str(self.newStart) \
      + " -> inst # " + str(self.origEnd) + "\\" + str(self.newEnd) + "\n"
      if preDiff != None:
        header += "Pre  Diff: ID: "  + str(preDiff) + "\n"
      if postDiff != None:
        final = header + '\n'.join(self.lines) + "\nPost Diff: ID:" + postDiff
      else:
        final = header + '\n'.join(self.lines)
      return final
    else:
      return None

  def incOrigLength(self):
    self.origLength += 1

  def incNewLength(self):
    self.newLength += 1


class diffReport:
  def __init__(self, goldenLines, faultyLines, startPoint, injectedID):
    self.injectedID = injectedID
    debug("Starting a diffReport, startpoint = " + str(startPoint))
    self.startPoint = startPoint
    self.blocks = []

    #perform ctrl diff analysis
    goldenIDs = goldenLines[:]
    faultyIDs = faultyLines[:]
    goldenIDs = trimLinesToCtrlIDs(goldenIDs)
    faultyIDs = trimLinesToCtrlIDs(faultyIDs)

    #This ugly hack forces the difflib routine to prioritize certain ctrl flow matches.
# TODO: the fundamental problem here is unix diff is not greedy
# so we might need to come up with a comprehensive fix
# The hack might not always work. Jiesheng

    i = 0
    while i < len(goldenIDs):
      if i < len(faultyIDs) and goldenIDs[i] == faultyIDs[i]:
        goldenIDs[i] = "S" + goldenIDs[i]
        faultyIDs[i] = "S" + faultyIDs[i]
      else:
        break
      i += 1

    ctrldiff = list(difflib.unified_diff(goldenIDs[:], faultyIDs[:], n=1, lineterm=''))

    if ctrldiff:
      ctrldiff.pop(0)
      ctrldiff.pop(0)

      debug("\n".join(ctrldiff))
      debug("Length = " + str(len(ctrldiff)))

      i = 0
      length = 1
      start = None

      while (i < len(ctrldiff)):
        if "@@ " in ctrldiff[i]:
          if start != None:
            debug("Calling ctrlDiffBlock constructor " + str(start) + " " + str(length))
            debug("\n".join(ctrldiff[start:start+length]))
            cblock = ctrlDiffBlock(ctrldiff[start:start+length])
            self.blocks.append(cblock)
            length = 1
          start = i
        else:
          length += 1
        i += 1
      #Dont forget the last block in the diff!
      if start != None:
        debug("Calling ctrlDiffBlock constructor " + str(start) + " " + str(length))
        debug("\n".join(ctrldiff[start:start+length]))
        cblock = ctrlDiffBlock(ctrldiff[start:start+length])
        self.blocks.append(cblock)

      debug("Golden Lines:\n" + "\n".join(goldenLines))
      debug("Faulty Lines:\n" + "\n".join(faultyLines))

      debug("Removing ctrldiff ranges from lines")
      for block in self.blocks:
        goldenLines, faultyLines = removeRangeFromLines(goldenLines, faultyLines, \
          block.getRange(), self.startPoint)
        debug("Golden Lines:\n" + "\n".join(goldenLines))
        debug("Faulty Lines:\n" + "\n".join(faultyLines))

      goldenLines = filter(None, goldenLines)
      faultyLines = filter(None, faultyLines)


    datadiff = list(difflib.unified_diff(goldenLines, faultyLines, n=0, lineterm=''))

    if datadiff:
      datadiff.pop(0)
      datadiff.pop(0)

      #perform data diff analysis
      i = 0
      length = 1
      start = None

      while (i < len(datadiff)):
        if "@@ " in datadiff[i]:
          if start != None:
            self.blocks.append(diffBlock(datadiff[start:start+length]))
            length = 1
          start = i
        else:
          length += 1
        i += 1
      #Dont forget the last block in the diff!
      if start != None:
        self.blocks.append(diffBlock(datadiff[start:start+length]))


  def printSummary(self):
    #Sort the list of blocks by their starting point (wrt the golden trace)
    self.blocks.sort(key = lambda x: (x.getSummary(self.startPoint)).split("\n")[1].replace('\\',' ').split()[3])

    for block in self.blocks:
      if block.preDiff == None:
        block.preDiff = self.injectedID
      print block.getSummary(self.startPoint)

def trimLinesToCtrlIDs(lines):
  i = 0
  while (i < len(lines)):
    words = lines[i].split()
    lines[i] = words[1]
    i += 1
  return lines



class diffLine:
  def __init__(self, rawLine):
    self.raw = rawLine
    elements = str(rawLine).split()
    #ID: 14\tOPCode: sub\tValue: 1336d337
    debug("RAWLINE: " + str(rawLine), 3)
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
      if "Diff@" in self.diffs[i] and "Pre  Diff" in self.diffs[i+1]:
        csplit = self.diffs[i+2].split()
        edgeStart = int(self.diffs[i+1].split()[3])
        if csplit[5] != "None":
          edgeEnd = int(csplit[5])
          if (i+3 < len(self.diffs)):
            affectedEdges.add((edgeEnd, int(self.diffs[i+3].split()[5])))
        else:
          d = i + 2 #Adjusting so we dont check the find the pre diff of the diff@ instance we
                    #are currently on.
          while d < len(self.diffs):
            if "Post Diff" in self.diffs[d]:
              edgeEnd = self.diffs[d].split()[3]
              d = len(self.diffs)
            elif "Pre  Diff" in self.diffs[d]:
              d = len(self.diffs) #If we found a new ctrl diff block before finding a post diff,  
                                  #exit the loop early
            d += 1
        affectedEdges.add((edgeStart, edgeEnd))
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
