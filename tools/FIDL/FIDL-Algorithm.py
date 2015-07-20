#! /usr/bin/env python3

# Everytime the contents of .fidl file is changed, this script should be run to create new passes and injectors
# It is assumed that the script is executed in the <llfisrc>/tools/FIDL/ directory

import sys, os
import shutil, errno
import subprocess

script_path = os.path.realpath(os.path.dirname(__file__))
InputFIDL = os.path.basename(sys.argv[1])

### PHIL @ July 12
llfiroot = os.path.dirname(os.path.dirname(script_path))
software_fault_injectors = os.path.join(llfiroot, 'runtime_lib/_SoftwareFaultInjectors.cpp')
software_failures_passes_dir = os.path.join(llfiroot, 'llvm_passes/software_failures/')
cmakelists = os.path.join(llfiroot, 'llvm_passes/CMakeLists.txt')
gui_software_fault_list = os.path.join(llfiroot, 'gui/config/customSoftwareFault_list.txt')
setup_script = os.path.join(llfiroot, 'setup.py')

############################################################################

def checkInputFIDL():
	#Check for Input FIDL's presence
  global cOpt
  srcpath = os.path.dirname(options["source"])
  try:
    f = open(os.path.join(srcpath, 'input.FIDL'), 'r')
  except:
    print("ERROR: No input.FIDL file in the %s directory." % srcpath)
  os.rmdir(options["dir"])
  exit(1)
#############################################################################
 #read .fidl file, and calculates the number of trigger points
def readInputFIDL():
  global A,B,C,D,E,F,G,H,K,X,M,N,O,P,F_Class,F_Mode,NumRegs,NumInsts,Insts,Regs,F_Injector,SpecInstsIndexes,numOfSpecInsts, Type, Action,src, singlesrc,multisrc, dst, RetVal, Reg
  fo = open(InputFIDL, 'r')
  
  FIDLObjects0=list(fo)
  # remove '/n' from all list members.
  FIDLObjects = [el.replace('\n', '').replace("  ", '') for el in FIDLObjects0]
  #print (FIDLObjects)
  
  PassName=FIDLObjects.index('New_Failure_Mode ') 
  Trigger= FIDLObjects.index('Trigger:')
  Target=FIDLObjects.index('Target:')
  TriggerS=FIDLObjects.index('Trigger*: ')
  Action=FIDLObjects.index('Action:')
  F_Class=FIDLObjects[FIDLObjects.index('Failure_Class : ')+1]
  F_Mode= FIDLObjects[FIDLObjects.index('Failure_Mode :')+1]
  Insts=FIDLObjects[Trigger+1:TriggerS]
  while '' in Insts:
    Insts.remove('')
  #print (Insts)  
  NumInsts=len(Insts)
  SpecInsts= FIDLObjects[TriggerS+1:Target]
  num=len(SpecInsts) 
  for i in range (0, num):
    if SpecInsts[i] != '':
      s= SpecInsts[i].split()
      
      SpecInstsIndexes = [el.replace('\n', '').replace("  ", '') for el in s]
      #print (SpecInstsIndexes)
      if SpecInstsIndexes[0] != '{' :
        print ('Trigger* must be begun by {')
      SpecInstsIndexes.remove('{')
      SpecInstsIndexes.remove('}')
      numOfSpecInsts= len(SpecInstsIndexes)
      #print (numOfSpecInsts) 
      SpecInstsIndexes= (', '.join(  SpecInstsIndexes))
      #print (SpecInstsIndexes)
    else:
      numOfSpecInsts=0 
      SpecInstsIndexes= ''
  Regs=FIDLObjects[Target+1:Action]
  #print (Regs)
  while '' in Regs:
    Regs.remove('')
 # print (Regs)  
  NumRegs= len(Regs)
 #
  #print (NumRegs)
  #print (NumInsts)
  src=0 
  singlesrc = 0
  multisrc=0
  dst= 0 
  RetVal=0  
  
  for i in range (0, NumRegs):
    if Regs[i] != '':
    	s= Regs[i].split()
    	#print (s)
    	if s[0]=='dst':
    		dst=1
    	elif s[0]=='src':
    		src=1
    		singlesrc=1
    		Reg = s[1]
    		Regs[i]= Reg
    	elif s[0]=='RetVal':
    		RetVal=1
    	  
    		
    	elif s[2] == 'dst' :
    		dst=1
    	elif s[2] == 'src' :
    		#dst=0
    		src=1
    		multisrc=1
    		Regs[i]=s[3]
    	elif s[2]=='RetVal' :
    		#dst=0  
    		#src=0 
    		RetVal=1
    	elif s[1]=='::':
    		Regs[i]= s[3]
    		Insts [i]=s[0] 
    	else:		
    	  print ('Target is not in proper format')
    else:
    	 dst=1
    	 print (" un-defined Target is set to default")  
           
      
      
       
  #H=FIDLObjects.index('}')
  #Atype=FIDLObjects.index(Action+1)
  Type=FIDLObjects [Action+1]
  #print (Type)  
  fo.close


##############################################################################
def FTriggerGenerator():
  
#convert trigger and target of .fidl file into appropriate llvm passes
  #os.chdir("llfisrc/Templates/")
  
  xo= open ('TargetDestinationTemplate.cpp','r')
  MapLines0=list(xo)
  xo.close
  
  # remove '/n' from all list members.
  MapLines = [el.replace('\n', '').replace("  ", '') for el in MapLines0]
  #print (MapLines)
  M1=MapLines.index(' // probe 0')
  
  MapLines.insert(M1+1,'class _%s_%sInstSelector : public FIInstSelector{' %(F_Class,F_Mode) )
  M2=MapLines.index('// probe 1')
  MapLines.insert(M2+1,'_%s_%sInstSelector (){' %(F_Class,F_Mode) )
  M3=MapLines.index(' // probe 2')
  for i in range (0,NumInsts):
    if Insts[i]!= '':
     MapLines.insert(M3+1, 'funcNames.insert(std::string("%s"));'%(Insts[i])) 
  M4=MapLines.index('// probe 3')
  MapLines.insert(M4+1,'info["failure_class"] = "%s";' %(F_Class))
  MapLines.insert(M4+2,'info["failure_mode"] = "%s";' %(F_Mode))
  MapLines.append( 'static RegisterFIInstSelector A("%s(%s)", new   _%s_%sInstSelector());'%(F_Mode, F_Class, F_Class,F_Mode))
  if singlesrc==1:
  	MapLines.append( 'static RegisterFIRegSelector B("%s(%s)",  new FuncArgRegSelector( %s));}'%(F_Mode, F_Class, Reg))
  elif dst==1:
  	MapLines.append( 'static RegisterFIRegSelector B("%s(%s)", new   FuncDestRegSelector());}'%(F_Mode, F_Class))
  
  
  to= open ('TargetSourceTemplate.cpp', 'r')
  PassLines0= list (to)
  to.close

  # remove '/n' from all list members.
  PassLines = [el.replace('\n', '').replace("  ", '') for el in PassLines0]
  A=PassLines.index('// mark 1')
  PassLines.insert(A+1, 'class _%s_%sInstSelector : public SoftwareFIInstSelector{' %(F_Class,F_Mode)) # Trigger: "fread"
  B=PassLines.index('// mark 2')
  PassLines.insert(B+1,'_%s_%sInstSelector (){' %(F_Class,F_Mode))
  X= PassLines.index('// mark 3')
           
  for i in range (0,NumRegs):
    if Insts[i]!= '':
      PassLines.insert(X+1,'funcNamesTargetArgs["%s"]= std::set<int>();'  %(Insts[i]) )
      PassLines.insert(X+2, 'funcNamesTargetArgs["%s"].insert(%s);'%(Insts[i], Regs[i]))
     
  
  C=PassLines.index('// mark 4')
  PassLines.insert(C+1, 'info["failure_class"] = "%s";'%(F_Class))
  PassLines.insert(C+2,'info["failure_mode"] = "%s";'%(F_Mode))
  F=PassLines.index('// mark 5')
  PassLines.insert(F-2,'class _%s_%sRegSelector: public SoftwareFIRegSelector{'%(F_Class,F_Mode))  
  PassLines.insert(F-3, 'std::map<std::string, std::set<int> >  _%s_%sInstSelector::funcNamesTargetArgs;'%(F_Class,F_Mode))
  F=PassLines.index('virtual bool isRegofInstFITarget(Value *reg, Instruction *inst){')
  PassLines.insert(F+5, 'if( _%s_%sInstSelector::isTarget(CI, reg)) return true;'%(F_Class,F_Mode))
  PassLines.append( 'static RegisterFIInstSelector A("%s(%s)", new   _%s_%sInstSelector());'%(F_Mode, F_Class, F_Class,F_Mode))
  if multisrc==1:
  	PassLines.append( 'static RegisterFIRegSelector B("%s(%s)", new   _%s_%sRegSelector());}'%(F_Mode, F_Class, F_Class,F_Mode))
 # print ( PassLines)
  else: 
    print ('target is not src registers')
  AA=PassLines.index ('//mark 6')

  PassLines.insert(AA+1,'long numOfSpecInsts= %s;'%(numOfSpecInsts))
  PassLines.insert(AA+2,'long IndexOfSpecInsts[] = {%s};'%(SpecInstsIndexes))
  
  
  
  
  	
  #elif RetVal==1: 
  	#PassLines.append( 'static RegisterFIRegSelector B("%s(%s)", new   RetValRegSelector());}'%(F_Mode, F_Class))
  
  # complete instrumenting pass development by printing the pass content into a file.
  
  
  filter(None, PassLines)
  NumLine= len (PassLines)
  for i in range (0,NumLine):
    "".join(PassLines[i].split())
    
  filter(None, MapLines)
  RangeLine= len (MapLines)
  for i in range (0,RangeLine):
    "".join(MapLines[i].split())    
    

  with open('_%s_%sSelector.cpp'%(F_Class,F_Mode), mode='wt', encoding='utf-8') as myfile:
  	if multisrc==1: 
  	  for lines in PassLines:
  	  	print(lines, file = myfile)
  	  print ('Instrument module created.')
  	elif dst==1 or singlesrc==1:
  		for lines in MapLines:
  			print(lines, file = myfile)
  		print ('Instrument module created.')
  	else:
  		print ('Check your target format!') 
  	if dst==1 and multisrc==1:
  		print ("Invalid trigger module (both src and dst usage not allowed)")	
  	   
  	myfile.close
  
  # modify llvm_pass/CMakeLists.txt
  # TODO need to check if the line exist and then modify it
  f = open(cmakelists, 'r')
  l = list(f)
  f.close
  
  try:
    l.index('  software_failures/%s\n' % filename) 
  except:
    l.insert(l.index('  #FIDL\n') + 1, '  software_failures/%s\n' % filename)

    f = open(cmakelists, 'w')
    f.writelines(l)
    f.close

  # modify GUI's list
  # TODO same as above
  f = open(gui_software_fault_list, 'r')
  l = list(f)
  f.close
  
  try:
    l.index('%s(%s)\n' % (F_Mode, F_Class))
  except:
    l.append('%s(%s)\n' % (F_Mode, F_Class))
  
    f = open(gui_software_fault_list, 'w')
    f.writelines(l)
    f.close
  
   # print (PassLines)
###########################################################

def FInjectorGenerator():

  ko= open ('Built-in-FITemplate.cpp', 'r')
                
  InjectorLines0= list (ko)
  # remove '/n' from all list members.
  InjectorLines = [el.replace('\n', '') for el in InjectorLines0]
  M=InjectorLines.index('static RegisterFaultInjector AN("DataCorruption(Data)", BitCorruptionInjector::getBitCorruptionInjector());')
  N=InjectorLines.index('static RegisterFaultInjector CD("NoAck(MPI)", new HangInjector());')
  O=InjectorLines.index('static RegisterFaultInjector DB("CPUHog(Res)", new SleepInjector());')
  P=InjectorLines.index('static RegisterFaultInjector BA("MemoryLeak(Res)", new MemoryLeakInjector());')
  S=InjectorLines.index('static RegisterFaultInjector EH("PacketStorm(MPI)", new ChangeValueInjector(-40, false));')
  T=InjectorLines.index('static RegisterFaultInjector FB("NoClose(API)", new InappropriateCloseInjector(false));')
  U=InjectorLines.index('static RegisterFaultInjector HB("LowMemory(Res)", new MemoryExhaustionInjector(false));')
  V=InjectorLines.index('static RegisterFaultInjector IB("WrongSavedFormat(I/O)", new WrongFormatInjector());')
  W=InjectorLines.index('static RegisterFaultInjector JA("DeadLock(Res)", new PthreadDeadLockInjector());')
  X=InjectorLines.index('static RegisterFaultInjector KA("ThreadKiller(Res)", new PthreadThreadKillerInjector());')
  Y=InjectorLines.index('static RegisterFaultInjector LA("RaceCondition(Timing)", new PthreadRaceConditionInjector());')
  ko.close    
  #print (Type)     
  if Type == 'Corrupt':
  	 InjectorLines.insert(M+1,'static RegisterFaultInjector AO("%s(%s)", BitCorruptionInjector::getBitCorruptionInjector());'%(F_Mode, F_Class))
  	 #print('i am in corrupt')
  	 #print (" compilation successful")
  elif Type == "Freeze" :	
  	 InjectorLines.insert(N+1,'static RegisterFaultInjector CE("%s(%s)", new HangInjector());'%(F_Mode, F_Class))
  	 #print('i am in freeze')
  	 #print (" compilation successful")
  elif Type== "Delay" :	 
    InjectorLines.insert(O+1,'static RegisterFaultInjector DC("%s(%s)", new SleepInjector());'%(F_Mode, F_Class))
    #print('i am in delay')
    #print (" compilation successful")
  elif Type=="Perturb :: MemoryLeakInjector": 
    InjectorLines.insert(P+1, 'static RegisterFaultInjector BB("%s(%s)", new MemoryLeakInjector());'%(F_Mode, F_Class))
    #print ('i am in built-in perturb') 
    #print (" compilation successful")
  elif Type=="Perturb :: ChangeValueInjecto":
    InjectorLines.insert(S+1, 'static RegisterFaultInjector EI("%s(%s)", new ChangeValueInjector(-40, false));'%(F_Mode, F_Class))
    #print (" compilation successful")
  elif Type=="Perturb :: InappropriateCloseInjector":
  	 InjectorLines.insert(T+1, 'static RegisterFaultInjector FC("%s(%s)", new InappropriateCloseInjector(false));'%(F_Mode, F_Class))
  	 #print (" compilation successful")
  elif Type=="Perturb :: MemoryExhaustionInjector":
  	 InjectorLines.insert(U+1,'static RegisterFaultInjector HC("%s(%s)", new MemoryExhaustionInjector(false));'  %(F_Mode, F_Class))
  	# print (" compilation successful")
  elif Type=="Perturb :: WrongFormatInjector":
  	 InjectorLines.insert(V+1, 'static RegisterFaultInjector IC("%s(%s)", new WrongFormatInjector());'%(F_Mode, F_Class))
  	 #print (" compilation successful")
  elif Type=="Perturb :: PthreadDeadLockInjector":
  	 InjectorLines.insert(W+1, 'static RegisterFaultInjector JB("%s(%s)", new PthreadDeadLockInjector());'%(F_Mode, F_Class))
  #	 print (" compilation successful")
  elif Type=="Perturb :: PthreadThreadKillerInjector":
  	 InjectorLines.insert(X+1, 'static RegisterFaultInjector KB("%s(%s)", new PthreadThreadKillerInjector());'%(F_Mode, F_Class))
  	# print (" compilation successful")
  elif Type=="Perturb :: PthreadRaceConditionInjector":
  	 InjectorLines.insert(Y+1, 'static RegisterFaultInjector LB("%s(%s)", new PthreadRaceConditionInjector());' %(F_Mode, F_Class))
  	# print (" compilation successful")
    
  elif Type=='':
    InjectorLines.insert(M+1,'static RegisterFaultInjector AM("%s(%s)", BitCorruptionInjector::getBitCorruptionInjector());'%(F_Mode, F_Class)) 
    #print ('i am in un-defined')
   # print (" compilation successful")
    
        
  if Type=="Perturb :: CustomInjector":
    AddInjector()
    #print ('i am in perturb') 
   # print (" compilation successful") 	 
  else:
  	 filter (None, InjectorLines)
  	 NumLine= len (InjectorLines)
  	 for i in range (0,NumLine):
  	 	"".join(InjectorLines[i].split())
  	 with open(software_fault_injectors, mode='wt', encoding='utf-8') as myfile:
  	 	for lines in InjectorLines:
  	 		print(lines, file = myfile)
  	 	myfile.close	
      
  
 #######################################################################   
def AddInjector():
  fo = open(InputFIDL, 'r') 
  FIDLObjects0=list(fo)
  FIDLObjects = [el.replace('\n', '').replace(" ", '') for el in FIDLObjects0]  
  Injector=FIDLObjects.index('CustomInjector(char*Target){') 
  codes= FIDLObjects[Injector+1: ]
  #print (codes)
  codes=[i for i in codes if i !='']
  LOC=len (codes) 
  del (codes[LOC-1]) 
  #print (codes) 
  fo.close  	  
  	 
 
  lo = open('NewInjectorTemplate.cpp' , 'r') 
  NInjectorLines0=list(lo)
  NInjectorLines = [el.replace('\n', '') for el in NInjectorLines0]  	
  #Q= NInjectorLines.index(' public:') 
  NInjectorLines.insert(2,'class %s_%sFInjector: public SoftwareFaultInjector {'%(F_Class,F_Mode))
  R= NInjectorLines.index('    void * Target= (void *)buf;  ' )
  for i in range (0, LOC-1):
    NInjectorLines.insert(R+1+i, codes[i]) 
  NInjectorLines.append('static RegisterFaultInjector X("%s(%s)", new %s_%sFInjector);'% (F_Mode,F_Class,F_Class,F_Mode)) 
  #print (NInjectorLines)
  
  ko= open ('Built-in-FITemplate.cpp', 'r')
                
  InjectorLines0= list (ko)
  # remove '/n' from all list members.
  InjectorLines = [el.replace('\n', '') for el in InjectorLines0]
  FinalInjector=InjectorLines + NInjectorLines
  ko.close
  #writing to the file
  filter (None, FinalInjector)
  NumLine= len (FinalInjector)
  for i in range (0,NumLine):
    "".join(FinalInjector[i].split())
  
  with open(software_fault_injectors, mode='wt', encoding='utf-8') as myfile:
    for lines in FinalInjector:
      print(lines, file = myfile)
    myfile.close 
###########################################################

def main(InputFIDL):
  readInputFIDL()	 
  FTriggerGenerator()
  FInjectorGenerator()
  print ('Injector module created.')
  ################################################################################
if __name__ == '__main__':
        main(sys.argv[1])


