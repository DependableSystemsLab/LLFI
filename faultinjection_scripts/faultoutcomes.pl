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
	}
	foreach $o (@output)
	{
		if($o =~ /(input\d+\.faultyoutput\.)(\d+)(\.txt)/){
			$index = $2;
			push(@output_index,$index);
		}

		system("cmp $golden_output $output_dir/$o > $cmpfile 2>&1"); 
		if($o =~ /(input\d+\.faultyoutput\.)(\d+)(\.txt)/){
			$index = $2; 
		}
		open CMP, "< $cmpfile";
		@cmp = <CMP>;
		close CMP;
		chomp @cmp;
		if(-z $cmpfile){
			#benign
			push(@benign_index_array, $index);
			
		}
		elsif(grep(/EOF/, @cmp)){
			#crash
			push(@crash_index_array, $index);
			
		}
		else {
			push(@sdc_index_array, $index);
			
		}
	}
	if(scalar(@output_index)){
		for($i=0; $i < $num_fi; $i++){
			$found =0;
			foreach $index (@output_index){
				if($index == $i) { $found = 1; last;}
			}
			if($found == 0){
				push(@crash_index_array, $i);
			}
		}	
	}	

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

