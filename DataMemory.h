#ifndef DATAMEMORY_H
#define DATAMEMORY_H

#include<iostream>
#include <mutex>

class DataMemory {
public:
	DataMemory(int size=1024);
	~DataMemory();

	// The following function is just for debugging, allows the access of data memory elements up to a sent address
	void printDataMem(int index);

	int readVal(int index);
	void writeVal(int index, int val); 


private:
	int data_mem_size;
	int* data_memory;  // pointer to int that will contain the actual data in the data_memory 

	std::mutex mutex;

};




#endif 
