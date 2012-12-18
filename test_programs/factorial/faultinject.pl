#!/usr/bin/perl

#use lib 'path_to_your_local_directory_for_timeout_package'; 

use Time::Out qw(timeout) ;
$input_file = $ARGV[0];
$sopath = $ARGV[1];
$filename = $ARGV[2];
$num_fi = $ARGV[3]; #number of fault injections for branches
#$num_data_fi = $ARGV[4];
#$num_branch_bs = $ARGV[5]; 
$type = $ARGV[4];

$cleanexec = "$filename.bc";
$mem2regfile = "$filename.mem2reg.bc";
$prof_file = "$mem2regfile.prof.txt";
$linkedproffile_branch = "$filename.final_prof.branch.bc";
$linkedproffile_data = "$filename.final_prof.data.bc";
$linkedproffile_bs = "$filename.final_prof.bs.bc";
$prof_file_all = "$mem2regfile.all.prof.txt";
$linkedproffile_all = "$filename.final_prof.all.bc";
$nb_secs = 120;
$faultinjectfile_branch="$filename.inject.branch.bc";
$linkedfaultinjectfile_branch = "$filename.final_inject.branch.bc";
$hangfile = "$filename.hang.txt";
 
$faultinjectfile_data="$filename.inject.data.bc";
$linkedfaultinjectfile_data = "$filename.final_inject.data.bc";

$faultinjectfile_bs="$filename.inject.bs.bc";
$linkedfaultinjectfile_bs = "$filename.final_inject.bs.bc";

$branchstaticfile = "$mem2regfile.branchstatic.txt";
$datastaticfile = "$mem2regfile.datastatic.txt";

$fi_randomc = "fi_random.c";
$fi_randombc = "fi_random.bc";

$baseline_output = $filename."_baseline";
$dir_output_type = $filename."_output_$type";


if(-d $baseline_output)
{	system("rm -rf $baseline_output"); }

system("mkdir $baseline_output");

print STDERR "RUNNING BASELINE!\n";
if(-d $dir_output_type)
{ system("rm -rf $dir_output_type"); }
system("mkdir $dir_output_type");

runBaseline($cleanexec);
if($type eq "Branch")
{	print STDERR "RUNNING BRANCH!\n";
	$num_branch_fi = $num_fi;
	runFaultInjection($linkedproffile_branch, $faultinjectfile_branch, $linkedfaultinjectfile_branch, "Branch");	

}
elsif($type eq "Data")
{	print STDERR "RUNNING DATA!\n";
	$num_data_fi = $num_fi;
	runFaultInjection($linkedproffile_data, $faultinjectfile_data, $linkedfaultinjectfile_data, "Data");	

}
elsif($type eq "BackwardSlice")
{
	print STDERR "RUNNING BS\n";
	$num_branch_bs = $num_fi;
	runFaultInjection($linkedproffile_bs, $faultinjectfile_bs, $linkedfaultinjectfile_bs, $type);
}
sub change_file
{
	my($file,$define_var,$new_val) = @_;
	open INPUT_FILE, "< $file";
	open OUTPUT_FILE, "> temp.$file";
	$done =0;
	while($line=<INPUT_FILE>)
	{
		chomp $line;
		if(($line !~ /#include/) && ($done == 0))
		{ 	print OUTPUT_FILE "#define $define_var 1\n"; $done = 1;}
		print OUTPUT_FILE "$line\n";

	}
	
	close OUTPUT_FILE;
	close INPUT_FILE;
	system("mv temp.$file $file");
}

sub runFaultInjection
{
	my($linkedprofile, $fifile, $linkedfifile, $type) = @_;
	open INPUT_FILE, "< $input_file" or die"cant open $input_file\n";
	@inputs = <INPUT_FILE>;
	chomp @inputs;
	close INPUT_FILE;
	$input_count =0;
	system("cp $fi_randomc tmp.$fi_randomc");
	$inputline = $inputs[0];

	system("lli $linkedprofile $inputline output.prof.txt");
	system("cp $prof_file $type.$prof_file");
	if($type eq "Branch")
	{ 	
		system("opt -load $sopath/LLFI.so -FaultInjectionRandom -fioption=b $mem2regfile -o $fifile");
		$num_static = `cat $branchstaticfile | wc -l`;
		change_file($fi_randomc,"BRANCH_PROF",0);
		$run = $num_branch_fi;
	}
	elsif($type eq "BackwardSlice")
	{
		$fi_randomc_golden = "fi_random.golden.c";
		system("opt -load $sopath/LLFI.so -FaultInjectionRandom -fioption=nobranch $mem2regfile -o $fifile");
		#change_file($fi_randomc,"GOLDEN_RUN",0); #add golden run definition
		#system("llvm-gcc -emit-llvm $fi_randomc -S -o $fi_randombc"); 
		#system("llvm-link $fifile $fi_randombc -o $linkedfifile");
		#system("lli $linkedfifile $inputline");
		#system("cp tmp.$fi_randomc $fi_randomc");
		change_file($fi_randomc, "BACKWARD_SLICE_TRACING",0);
		$run = $num_branch_bs;
		#$dir_output = $dir_output_bs;	
	}
	system("llvm-gcc -emit-llvm $fi_randomc -S -o $fi_randombc"); 
	system("llvm-link $fifile $fi_randombc -o $linkedfifile");
	print "NUM INJECTIONS: $run\n";
	open HANGFILE, "> $hangfile" or die "cant open $hangfile\n";
	for($i=0;$i<$run;$i++)
	{  timeout $nb_secs => sub {system("lli $linkedfifile $inputline > $dir_output_type/input$input_count.faultyoutput.$i.txt"); };
		if ($@){
		#timed out operation
			print HANGFILE "$i\n";
			print STDERR "TIMED OUT!\n";
		}
	}
	close HANGFILE;
	system("cp tmp.$fi_randomc $fi_randomc");
	system("rm -rf tmp.$fi_randomc");
}
sub runBaseline
{
	my($cleanexec) = @_;
	$input_count =0;
	open INPUT_FILE, "< $input_file" or die"cant open $input_file\n";
	@inputs = <INPUT_FILE>;
	chomp @inputs;
	close INPUT_FILE;
	$input_count =0;
	$inputline= $inputs[0];
	system("lli $cleanexec $inputline > $baseline_output/input$input_count.cleanoutput.txt"); 
}
