#include "Core.h"


Core::Core(Instr* instr_mem[], int instr_count) : instructions_count(instr_count), PC(0)
{
	for (int i = 0; i < instructions_count; i++)
	{
		instr_memory[i] = instr_mem[i];
	}
}

Core::~Core()
{
	for (int i = 0; i < instructions_count; i++)
	{
		delete instr_memory[i];
	}
}

void Core::execute(DataMemory& data_memory, int core_num)   // 5aletha Parameter gaya mn bara ??????????
{
	int temp = 0;
	int iter = 0;
	// loop through all instructions in InstrMem and execute them one by one depending on you PC indexing
	while (PC < instructions_count) {
		instr_memory[PC]->FixOperands(data_memory);  // to read from data memory address operands 
		instr_memory[PC]->exec(temp, core_num);
		instr_memory[PC]->FixOperands(data_memory);  // to write the result to data memory 

		// The value of PC is updated inside each instruction depending on the type of instruction
		PC = temp;

		// You might need to use this output just for debugging 
		//std::cout << "Current value of PC is " << PC << std::endl;

		if (PC >= instructions_count && iter < instructions_count) {   // if jump instructions are requesting the move to an instruction that isn't existing, raise exception
			throw WrongMemoryAddressException("Can't Jump to an address that is not within the range of the Instruction Memory!");   // !!!!!! raise exception!!!! passed address is out of range of the Instruction memory !!!
		}


		if (PC == -1)   // this indicates that the current instruction we just executed is a HALT so must stop and return to main
			break;

		iter += 1;
	}
}

