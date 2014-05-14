import urllib2
import sys
import os
import subprocess
import hashlib

#Input: 32/64bit, alternative download locations/options

#Copy LLFI files

#Download LLVM, Clang, etc

def DownloadSources():
	DownloadsPath = "./downloads"
	FullDownloadsPath = os.path.abspath(DownloadsPath)

	LLVMSRCURL = "http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz"
	CLANGSRCURL = "http://llvm.org/releases/3.4/clang-3.4.src.tar.gz"
	PYAMLSRCURL = "http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz"
	LLVMSRCFILENAME = "llvm-3.4.src.tar.gz"
	CLANGSRCFILENAME = "clang-3.4.src.tar.gz"
	PYAMLSRCFILENAME = "PyYAML-3.11.tar.gz"
	LLVMMD5 = "46ed668a1ce38985120dbf6344cf6116"
	CLANGMD5 = "b378f1e2c424e03289effc75268d3d2c"
	PYAMLMD5 = "f50e08ef0fe55178479d3a618efe21db"

	CheckAndCreateDownloadDir(DownloadsPath)
	CheckAndDownload(LLVMSRCFILENAME, LLVMMD5, LLVMSRCURL)
	CheckAndDownload(CLANGSRCFILENAME, CLANGMD5, CLANGSRCURL)
	CheckAndDownload(PYAMLSRCFILENAME, PYAMLMD5, PYAMLSRCURL)

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

if __name__ == "__main__":
	DownloadSources()
	
