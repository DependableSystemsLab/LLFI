#!/usr/bin/python

#traceDiff.py
#	Author: Sam Coulter
#	This python script is part of the greater LLFI system.
#	This script will examine two tracing output files generated by running a program after
#	the LLFI traceInst pass has been performed.
# 	Exec: traceDiff.py goldenTrace faultyTrace
#	Input: GoldenTrace/faultyTrace - Trace output files after running a traced program
#	Output: Trace Summary into Standard output, redirect with PIPE to save to file


import sys
import subprocess
import glob

class diffBlock:
	def __init__(self, header, start):
		#Split the block (diff) header into parts and store
		#eg 10,15c13,18
		origHeader, newHeader = header.replace('a','c').replace('d','c').split('c')
		origsplit = origHeader.split(',')
		newsplit = newHeader.split(',')
		self.origStart = int(origsplit[0]) + start
		if (len(origsplit) > 1):
			self.origEnd =  int(origsplit[1]) + start
		else:
			self.origEnd = self.origStart
		self.newStart = int(newsplit[0]) + start
		if (len(newsplit) > 1):
			self.newEnd = int(newsplit[1]) + start
		else:
			self.newEnd = self.newStart
		self.origLength = int(self.origEnd) - int(self.origStart) + 1
		self.newLength = int(self.newEnd) - int(self.newStart) + 1

		self.origLines = []
		self.newLines = []

		self.start = start

	#print some info for debugging
	def printdebug(self):
		print self.origStart, "to", self.origEnd, "length", self.origLength
		for line in self.origLines:
			line.printself()
		print self.newStart, "to", self.newEnd, "length", self.newLength
		for line in self.newLines:
			line.printself()

	#print the block analysis summary
	def printSummary(self):
		status = "Control Difference"
		
		if self.newLines and self.origLines:
			firstNewLine = self.newLines[0]
			lastNewLine =  self.newLines[len(self.newLines)-1]
			firstOrigLine = self.origLines[0]
			lastOrigLine = self.origLines[len(self.origLines)-1]
			
			if (self.origLength != self.newLength):
				status = "Control Difference"
			else:
				for oline, nline in zip(self.origLines, self.newLines):
					if (oline.ID == nline.ID) and (oline.OPCode == nline.OPCode):
						status = "Data Difference"
					elif (oline.ID != nline.ID) or (oline.OPCode != nline.OPCode):
						status = "Control Difference"
						break
			assert (status != 0), "Control/Data Difference evaluation Error"
			print status, "detected at:" 
			print "    Golden Inst Number:", self.origStart, "ID:", firstOrigLine.ID, \
					"OPCode:", firstOrigLine.OPCode, "Value:", firstOrigLine.Value
			print "    Faulty Inst Number:", self.newStart, "ID:", firstNewLine.ID, \
					"OPCode:", firstNewLine.OPCode, "Value:", firstNewLine.Value
			if (self.origLength != self.newLength) or (self.origLength > 1):
				print "    Trace re-aligns after:   (", \
				self.origLength-1, "/", self.newLength-1, " instructions later)"
				print "      Golden Inst Number:", self.origEnd, \
						"ID:", lastOrigLine.ID, \
						"OPCode:", lastOrigLine.OPCode, \
						"Value:", lastOrigLine.Value
				print "      Faulty Inst Number:", self.newEnd, \
						"ID:", lastNewLine.ID, \
						"OPCode:", lastNewLine.OPCode, \
						"Value:", lastNewLine.Value
			else:
				print "    Trace re-aligns immediately"

		elif self.newLines:
			firstNewLine = self.newLines[0]
			lastNewLine =  self.newLines[len(self.newLines)-1]
			print "Control Difference detected at:"
			print "    New Instructions after Golden Inst Number:", self.origStart
			print "    Faulty Inst Number:", self.newStart, "ID:", firstNewLine.ID, \
					"OPCode:", firstNewLine.OPCode, "Value:", firstNewLine.Value
			print "    Trace re-aligns after:   (", \
				self.origLength-1, "/", self.newLength-1, " instructions later)"
			print "      Faulty Inst Number:", self.newEnd, \
						"ID:", lastNewLine.ID, \
						"OPCode:", lastNewLine.OPCode, \
						"Value:", lastNewLine.Value

		elif self.origLines:
			firstOrigLine = self.origLines[0]
			lastOrigLine = self.origLines[len(self.origLines)-1]
			print "Control Difference detected at:"
			print "    Instructions missing after Faulty Inst Number:", self.newStart
			print "    Golden Inst Number:", self.origStart, "ID:", firstOrigLine.ID, \
					"OPCode:", firstOrigLine.OPCode, "Value:", firstOrigLine.Value
			print "    Trace re-aligns after:   (", \
				self.origLength-1, "/", self.newLength-1, " instructions later)"
			print "      Golden Inst Number:", self.origEnd, \
						"ID:", lastOrigLine.ID, \
						"OPCode:", lastOrigLine.OPCode, \
						"Value:", lastOrigLine.Value

class diffLine:
	def __init__(self, rawLine):
		elements = str(rawLine).split()
		assert (elements[1] == "ID" && elements[3] == "OPCode:" &&  \
			elements[5] == "Value:"), "DiffLine constructor called incorrectly"
		self.ID = int(elements[2])
		self.OPCode = str(elements[4])
		self.Value = str(elements[6])

	def printself(self):
		print self.ID, self.OPCode, self.Value

def traceDiff(argv, output = 0):
	if output != 0:
		sys.stdout = open(output, "w")
	if (len(argv) != 3):
		print "Uh Oh, something broke! argv!=3"
		exit(1)

	origFile = open(argv[1], 'r')
	origTrace = origFile.read()
	origFile.close()

	newFile = open(argv[2], 'r')
	newTrace = newFile.read()
	newFile.close()

	origTraceLines = origTrace.split("\n")
	newTraceLines =  newTrace.split("\n")

	newTraceStartPoint = int(newTraceLines[0][39:])
	newTraceLines.pop(0)
	for i in range (0,newTraceStartPoint-1):
		origTraceLines.pop(0)

	origFile = open("TempOrigFile", 'w')
	for line in origTraceLines:
		origFile.write(line)
		origFile.write("\n")
	origFile.close();

	newFile = open("TempNewFile", 'w')
	for line in newTraceLines:
		newFile.write(line)
		newFile.write("\n")
	newFile.close()

	diffProcess = subprocess.Popen(["diff","TempOrigFile","TempNewFile"], stdout=subprocess.PIPE)
	(diffOutput,diffErr) = diffProcess.communicate()
	diffProcess.wait()
	if (diffErr):
		print "diff encountered an error, exiting traceDiff"
		print diffErr
		exit(1)
	else:
		print "diff Succesful on", argv[1],argv[2]


	p = subprocess.Popen(["rm", "TempOrigFile", "TempNewFile"])
	diffProcess.wait()


	lines = diffOutput.split("\n")

	for i in range(0, len(lines)-1):
		if (len(lines[i]) != 0) and (lines[i][0] not in ['<','>','-','#']):
			#print "found a block header"
			#print lines[i]
			block = diffBlock(lines[i], newTraceStartPoint)
			i = i + 1
			while ((len(lines[i]) != 0) and (lines[i][0] in ['<','>','-','#'])):
				if (lines[i][0] == '-'):
					i = i + 1
					continue
				if (lines[i][0] == '<'):
					block.origLines.append(diffLine(lines[i]))
				if (lines[i][0] == '>'):
					block.newLines.append(diffLine(lines[i]))
				i = i + 1
			block.printSummary()

if (__name__ == "__main__"):
	traceDiff(sys.argv)