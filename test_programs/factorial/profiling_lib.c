#include <stdio.h>
#include <stdlib.h>
#include<string.h>

enum {BRANCH, DEF, ALL, BACKWARD_SLICE};
FILE *profileFile;
char profileFileName[80];
int count = 0;
int prof_option;
//can extend later with other profilings

void doProfiling(int option)
{
    prof_option = option;
	count++;
}
void endProfiling(char *appName)
{
    strcpy(profileFileName,appName);
	if(prof_option == ALL)
		strcat(profileFileName,".all.prof.txt");
	else
		strcat(profileFileName,".prof.txt");
    if ((profileFile = fopen(profileFileName,"w"))==NULL) {
		fprintf(stderr,"Unable to open profiling file %s\n", profileFileName);
		return;	
	}
	if(prof_option == BRANCH)
    {	fprintf(profileFile,"BranchCount = %d\n", count); }
    else if(prof_option == DEF)
    {	fprintf(profileFile, "DataVariableCount = %d\n", count); }
    else if(prof_option == ALL)
	{   fprintf(profileFile, "AllCount = %d\n", count);}
	else if(prof_option == BACKWARD_SLICE)
	{	fprintf(profileFile, "BackwardSliceCount = %d\n", count); }
		
    fclose(profileFile); 
}
