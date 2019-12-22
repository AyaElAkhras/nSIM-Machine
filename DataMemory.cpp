#include "DataMemory.h"


DataMemory::DataMemory(int size):data_mem_size(size) {
	data_memory = new int[size];

	// Initialize it all to 0s
	for (int i = 0; i < size; i++) {
		data_memory[i] = 0;
	}			
}

DataMemory::~DataMemory() {
	delete[] data_memory;
}

int DataMemory::readVal(int index) {
	std::lock_guard<std::mutex> guard(mutex);    
	return data_memory[index];
}

void DataMemory::writeVal(int index, int val) {
	std::lock_guard<std::mutex> guard(mutex);
	data_memory[index] = val;
}



// Used for debugging only, will call it in main in the end after joining all threads, so no point of using mutex here
void DataMemory::printDataMem(int index) {
	std::cout << "Will print the content of the Data Memory up to index number " << index << ":" << std::endl;
	for (int k = 0; k < index; k++) {
		std::cout << "  data_mem[" << k << "] = " << data_memory[k];
	}

	std::cout << std::endl << std::endl;
}
