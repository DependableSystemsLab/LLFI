#!/bin/bash
executable=$1
repinputfile=$2
sopath=$3
numbsfi=$4

if [ $# -ne 4 ]
then
        echo "Usage: `basename $0` executable repinputfile sopath num_of_faultinjections"
        exit
fi

filename=$executable
bcfile=$filename".bc"
mem2regfile=$filename".mem2reg.bc"
proffile_branch=$filename".mem2reg.prof.branch.bc"
proffile_data=$filename".mem2reg.prof.data.bc"
proffile_all=$filename".mem2reg.prof.all.bc"
proffile_bs=$filename".mem2reg.prof.bs.bc"
faultinjectfile_branch=$filename".inject.branch.bc"
faultinjectfile_data=$filename".inject.data.bc"
fic="fi_random.c"
fibc="fi_random.bc"
profc="profiling_lib.c"
proflib="profiling_lib.bc"
linkedproffile_bs=$filename".final_prof.bs.bc"
finalinjectfile=$filename".final_inject.bs.bc"
#type_branch="branch"

llvm-gcc -emit-llvm $profc -S -o $proflib
opt -mem2reg $bcfile -o $mem2regfile

opt -load $sopath/LLFIProfiling.so -ProfilingPass -profileoption=s $mem2regfile -o $proffile_bs
llvm-link $proffile_bs $proflib -o $linkedproffile_bs

> $mem2regfile.activatedFaults.txt
./faultinject.pl $repinputfile $sopath $filename $numbsfi "BackwardSlice"
./faultoutcomes.pl $filename $numbsfi "BackwardSlice"

## kill all lli appName... processes, this should always be the last command in this file. 
for lli_process in `ps wwaux | grep "lli $finalinjectfile" | grep -v grep |awk '{print $2}'`
do
echo $lli_process
kill -9 $lli_process
done
