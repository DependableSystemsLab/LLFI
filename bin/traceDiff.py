#!/usr/bin/python

#Run Diff on the two outputs

#Collect every difference block
	#Identify whether block is control or data different
	#report block beginning ID 
	#give some stats about block difference?

#p = subprocess.Popen("date", stdout=subprocess.PIPE, shell=True)
#(output, err) = p.communicate()
#print "Today is", output

import sys
import subprocess

def traceDiff(argv):
	if (len(argv) != 3):
		print "Uh Oh, something broke! argv!=3"
	print str(argv)


if (__name__ == "__main__"):
	traceDiff(sys.argv)