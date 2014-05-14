import urllib2
import sys
import os
import subprocess
import hashlib

#Update These to change download targets
LLVMDOWNLOAD = {'URL':"http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz", \
				'FILENAME':"llvm-3.4.src.tar.gz", \
				'MD5':"46ed668a1ce38985120dbf6344cf6116" }
CLANGDOWNLOAD = {'URL':"http://llvm.org/releases/3.4/clang-3.4.src.tar.gz", \
				 'FILENAME':"clang-3.4.src.tar.gz", \
				 'MD5':"b378f1e2c424e03289effc75268d3d2c" }
PYAMLDOWNLOAD = {'URL':"http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz", \
				 'FILENAME':"PyYAML-3.11.tar.gz", \
				 'MD5':"f50e08ef0fe55178479d3a618efe21db" }
DOWNLOADTARGETS = (LLVMDOWNLOAD, CLANGDOWNLOAD, PYAMLDOWNLOAD)
DOWNLOADSDIRECTORY = "./downloads"

def DownloadSources():
	DownloadsPath = DOWNLOADSDIRECTORY
	FullDownloadsPath = os.path.abspath(DownloadsPath)

	CheckAndCreateDownloadDir(DownloadsPath)
	for target in DOWNLOADTARGETS:
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

def CheckAndCreateDownloadDir(dir):
	FullPath = os.path.abspath(dir)
	if (os.path.exists(FullPath)):
		if (os.path.isdir(FullPath)):
			print "Downloads directory exists."
			return True
		else:
			print "Downloads path occupied by file, deleting..."
			subprocess.call(["rm", FullPath])
	print "Creating downloads directory."
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

def ExtractSources():
	print ""

def CopyLLFI():
	print ""

if __name__ == "__main__":
	DownloadSources()
	ExtractSources()
	CopyLLFI()
	
