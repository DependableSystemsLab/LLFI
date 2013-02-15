#!/usr/bin/perl
$exec = $ARGV[0];
$num_fi = $ARGV[1];
$type = $ARGV[2];

$golden_output = "$exec\_baseline/input0.cleanoutput.txt";
$activatedfaultfile = "$exec.mem2reg.bc.activatedFaults.txt";
$hangfile = "$exec.hang.txt";

$type_outputdir = "$exec\_output_$type";
$outcome_file = "$exec\_faultoutcome_stats.txt";



calculate_outcome($type_outputdir, $num_fi, $type);

sub calculate_outcome
{
	my($output_dir,$total_faults_injected, $type) = @_;
	@output = `ls $output_dir`;
	chomp @output;
	system("> output_$type.txt");
	open OUTPUT_FILE, "> $outcome_file" or die "cant open $outcome_file\n";

    $cmpfile = "compare.txt";	
	#all hangs
	open HANGFILE, "< $hangfile", or die "cant open $hangfile\n";
	@hangs = <HANGFILE>;
	close HANGFILE;
	chomp @hangs;
	foreach $hangid (@hangs){
		push(@hang_index_array, $hangid);
		print "$hangid is a HANG\n";
	}
	###################################################################
	#new output analysis code, Qining
	open BASELINE, "< $golden_output", or die "cant open original baseline outputfile\n";
	@original_baseline = <BASELINE>;
	close BASELINE;
	#print @original_baseline;
	my @choped_baseline = ();
	for($i = 0; $i < scalar(@original_baseline); $i++)
	{
		if($i>=12 and $i<=50)
		{
			next;
		}
		if(!($original_baseline[$i] =~ m/spawn/ || 
			$original_baseline[$i] =~ m/\d+\:\d+\:\d+/ || 
			$original_baseline[$i] =~ m/users,  load/ || 
			$original_baseline[$i] =~ m/\d+ total/ || 
			$original_baseline[$i] =~ m/\'arpa\'/ || 
			$original_baseline[$i] =~ m/\'validate\'/ || 
			$original_baseline[$i] =~ m/Did you know you can/ ||
			$original_baseline[$i] =~ m/\/\@/ ||
			$original_baseline[$i] =~ m/\/E/ ||
			$original_baseline[$i] =~ m/\/G/ ||
			$original_baseline[$i] =~ m/\/R/))
		{
			push(@choped_baseline, $original_baseline[$i]);
		}
	}
	##chomp @choped_baseline;
	##print @choped_baseline;
	#here we've got base_line list
	foreach $o (@output)
	{
		if($o =~ /(input\d+\.faultyoutput\.)(\d+)(\.txt)/)
		{
			$index = $2;
			push(@output_index,$index);
			if($index ~~ @hangs)
			{
				next; #if the fault causes timeout, we skip it because it has already be processed
			}
		}
		open FAULTYOUTPUT, "< $output_dir/$o", or die "cant open original baseline outputfile\n";
		@original_faulty = <FAULTYOUTPUT>;
		close FAULTYOUTPUT;
		my @choped_faulty = ();
		for($i = 0; $i < scalar(@original_faulty); $i++)
		{
			if($i>=12 and $i<=50)
			{
				next;
			}
			if(!($original_faulty[$i] =~ m/spawn/ || 
			$original_faulty[$i] =~ m/\d+\:\d+\:\d+/ || 
			$original_faulty[$i] =~ m/users,  load/ || 
			$original_faulty[$i] =~ m/\d+ total/ || 
			$original_faulty[$i] =~ m/\'arpa\'/ || 
			$original_faulty[$i] =~ m/\'validate\'/ || 
			$original_faulty[$i] =~ m/Did you know you can/ ||
			$original_faulty[$i] =~ m/\/\@/ ||
			$original_faulty[$i] =~ m/\/E/ ||
			$original_faulty[$i] =~ m/\/G/ ||
			$original_faulty[$i] =~ m/\/R/))
			{
				push(@choped_faulty, $original_faulty[$i]);
			}
		}
		##chomp @choped_faulty;
		##print @choped_faulty;
		#here we've got one faulty list
		if(!(@choped_faulty[scalar(@choped_faulty)-2,scalar(@choped_faulty)-1] ~~ @choped_baseline[scalar(@choped_baseline)-2,scalar(@choped_baseline)-1]))
		{
			push(@crash_index_array, $index); # Crash
			print "$index is a CRASH\n";
			next;
		}
		if(!(@choped_faulty ~~ @choped_baseline))
		{
			push(@sdc_index_array, $index); # SDC
			print "$index is a SDC\n";
			next;
		}
		push(@benign_index_array, $index); # Benign
		print "$index is a BENIGN\n";
	}
	#if there are any execution without output files
	 if(scalar(@output_index))
	 {
		 for($i=0; $i < $num_fi; $i++)
		 {
			 $found =0;
			 foreach $index (@output_index)
			 {
				 if($index == $i) { $found = 1; last;}
			 }
			 if($found == 0)
			 {
				 push(@crash_index_array, $i);
			 }
		 }	
	 }
	#new code ends
	###################################################################
	#~ foreach $o (@output)
	#~ {
		#~ if($o =~ /(input\d+\.faultyoutput\.)(\d+)(\.txt)/){
			#~ $index = $2;
			#~ push(@output_index,$index);
		#~ }
#~ 
		#~ system("cmp $golden_output $output_dir/$o > $cmpfile 2>&1"); 
		#~ if($o =~ /(input\d+\.faultyoutput\.)(\d+)(\.txt)/){
			#~ $index = $2; 
		#~ }
		#~ open CMP, "< $cmpfile";
		#~ @cmp = <CMP>;
		#~ close CMP;
		#~ chomp @cmp;
		#~ if(-z $cmpfile){
			#~ #benign
			#~ push(@benign_index_array, $index);
			#~ 
		#~ }
		#~ elsif(grep(/EOF/, @cmp)){
			#~ #crash
			#~ push(@crash_index_array, $index);
			#~ 
		#~ }
		#~ else {
			#~ push(@sdc_index_array, $index);
			#~ 
		#~ }
	#~ }
	#~ if(scalar(@output_index)){
		#~ for($i=0; $i < $num_fi; $i++){
			#~ $found =0;
			#~ foreach $index (@output_index){
				#~ if($index == $i) { $found = 1; last;}
			#~ }
			#~ if($found == 0){
				#~ push(@crash_index_array, $i);
			#~ }
		#~ }	
	#~ }	

	print OUTPUT_FILE "\nSDC INDEX\n";
	print OUTPUT_FILE "@sdc_index_array";

    print OUTPUT_FILE "\nCRASH INDEX\n";
    print OUTPUT_FILE "@crash_index_array";
	
    print OUTPUT_FILE "\nBENIGN INDEX\n";
    print OUTPUT_FILE "@benign_index_array";



	open ACTIVATEDFILE, "< $activatedfaultfile" or die "cant open $activatedfaultfile\n";
	@activatedFaults = <ACTIVATEDFILE>;
	chomp @activatedFaults;
	close ACTIVATEDFILE;

	$sdc = scalar(@sdc_index_array);
	#print "$sdc\n";
	
	$sdcrate = ($sdc/$num_fi) * 100;
	$crash = scalar(@crash_index_array);
	$benign = scalar(@benign_index_array);
	$hang = scalar(@hang_index_array);

	print OUTPUT_FILE "\nSDC Rate with 100% activation: $sdcrate\n";
	print OUTPUT_FILE "APPLICATION, SDC, CRASH, BENIGN, HANG\n";
	print OUTPUT_FILE "$exec, $sdc, $crash, $benign, $hang \n";

	print OUTPUT_FILE "ALL SDC\n";
	foreach $index(@sdc_index_array){
		if($activatedFaults[$index] =~ /^(Injected Fault : ID = )(\d+)/){
				print OUTPUT_FILE "$2\n";
		}
	}
	print OUTPUT_FILE "ALL CRASH\n";
	foreach $index(@crash_index_array){
		if($activatedFaults[$index] =~ /^(Injected Fault : ID = )(\d+)/){
			print OUTPUT_FILE "$2\n";
		}
		
	}
	print OUTPUT_FILE "ALL BENIGN\n";
	foreach $index(@benign_index_array){
		if($activatedFaults[$index] =~ /^(Injected Fault : ID = )(\d+)/){
			print OUTPUT_FILE "$2\n";
		}
		
	}

	close OUTPUT_FILE;
}

