#traceTools.py
#Author: Sam Coulter
#This file contains library functions and classes for the llfi tracing and
#tracing analyses scripts

import sys
import os
import glob

class faultReport:
	def __init__(self, lines):
		self.instNumber = -1
		self.faultFlows = []
		self.faultCount = -1
		self.faultID = -1
		self.faultOPCode = ''
		self.goldValue = -1
		self.faultValues = []

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

			for i in range(self.faultCount):
				self.faultFlows.append(lines[3+i])
		else:
			print "ERROR: Not a properly formed faultReport"

	def union(self, other):
		if self.instNumber == other.instNumber:
			self.faultCount += other.faultCount
			self.faultFlows.extend(other.faultFlows)
			self.faultValues.extend(other.faultValues)

	def report(self):
		lines = []
		lines.append("#FaultReport")
		header = str(self.faultCount) + " @ " + str(self.instNumber)
		lines.append(header)
		faultline = "ID: " + str(self.faultID) + " OPCode: " + str(self.faultOPCode)
		faultline += " Value: " + str(self.goldValue) + " / "
		for val in self.faultValues:
			faultline += " " + str(val)
		lines.append(faultline)
		lines.extend(self.faultFlows)
		return '\n'.join(lines)


def parseFaultReportsfromFile(target):
	reports = []
	reportFile = open(target, 'r')
	fileLines = reportFile.readlines()

	#Remove blank lines from file
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
		temp = []
		if "#FaultReport" in fileLines[i]:
			temp.append(fileLines[i])
			i += 1
			while (fileLines[i] != "#FaultReport"):
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