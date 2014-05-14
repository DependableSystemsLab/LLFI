LLFI 1 Command Installer Package
================================
This package provides the simplest way to fully install an LLFI framework.
The provided build scribt  will compile both the LLVM, LLFI, and the LLFI-GUI
into the appropriate subdirectories.

Requirements:
	64bit Linux OS
	Cmake v2.8 or above
	Python 3 or above
	Java7 with JavaFX
	tcsh

Instructions:
	After extracting, simply run
		python build.py
	or:
		chmod +x build.py
		./build.py
	Expect a long build time (~1 Hour) to fully compile LLVM and LLFI.

	After compilation, LLFI GUI can be launched by running the LLFI-GUI script

Removal Instructions:
	To complete remove the LLFI framework from your system:

	rm -rf llfi
