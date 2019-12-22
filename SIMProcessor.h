#ifndef SIMPROCESSOR_H
#define SIMPROCESSOR_H

// This is the microprocessor that contains 1 DataMemory Bank and 1 InstructionFactory and N cores 
	// Each core has its own PC and executes instructions from its instruction_memory 

// in its constructor, it takes the number of cores N, and an array of files containing N file names 
#include <thread>
#include <vector>
#include "InstrFactory.h"
#include "Core.h"
using namespace std;

class SIMProcessor {
public:
	SIMProcessor(int N, string file_names[], int number_of_files);
	~SIMProcessor();   // calls the destructors of all objects 
	void exec();  // starts executing all its cores concurrently
	void printDataMem(int index);  // prints the contents of the DataMemory up to a specific index 


private:
	InstrFactory instr_factory; 	//  object will be passed one of the .txt files and should return Array of pointers to instructions
	DataMemory data_memory;  	// a single DataMemory object is going to be shared among multiple Cores
	string* file_names;
	int number_of_cores;
	vector<thread> threads;    // create a vector of N threads corresponding to the number_of_cores

	
};


#endif