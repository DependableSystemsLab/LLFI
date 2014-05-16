import urllib2
import sys
import os
import subprocess
import hashlib

#Update These to change download targets
LLVM34DOWNLOAD = {'URL':"http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz", 
				'FILENAME':"llvm-3.4.src.tar.gz", 
				'MD5':"46ed668a1ce38985120dbf6344cf6116", 
				'EXTRACTPATH':"llvmsrc", 
				'EXTRACTEDNAME':'llvm-3.4',
				'ARCHIVETYPE':'.tar.gz',
				'EXTRACTFLAG':True,
				'DOWNLOADFLAG':True}
CLANG34DOWNLOAD = {'URL':"http://llvm.org/releases/3.4/clang-3.4.src.tar.gz", 
				 'FILENAME':"clang-3.4.src.tar.gz", 
				 'MD5':"b378f1e2c424e03289effc75268d3d2c", 
				 'EXTRACTPATH':"llvmsrc/tools/clang", 
				 'EXTRACTEDNAME':'clang-3.4',
				 'ARCHIVETYPE':'.tar.gz',
				 'EXTRACTFLAG':True,
				 'DOWNLOADFLAG':True}
PYAML311DOWNLOAD = {'URL':"http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz", 
				 'FILENAME':"PyYAML-3.11.tar.gz", 
				 'MD5':"f50e08ef0fe55178479d3a618efe21db", 
				 'EXTRACTPATH':"pyyamlsrc", 
				 'EXTRACTEDNAME':'PyYAML-3.11',
				 'ARCHIVETYPE':'.tar.gz',
				 'EXTRACTFLAG':True,
				 'DOWNLOADFLAG':True}
LLFIDOWNLOAD = {'URL':'https://github.com/scoult3r/LLFI/archive/master.zip', #"https://github.com/DependableSystemsLab/LLFI/archive/master.zip", 
				'FILENAME':"master.zip", 
				'MD5':"fc3ba3cfea7ae3236bf027b847058105", #"c9a8c3ffcbd033a4d3cf1dc9a25de09c" #You will have to change this outside of the git repo
				'EXTRACTPATH':"llfisrc", 													  #If you change this md5 within the repo, the md5 of the
				'EXTRACTEDNAME':'LLFI-master',           									  #repo will change
				'ARCHIVETYPE':'.zip',
				'EXTRACTFLAG':True,
				'DOWNLOADFLAG':True}
DOWNLOADTARGETS = [LLVM34DOWNLOAD, CLANG34DOWNLOAD, PYAML311DOWNLOAD, LLFIDOWNLOAD]
DOWNLOADSDIRECTORY = "./downloads/"
LLFIROOTDIRECTORY = "./llfi/"

def DownloadSources(targets, downloadDirectory):
	FullDownloadsPath = os.path.abspath(downloadDirectory)

	CheckAndCreateDir(FullDownloadsPath)
	for target in targets:
		if target["DOWNLOADFLAG"] == True:
			CheckAndDownload(target['FILENAME'], target['MD5'], target['URL'])

def CheckAndDownload(filename, md5, url):
	md5new = ""
	filepath = os.path.abspath("./downloads/" + filename)
	if os.path.isfile(filepath):
		print "Download target " + filename + " already exists."
		with open(filepath) as check:
			data = check.read()
			md5new = hashlib.md5(data).hexdigest()
		if md5 == md5new:
			print "MD5 Verified"
			return True
		else:
			print "MD5 does not match! Deleting File."
			subprocess.call(["rm", filepath])
	DownloadFile(url, "./downloads/")
	return True

def CheckAndCreateDir(dir):
	FullPath = os.path.abspath(dir)
	if (os.path.exists(FullPath)):
		if (os.path.isdir(FullPath)):
			print "%s directory exists." % (dir)
			return True
		else:
			print "%s path occupied by file, deleting..." % (dir)
			subprocess.call(["rm", FullPath])
	print "Creating %s directory." % (dir)
	subprocess.call(["mkdir", dir])	

def DownloadFile(url, destinationDirectory):
	filename = url.split('/')[-1]
	f = open(os.path.join(destinationDirectory, filename), 'wb')

	u = None
	meta = None
	file_size = None
	count = 0
	while file_size == None:
		try: 
			u = urllib2.urlopen(url, timeout=3)
		except urllib2.URLError, e:
			print "Unable to connect to " + url
			print "Please check your internet connection, or"
			print "update to latest version of LLFI installer."
			print "Exiting."
			sys.exit(0)
		meta = u.info()
		if len(meta.getheaders("Content-Length")) > 0: 
			file_size = int(meta.getheaders("Content-Length")[0])
		count = count + 1
		if count > 10:
			print "Downloading of " + url + "has timed out."
			print "Please check your internet connection, or"
			print "update to latest version of LLFI installer."
			print "Exiting."
			sys.exit(0)

	print "Downloading: %s: Bytes: %s" % (filename, file_size)
	file_size_dl = 0
	block_sz = 8192
	while True:
	    buffer = u.read(block_sz)
	    if not buffer:
	        break

	    file_size_dl += len(buffer)
	    f.write(buffer)
	    status = r"%10d  [%3.2f%%]" % (file_size_dl, file_size_dl * 100. / file_size)
	    status = status + chr(8)*(len(status)+1)
	    print status,

	f.close()
	sys.stdout.flush()
	print ""

def ExtractSources(targets, downloadsDirectory, extractionDirectory):
	fullDownloadsPath = os.path.abspath(downloadsDirectory)
	fullExtractionPath = os.path.abspath(extractionDirectory)
	CheckAndCreateDir(extractionDirectory)
	print "Moving to extraction root directory."
	os.chdir(extractionDirectory)
	for target in targets:
		if target["EXTRACTFLAG"] == True:
			path = target['EXTRACTPATH']
			dirName = target['EXTRACTEDNAME']
			print "Extracting " + target['FILENAME']
			archivePath = os.path.join(fullDownloadsPath, target['FILENAME'])
			if os.path.isfile(archivePath):
				ExtractArchive(target["ARCHIVETYPE"], archivePath)
				print "Renaming " + dirName + " to " + path
				CheckAndCreateDir(path)
				subprocess.call("cp -R " + dirName+"/* " + path, shell=True)
				subprocess.call(["rm", "-rf", dirName])
			os.chdir(fullExtractionPath)

def ExtractArchive(archiveType, archivePath):
	if archiveType == ".tar.gz":
		subprocess.call(["tar", "-xf", archivePath])
	if archiveType == ".zip":
		archivePath = archivePath[:-4]
		subprocess.call(["unzip", "-q", archivePath])

def UpdateFlags(targets, key, value):
	newList = []
	for target in targets:
		target[key] = value
		newList.append(target)
	return newList


if __name__ == "__main__":
	for arg in sys.argv[1:]:
		if arg in ("--version", "-v"):
			print "LLFI Installer Version 0.1"
			print "Last updated May 16th, 2014"
			sys.exit(0)
		if arg in ("--cleanDownloads", "-cD"):
			print "Cleaning downloads..."
			subprocess.call(["rm", "-rf", DOWNLOADSDIRECTORY])
			print "Done."
		if arg in ("--cleanSources", "-cS"):
			print "Cleaning extracted sources..."
			currPath = os.getcwd()
			if os.path.isdir(LLFIROOTDIRECTORY):
				os.chdir(LLFIROOTDIRECTORY)
				for target in DOWNLOADTARGETS:	
					subprocess.call(["rm", "-rf", target['EXTRACTPATH']])
				print "Done."
			os.chdir(currPath)
		if arg in ("--noDownload", "-nD"):
			print "Flag Set: Do not perform downloads."
			DOWNLOADTARGETS = UpdateFlags(DOWNLOADTARGETS, "DOWNLOADFLAG", False)
		if arg in ("--noExtract", "-nE"):
			print "Flag set: Do not extract downloaded files."
			DOWNLOADTARGETS = UpdateFlags(DOWNLOADTARGETS, "EXTRACTFLAG", False)
	DownloadSources(DOWNLOADTARGETS, DOWNLOADSDIRECTORY)
	ExtractSources(DOWNLOADTARGETS, DOWNLOADSDIRECTORY, LLFIROOTDIRECTORY)

