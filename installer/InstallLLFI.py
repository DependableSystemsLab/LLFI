

from __future__ import ( division, absolute_import, print_function, unicode_literals )
import sys, os, tempfile, logging
if sys.version_info >= (3,):
    import urllib.request as urllib2
    import urllib.parse as urlparse
else:
    import urllib2
    import urlparse
import subprocess
import hashlib
import imp
import site
import xml.etree.ElementTree as ET
import argparse

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

#LLVM33 Targets:
LLVM33DOWNLOAD = {'URL':"http://llvm.org/releases/3.3/llvm-3.3.src.tar.gz", 
				'FILENAME':"llvm-3.3.src.tar.gz", 
				'MD5':"40564e1dc390f9844f1711c08b08e391", 
				'EXTRACTPATH':"llvmsrc", 
				'EXTRACTEDNAME':'llvm-3.3.src',
				'ARCHIVETYPE':'.tar.gz',
				'EXTRACTFLAG':True,
				'DOWNLOADFLAG':True}
CLANG33DOWNLOAD = {'URL':"http://llvm.org/releases/3.3/cfe-3.3.src.tar.gz", 
				 'FILENAME':"cfe-3.3.src.tar.gz", 
				 'MD5':"8284891e3e311829b8e44ac813d0c9ef", 
				 'EXTRACTPATH':"llvmsrc/tools/clang", 
				 'EXTRACTEDNAME':'cfe-3.3.src',
				 'ARCHIVETYPE':'.tar.gz',
				 'EXTRACTFLAG':True,
				 'DOWNLOADFLAG':True}
#Primary Repository LLFI
LLFIPUBLICDOWNLOAD = {'URL':'https://github.com/DependableSystemsLab/LLFI/archive/master.zip', 
					  'FILENAME':"master.zip", 
					  'MD5':"fc3ba3cfea7ae3236bf027b847058105",
					  'EXTRACTPATH':"llfisrc", 					
					  'EXTRACTEDNAME':'LLFI-master',           	
					  'ARCHIVETYPE':'.zip',
					  'EXTRACTFLAG':True,
					  'DOWNLOADFLAG':True}

DOWNLOADTARGETS = [LLVM34DOWNLOAD, CLANG34DOWNLOAD, PYAML311DOWNLOAD, LLFIDOWNLOAD]
DOWNLOADSDIRECTORY = "./downloads/"
LLFIROOTDIRECTORY = "."

def Touch(path):
    with open(path, 'a'):
        os.utime(path, None)

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
		print("Download target " + filename + " already exists.")
		with open(filepath) as check:
			data = check.read()
			md5new = hashlib.md5(data).hexdigest()
		if md5 == md5new:
			print("MD5 Verified")
			return True
		else:
			print("MD5 does not match! Deleting File.")
			subprocess.call(["rm", filepath])
	DownloadFile(url, "./downloads/")
	return True

def CheckAndCreateDir(dir):
	FullPath = os.path.abspath(dir)
	if (os.path.exists(FullPath)):
		if (os.path.isdir(FullPath)):
			print("%s directory exists." % (dir))
			return True
		else:
			print("%s path occupied by file, deleting..." % (dir))
			subprocess.call(["rm", FullPath])
	print("Creating %s directory." % (dir))
	subprocess.call(["mkdir", dir])
	return False

def DownloadFile(url, destinationDirectory, desc=None):
    u = urllib2.urlopen(url)

    scheme, netloc, path, query, fragment = urlparse.urlsplit(url)
    filename = os.path.basename(path)
    if not filename:
        filename = 'downloaded.file'
    if desc:
        filename = os.path.join(desc, filename)

    with open(os.path.join(destinationDirectory, filename), 'wb') as f:
        meta = u.info()
        meta_func = meta.getheaders if hasattr(meta, 'getheaders') else meta.get_all
        meta_length = meta_func("Content-Length")
        file_size = None
        if meta_length:
            file_size = int(meta_length[0])
        print("Downloading: {0} Bytes: {1}".format(url, file_size))

        file_size_dl = 0
        block_sz = 8192
        while True:
            buffer = u.read(block_sz)
            if not buffer:
                break

            file_size_dl += len(buffer)
            f.write(buffer)

            status = "{0:16}".format(file_size_dl)
            if file_size:
                status += "   [{0:6.2f}%]".format(file_size_dl * 100 / file_size)
            status += chr(13)
            print(status, end="")
        print()

    return filename

def ExtractSources(targets, downloadsDirectory, extractionDirectory):
	fullDownloadsPath = os.path.abspath(downloadsDirectory)
	fullExtractionPath = os.path.abspath(extractionDirectory)
	CheckAndCreateDir(extractionDirectory)
	print("Moving to extraction root directory.")
	os.chdir(extractionDirectory)
	for target in targets:
		if target["EXTRACTFLAG"] == True:
			path = target['EXTRACTPATH']
			dirName = target['EXTRACTEDNAME']
			print("Extracting " + target['FILENAME'])
			archivePath = os.path.join(fullDownloadsPath, target['FILENAME'])
			if os.path.isfile(archivePath):
				ExtractArchive(target["ARCHIVETYPE"], archivePath)
				print("Renaming " + dirName + " to " + path)
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

def build(buildLLVM, forceMakeLLVM):
	#Build LLVM
	if buildLLVM:
		CheckAndCreateDir("llvm")
		os.chdir("llvm")
		if (not os.path.exists("CMAKESUCCESS")) or forceMakeLLVM:
			print("Running cmake for LLVM:")
			p = subprocess.call(["cmake", "../llvmsrc", "-DLLVM_REQUIRES_RTTI=1", "-DCMAKE_BUILD_TYPE=Release"])
			if p != 0:
				sys.exit(p)
			Touch("CMAKESUCCESS")

		if (not os.path.exists("MAKESUCCESS")) or forceMakeLLVM:
			print("Running make for LLVM")
			p = subprocess.call("make")
			if p != 0:
				sys.exit(p)
			Touch("MAKESUCCESS")

		os.chdir("..")

	script_path = os.getcwd()
	#Configure and Build LLFI

	llvm_paths_cmake = os.path.join(script_path, "llfisrc/config/llvm_paths.cmake")
	llvm_paths_py = os.path.join(script_path, "llfisrc/config/llvm_paths.py")

	cmake_File = open(llvm_paths_cmake, "w")
	LLVM_DST_ROOT = os.path.realpath("llvm")
	LLVM_SRC_ROOT = os.path.realpath("llvmsrc")
	LLVM_GXX_BIN_DIR = os.path.realpath("llvm/bin")

	cmake_File.write("set(LLVM_DST_ROOT " + LLVM_DST_ROOT + ")\n")
	cmake_File.write("set(LLVM_SRC_ROOT " + LLVM_SRC_ROOT + ")\n")
	cmake_File.close()

	py_File = open(llvm_paths_py, "w")
	py_File.write("LLVM_DST_ROOT = " + '"' + LLVM_DST_ROOT + '"\n')
	py_File.write("LLVM_SRC_ROOT = " + '"' + LLVM_SRC_ROOT + '"\n')
	py_File.write("LLVM_GXX_BIN_DIR = " + '"' + LLVM_GXX_BIN_DIR + '"\n')
	py_File.close()

	CheckAndCreateDir("llfi")
	os.chdir("llfi")
	print("Running cmake for LLFI:")
	p = subprocess.call(["cmake", "../llfisrc"])
	if p != 0:
		sys.exit(p)

	print("Running make for LLFI:")
	p = subprocess.call("make")
	if p != 0:
		sys.exit(p)
	os.chdir("..")

	#Build LLFI GUI
	updateGUIXMLBuildPath(getJavaFXLibLocation())
	currPath = os.getcwd()
	antPath = os.path.join(currPath, "llfisrc/Gui_SourceCode/LLFI/build.xml")
	binPath = os.path.join(currPath, "llfisrc/Gui_SourceCode/LLFI/bin")
	jarPath = os.path.join(currPath, "llfisrc/LLFI-GUI/llfi_gui.jar")
	CheckAndCreateDir("llfisrc/LLFI-GUI")
	p = subprocess.call("cp llfisrc/LLFI-GUI/* llfi/LLFI-GUI/", shell=True)
	p = subprocess.call(["rm", "-rf", jarPath])
	p = subprocess.call(["rm", "-rf", binPath])
	p = subprocess.call(["ant", "-f", antPath ], env=os.environ)
	p = subprocess.call(["ant", "-f", antPath, "jar" ], env=os.environ)

	subprocess.call(["cp", "llfisrc/installer/LLFI-GUI", "."])

def buildPyYaml(forceBuild):
	script_path = os.getcwd()
	pyyaml_path = os.path.join(script_path,"pyyaml")
	os.chdir("pyyamlsrc")

	if (not os.path.exists('YAMLBUILDSUCCESS')) or forceBuild:
		p = subprocess.call(["python3","setup.py","install","--prefix="+pyyaml_path])
		if p != 0:
			sys.exit(p)
		Touch("YAMLBUILDSUCCESS")

	os.chdir("..")

def updateGUIXMLBuildPath(newPath):
	print("Modifying LLFI-GUI build.xml")
	tree = ET.parse('llfisrc/Gui_SourceCode/LLFI/build.xml')
	root = tree.getroot()
	pathnode = root.findall("./path[@id='JavaFX SDK.libraryclasspath']/pathelement")

	for path in root.iter('path'):
		if path.get('id') == "JavaFX SDK.libraryclasspath":
			pathelement = path.find('./pathelement[@location]')
			pathelement.set("location", newPath + "jfxrt.jar")
			
	for path in root.iter('target'):
		if path.get('name') == "jar":
			buildelement = path.find('./jar[@destfile]')
			buildelement.set("destfile", "../../../llfi/LLFI-GUI/llfi_gui.jar")

	for target in root.iter('target'):
		if target.get('name') == "jar":
			element = target.find("./jar/zipfileset[@includes='jfxrt.jar']")
			element.set("dir", newPath)
	tree.write('llfisrc/Gui_SourceCode/LLFI/build.xml')		


def getJavaFXLibLocation():
	uname = subprocess.check_output("uname").strip()
	javaLibPath = 1
	if 'Darwin' in str(uname):
		javahome = subprocess.check_output(["/usr/libexec/java_home", "-v", "1.7"], universal_newlines=True).strip()
		javaLibPath = javahome+"/jre/lib/"
	else:
		javaBinPath = subprocess.check_output("readlink -f $(which java)", shell=True, universal_newlines=True)
		javaBinPath = javaBinPath.strip()
		pathSplit = javaBinPath.split("/")
		if (str('jre') in [str(x) for x in pathSplit]):
			javaLibPath = javaBinPath[:-9] + "/lib/"
		else:
			javaLibPath = javaBinPath[:-9] + "/jre/lib/"
	print("Detecting JFX Lib at " + str(javaLibPath))
	return javaLibPath

def addEnvs():
	scriptPath = os.path.dirname(os.path.realpath(__file__))
	llfibuildPath = os.path.join(scriptPath, "llfi/")

	versionString = subprocess.check_output(["python3", "--version"], stderr=subprocess.STDOUT)
	versionString = versionString.strip()
	versionSplit = versionString.split()
	versionSplit = str(versionSplit[1]).split('.')

	majorVer = versionSplit[0]
	minorVer = versionSplit[1]

	pyVersion = str(majorVer) + "." + str(minorVer)
	pyPath = os.path.join(scriptPath, "pyyaml/lib/python"+pyVersion+"/site-packages/")

	homePath = os.environ['HOME']
	tcshPath = os.path.join(homePath, ".tcshrc")

	with open(tcshPath, "a") as rcFile:
		rcFile.write("setenv PYTHONPATH " + pyPath + "\n")
		rcFile.write("setenv llfibuild " + llfibuildPath + "\n") 

parser = argparse.ArgumentParser(
		description=("Installer for UBC DependableSystemsLab's LLFI"),
		epilog="More information available at www.github.com/DependableSystemsLab/LLFI",
		usage='%(prog)s [options]')
parser.add_argument("-v", "--version",  action='version', version="LLFI Installer v0.1, May 17th 2014")
parser.add_argument("-cD", "--cleanDownloads", action='store_true', help="Clean (rm) already downloaded files before installing")
parser.add_argument("-cS", "--cleanSources", action='store_true', help="Clean (rm) already extracted files before installing")
parser.add_argument("-nD", "--noDownload", action='store_true', help="Do not download any files")
parser.add_argument("-nE", "--noExtract", action='store_true', help="Do not extract the archives before installing")
parser.add_argument("-nB", "--noBuild", action='store_true', help="Do not perform installation, only downloading + extracting")
parser.add_argument("-nBLLVM", "--noBuildLLVM", action='store_true', help="Do not compile the LLVM")
parser.add_argument("-fBLLVM", "--forceBuildLLVM", action='store_true', help="Force recompilation of LLVM")
parser.add_argument("-fBPyYaml", "--forceBuildPyYaml", action='store_true', help="Force recompilation of PyYaml")
parser.add_argument("-tF", "--testFeature", action='store_true', help="LLFI installer development use only")

def testFeature():
	print("Testing Experimental Installer Feature")

if __name__ == "__main__":
	args = parser.parse_args(sys.argv[1:])
	if args.testFeature:
		testFeature()
		sys.exit(0)
	if args.cleanDownloads:
		print("Cleaning downloads...")
		subprocess.call(["rm", "-rf", DOWNLOADSDIRECTORY])
		print("Done.")
	if args.cleanSources:
		print("Cleaning extracted sources...")
		currPath = os.getcwd()
		if os.path.isdir(LLFIROOTDIRECTORY):
			os.chdir(LLFIROOTDIRECTORY)
			for target in DOWNLOADTARGETS:	
				subprocess.call(["rm", "-rf", target['EXTRACTPATH']])
			print("Done.")
		os.chdir(currPath)	
	print("Installing LLFI to: " + os.path.abspath(LLFIROOTDIRECTORY))
	if not args.noDownload:
		DownloadSources(DOWNLOADTARGETS, DOWNLOADSDIRECTORY)
	if not args.noExtract:
		ExtractSources(DOWNLOADTARGETS, DOWNLOADSDIRECTORY, LLFIROOTDIRECTORY)
	if not args.noBuild:
		build(not args.noBuildLLVM, args.forceBuildLLVM)
		addEnvs()
		buildPyYaml(args.forceBuildPyYaml)
