#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include "FaultInjector.h"
#include "FaultInjectorManager.h"

using namespace std;

int main(int argc, char* argv[]) {
	string output_file_path("");
	ofstream output_file;
	for(int i = 0; i < argc; i++){
		if(string(argv[i]) == string("-o")){
			output_file_path = string(argv[i+1]);
		}
		// cout << "argv[" << i << "] = " << argv[i] << endl;
	}

	if(output_file_path.length() != 0){
		output_file.open(output_file_path.c_str());
	}

	FaultInjectorManager* faultinjectormanager = FaultInjectorManager::getFaultInjectorManager();
	vector<string> hardwarefaultinjectornames = faultinjectormanager->getInjectorNamesForType(string("HardwareFault"));
	if(output_file.is_open()){
		output_file << "HardwareFaultInjector:" << endl;
	}else{
		cout << "HardwareFaultInjector:" << endl;
	}
	for(int i = 0; i<hardwarefaultinjectornames.size(); i++){
		if(output_file.is_open()){
			output_file << "    - " << hardwarefaultinjectornames[i] << endl;
		}else{
			cout << "    - " << hardwarefaultinjectornames[i] << endl;
		}
	}

	vector<string> softwarefaultinjectornames = faultinjectormanager->getInjectorNamesForType(string("SoftwareFault"));
	if(output_file.is_open()){
		output_file << "SoftwareFaultInjector:" << endl;
	}else{
		cout << "SoftwareFaultInjector:" << endl;
	}
	for(int i = 0; i<softwarefaultinjectornames.size(); i++){
		if(output_file.is_open()){
			output_file << "    - " << softwarefaultinjectornames[i] << endl;
		}else{
			cout << "    - " << softwarefaultinjectornames[i] << endl;
		}
	}

	if(output_file.is_open())	output_file.close();

	return 0;
}