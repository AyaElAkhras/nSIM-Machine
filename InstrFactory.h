#ifndef INSTR_FACTORY_H
#define INSTR_FACTORY_H
#include <string>
#include <fstream>

#include "Instr.h"
#include "SimulatorExceptions.h"



enum opcode {   // all the supported instructions 
	ADD,
	NEG,
	MUL,
	JMP,
	JMP0,
	ASS,
	LE,
	READ,
	WRITE,
	HALT,
	UNDEFINED   // if the opcode is none of the above instructions, this means exception should be raised 
};



class InstrFactory
{
public:
	InstrFactory(int dataMemorySize = 1024, int instructionMemorySize = 1024);
	~InstrFactory();

	int ParseFile(std::string file_name, Instr* instruction_memory[]);  // returns the number of read instructions 

private:
	Instr* StrtoInstr(std::string instr, int instruction_num);  // it takes 1 assembly line and returns its corresponding instruction object

	opcode decideInstrType(std::string str_opcode);   // takes the instruction name as a string and returns it as an enum for easier Switch case

	// Parsers for different instruction types
	void parseThreeOperandsInstr(std::string str_operands, int& in1, int& in1_type, int& in2, int& in2_type, int& out, int instruction_num);
	void parseTwoOperandInstr(std::string str_operands, int& in, int& in_type, int& out, int instruction_num);
	void parseJmpInstr(std::string str_operands, int& addr, int instruction_num);
	void parseJmp_0Instr(std::string str_operands, int& in, int& in_type, int& out, int instruction_num);
	void parseReadInstr(std::string str_operands, int& addr, int instruction_num);
	void parseWriteInstr(std::string str_operands, int& in, int& in_type, int instruction_num);


	int dataMemorySize; // needed to decide if passed addresses are valid within the data memory range or not 
	int instructionMemorySize; // needed to stop parsing if the number of instructions in file are exceeding the size of the memory 
};


#endif 

