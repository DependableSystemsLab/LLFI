#!/bin/bash

####################### Readme #######################
# This script is for initializing a WATERS server.
# Basic development tools and CMake 2.8 will be inst-
# alled. LLVM 2.9 and a custom version of LLFI(for LL-
# VM 2.9) will be downloaded, build and installed.
# The default user account for this script is 'root'.
# So that it does not involve typing any password dur-
# ing the process
#
# Author: Qining
######################################################

export MAINDIR=/home

## Install basic pacakges
yum update -y
yum install -y nautilus-open-terminal
yum install -y xauth
yum install -y dbus-x11
yum groupinstall -y 'Fonts'
yum install -y gedit
yum groupinstall -y 'Development Tools'
yum install -y wget
yum install -y git

## Install CMake 2.8
cd $MAINDIR
mkdir cmake
wget http://www.cmake.org/files/v2.8/cmake-2.8.12.2-Linux-i386.sh
sh ./cmake-2.8.12.2-Linux-i386.sh --prefix=$MAINDIR/cmake --exclude-subdir
echo "export PATH=/home/cmake/bin:\$PATH">>/root/.bashrc
source /root/.bashrc
cmake --version

mkdir $MAINDIR/Downloads

## Compile, build and install llvm-3.4 and clang
cd $MAINDIR/Downloads
wget http://llvm.org/releases/3.4/llvm-3.4.src.tar.gz
wget http://llvm.org/releases/3.4/clang-3.4.src.tar.gz
tar -xvzf llvm-3.4.src.tar.gz
tar -xvzf clang-3.4.src.tar.gz
mv llvm-3.4 $MAINDIR/llvmsrc
mv clang-3.4 /home/llvmsrc/tools
mkdir $MAINDIR/llvm
cd $MAINDIR/llvm
cmake ../llvmsrc -DLLVM_REQUIRES_RTTI=1
make -j24
#make install
#echo "export PATH=/home/llvm/bin:\$PATH">>/root/.bashrc

## Install python3
cd $MAINDIR/Downloads
wget http://www.python.org/ftp/python/3.3.2/Python-3.3.2.tar.bz2
tar jxvf Python-3.3.2.tar.bz2
cd Python-3.3.2
./configure
./make -j24
./make install

# install pyyaml
cd $MAINDIR/Downloads
wget http://pyyaml.org/download/pyyaml/PyYAML-3.11.tar.gz
tar -xvzf PyYAML-3.11.tar.gz
mv PyYAML-3.11 $MAINDIR/pyyamlsrc
cd $MAINDIR/pyyamlsrc
python3 setup.py install --prefix=$MAINDIR/pyyaml
echo "export PYTHONPATH=\$PYTHONPATH:/home/pyyaml/lib/python3.3/site-packages">>/root/.bashrc
source /root/.bashrc

## install git 1.8
cd $MAINDIR/Downloads
wget http://git-core.googlecode.com/files/git-1.8.3.4.tar.gz
wget -O git-manpages-1.8.3.4.tar.gz http://code.google.com/p/git-core/downloads/detail?name=git-manpages-1.8.3.4.tar.gz&can-2&q=
yum install -y zlib-devel perl-CPAN gettext curl-devel
tar xvfz git-1.8.3.4.tar.gz
cd git-1.8.3.4
./configure
make -j24
make install
git --version

## Install LLFI
cd $MAINDIR/Downloads
git clone -b merge https://github.com/DependableSystemsLab/LLFI.git llfisrc
mv llfisrc $MAINDIR/llfisrc
cd $MAINDIR/llfisrc
./setup -LLVM_DST_ROOT $MAINDIR/llvm -LLVM_SRC_ROOT $MAINDIR/llvmsrc -LLFI_BUILD_ROOT $MAINDIR/llfi -LLVM_GXX_BIN_DIR $MAINDIR/llvm/bin
#echo "export PATH=\$PATH:/home/llfi/bin">>/root/.bashrc
#source /root/.bashrc

