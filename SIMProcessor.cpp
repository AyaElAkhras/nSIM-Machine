#include "SIMProcessor.h"

SIMProcessor::SIMProcessor(int N, string files[], int number_of_files)
{
	// check on N 1st
	if (N <= 0) {
		throw WrongNException("Number of Cores can't be a 0 or a negative number!!");   // will be catched in main 
	}
	
	// if N is > 0
	// Check that exactly N file names are passed or else raise an exception 
	if(number_of_files != N)
		throw WrongNException("Must Supply exactly N file names!!");   // will be catched in main 


	// We are sure that N is appropriate and N files are passed
	file_names = new string[N];
	for (int i = 0; i < N; i++) {
		file_names[i] = files[i];
	}

	number_of_cores = N;
	
}


void SIMProcessor::exec()
{
	for (int i = 0; i < number_of_cores; i++) {
		threads.push_back(thread([this, i]() {
			Instr* my_instruction_memory[INSTR_MEMORY_SIZE];   // creating a new array of instruction ptrs for each thread

			try {
				int instruction_num = instr_factory.ParseFile(file_names[i], my_instruction_memory);

				// Declaring a Core object and passing it the loaded instructions
				Core core(my_instruction_memory, instruction_num);
				try {
					core.execute(data_memory, i);
				}
				catch (std::exception except_p) {
					printf("\nException Occured From Core number %d! %s \n\n", i, except_p.what());
				}
			}
			catch (std::exception except) {
				printf("\nException Occured From Core number %d! %s \n\n", i, except.what());

			}

			}));
	}

	for (auto& thread : threads) {   
		thread.join();
	}

}


void SIMProcessor::printDataMem(int index)
{
	data_memory.printDataMem(index);
}

SIMProcessor::~SIMProcessor()
{
	delete[] file_names;
}
