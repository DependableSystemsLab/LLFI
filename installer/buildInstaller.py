import urllib2
import sys
import os
import subprocess
import hashlib

#Update These to change download targets
LLVMDOWNLOAD = {'URL':"http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz", 
				'FILENAME':"llvm-3.4.src.tar.gz", 
				'MD5':"46ed668a1ce38985120dbf6344cf6116", 
				'EXTRACTPATH':"llvmsrc", 
				'EXTRACTEDNAME':'llvm-3.4',
				'ARCHIVETYPE':'.tar.gz'}
CLANGDOWNLOAD = {'URL':"http://llvm.org/releases/3.4/clang-3.4.src.tar.gz", 
				 'FILENAME':"clang-3.4.src.tar.gz", 
				 'MD5':"b378f1e2c424e03289effc75268d3d2c", 
				 'EXTRACTPATH':"llvmsrc/tools/clang", 
				 'EXTRACTEDNAME':'clang-3.4',
				 'ARCHIVETYPE':'.tar.gz'}
PYAMLDOWNLOAD = {'URL':"http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz", 
				 'FILENAME':"PyYAML-3.11.tar.gz", 
				 'MD5':"f50e08ef0fe55178479d3a618efe21db", 
				 'EXTRACTPATH':"pyamlsrc", 
				 'EXTRACTEDNAME':'PyYAML-3.11',
				 'ARCHIVETYPE':'.tar.gz'}
LLFIDOWNLOAD = {'URL':'https://github.com/scoult3r/LLFI/archive/master.zip', #"https://github.com/DependableSystemsLab/LLFI/archive/master.zip", 
				'FILENAME':"master.zip", 
				'MD5':"fc3ba3cfea7ae3236bf027b847058105", #"c9a8c3ffcbd033a4d3cf1dc9a25de09c"
				'EXTRACTPATH':"llfisrc", 
				'EXTRACTEDNAME':'LLFI-master',
				'ARCHIVETYPE':'.zip'}
DOWNLOADTARGETS = (LLVMDOWNLOAD, CLANGDOWNLOAD, PYAMLDOWNLOAD, LLFIDOWNLOAD)
DOWNLOADSDIRECTORY = "./downloads/"
LLFIROOTDIRECTORY = "./llfi/"

def DownloadSources(targets, downloadDirectory):
	FullDownloadsPath = os.path.abspath(downloadDirectory)

	CheckAndCreateDir(FullDownloadsPath)
	for target in targets:
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
	u = urllib2.urlopen(url)
	f = open(os.path.join(destinationDirectory, filename), 'wb')
	meta = u.info()
	file_size = int(meta.getheaders("Content-Length")[0])
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
	print "Moving to extraction root directory."
	os.chdir(extractionDirectory)
	for target in targets:
		path = target['EXTRACTPATH']
		dirName = target['EXTRACTEDNAME']
		print "Extracting " + target['FILENAME']
		archivePath = os.path.join(fullDownloadsPath, target['FILENAME'])
		ExtractArchive(target, archivePath)
		print "Renaming " + dirName + " to " + path
		subprocess.call(["mv", dirName, path])
		os.chdir(fullExtractionPath)

def ExtractArchive(target, archivePath):
	if target['ARCHIVETYPE'] == ".tar.gz":
		subprocess.call(["tar", "-xf", archivePath])
	if target['ARCHIVETYPE'] == ".zip":
		archivePath = archivePath[:-4]
		subprocess.call(["unzip", archivePath])


def CopyLLFI():
	print ""

if __name__ == "__main__":
	if len(sys.argv) == 1:
		DownloadSources(DOWNLOADTARGETS, DOWNLOADSDIRECTORY)
		ExtractSources(DOWNLOADTARGETS, DOWNLOADSDIRECTORY, LLFIROOTDIRECTORY)
		CopyLLFI()
	else:
		for arg in sys.argv[1:]:
			if arg in ("-cleanDownloads", "-cD"):
				print "Cleaning downloads..."
				subprocess.call(["rm", "-rf", DOWNLOADSDIRECTORY])
				print "Done."
			if arg in ("-cleanSources", "-cS"):
				print "Cleaning extracted sources..."
				os.chdir(LLFIROOTDIRECTORY)
				for target in DOWNLOADTARGETS:	
					subprocess.call(["rm", "-rf", target['EXTRACTPATH']])
				print "Done."
	
