#ifndef CORE_H
#define CORE_H

#include "Instr.h"
#include "SimulatorExceptions.h"

#define DATA_MEMORY_SIZE 1024
#define INSTR_MEMORY_SIZE 1024

class Core
{
public:
	Core(Instr* instr_mem[], int instr_count = 0);
	~Core();
	void execute(DataMemory& data_memory, int core_num);

private:
	Instr* instr_memory[INSTR_MEMORY_SIZE];
	int instructions_count; // denotes the number of instructions actually loaded from input file 
	int PC;  // Program Counter indicating the index of the instruction currently being executed  

};

#endif

