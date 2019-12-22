#include "Instr.h"


AddInstr::AddInstr(int i1_type, int i1_content, int i2_type, int i2_content, int o)
{
	if (i1_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i1_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i1_content;
		// address field is pointless here and won't be used anywhere
	}

	if (i2_type == 1)  // indicates that it's an address
	{
		instr_operands[1].fix = READ_FROM_MEM;
		instr_operands[1].address = i2_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[1].fix = NO_FIX;
		instr_operands[1].value = i2_content;
		// address field is pointless here and won't be used anywhere
	}


	instr_operands[2].fix = NO_FIX;  // will be set to WRITE_TO_MEM after execution once the value is calculated to pass it to the memory
	instr_operands[2].address = o;

}

AddInstr::~AddInstr()
{
}

void AddInstr::FixOperands(DataMemory& data_mem)
{
	for (int i = 0; i < 3; i++)
	{
		if (instr_operands[i].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
		{
			instr_operands[i].value = data_mem.readVal(instr_operands[i].address);
			instr_operands[i].fix = NO_FIX;
		}

		else
			if (instr_operands[i].fix == WRITE_TO_MEM)  // update mem[address] with the value of this operand 
			{
				data_mem.writeVal(instr_operands[i].address, instr_operands[i].value);
				instr_operands[i].fix = NO_FIX;
			}
	}
}

// My convention is that the 2 in operands are put in array fields before the out operand
// Also this function assumes that the processor already called FixOperands and that the inputs value fields are ready for operation
void AddInstr::exec(int& PC, int core_num)
{
	instr_operands[2].value = instr_operands[0].value + instr_operands[1].value;
	instr_operands[2].fix = WRITE_TO_MEM;  // to update the output value in the memory 

	PC += 1;

}


///////////////////////////////////////////////////////////////////////////// New class
MulInstr::MulInstr(int i1_type, int i1_content, int i2_type, int i2_content, int o)
{
	if (i1_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i1_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i1_content;
		// address field is pointless here and won't be used anywhere
	}

	if (i2_type == 1)  // indicates that it's an address
	{
		instr_operands[1].fix = READ_FROM_MEM;
		instr_operands[1].address = i2_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[1].fix = NO_FIX;
		instr_operands[1].value = i2_content;
		// address field is pointless here and won't be used anywhere
	}


	instr_operands[2].fix = NO_FIX;  // will be set to WRITE_TO_MEM after execution once the value is calculated to pass it to the memory
	instr_operands[2].address = o;

}

MulInstr::~MulInstr() {

}

void MulInstr::FixOperands(DataMemory& data_mem)
{
	for (int i = 0; i < 3; i++)
	{
		if (instr_operands[i].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
		{
			instr_operands[i].value = data_mem.readVal(instr_operands[i].address);
			instr_operands[i].fix = NO_FIX;
		}

		else
			if (instr_operands[i].fix == WRITE_TO_MEM)  // update mem[address] with the value of this operand 
			{
				data_mem.writeVal(instr_operands[i].address, instr_operands[i].value);
				instr_operands[i].fix = NO_FIX;
			}
	}
}


void MulInstr::exec(int& PC, int core_num)
{
	instr_operands[2].value = instr_operands[0].value * instr_operands[1].value;
	instr_operands[2].fix = WRITE_TO_MEM;  // to update the output value in the memory 

	PC += 1;
}

///////////////////////////////////////////////////////////////////////////// New class
LeInstr::LeInstr(int i1_type, int i1_content, int i2_type, int i2_content, int o)
{
	if (i1_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i1_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i1_content;
		// address field is pointless here and won't be used anywhere
	}

	if (i2_type == 1)  // indicates that it's an address
	{
		instr_operands[1].fix = READ_FROM_MEM;
		instr_operands[1].address = i2_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[1].fix = NO_FIX;
		instr_operands[1].value = i2_content;
		// address field is pointless here and won't be used anywhere
	}


	instr_operands[2].fix = NO_FIX;  // will be set to WRITE_TO_MEM after execution once the value is calculated to pass it to the memory
	instr_operands[2].address = o;

}


LeInstr::~LeInstr() {

}


void LeInstr::FixOperands(DataMemory& data_mem)
{
	for (int i = 0; i < 3; i++) {
		if (instr_operands[i].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
		{
			instr_operands[i].value = data_mem.readVal(instr_operands[i].address);
			instr_operands[i].fix = NO_FIX;
		}

		else
			if (instr_operands[i].fix == WRITE_TO_MEM)  // update mem[address] with the value of this operand 
			{
				data_mem.writeVal(instr_operands[i].address, instr_operands[i].value);
				instr_operands[i].fix = NO_FIX;
			}
	}
}

void LeInstr::exec(int& PC, int core_num)
{
	if (instr_operands[0].value <= instr_operands[1].value) {
		instr_operands[2].value = 1;
	}

	else {
		instr_operands[2].value = 0;
	}

	instr_operands[2].fix = WRITE_TO_MEM;  // to update the output value in the memory 

	PC += 1;

}

///////////////////////////////////////////////////////////////////////////// New class
NegInstr::NegInstr(int i_type, int i_content, int out)
{
	if (i_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i_content;
		// address field is pointless here and won't be used anywhere
	}

	instr_operands[1].fix = NO_FIX;  // will be set to WRITE_TO_MEM after execution once the value is calculated to pass it to the memory
	instr_operands[1].address = out;
}

NegInstr::~NegInstr()
{

}

void NegInstr::FixOperands(DataMemory& data_mem) {
	for (int i = 0; i < 2; i++) {
		if (instr_operands[i].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
		{
			instr_operands[i].value = data_mem.readVal(instr_operands[i].address);
			instr_operands[i].fix = NO_FIX;
		}

		else
			if (instr_operands[i].fix == WRITE_TO_MEM)  // update mem[address] with the value of this operand 
			{
				data_mem.writeVal(instr_operands[i].address, instr_operands[i].value);
				instr_operands[i].fix = NO_FIX;
			}
	}
}

void NegInstr::exec(int& PC, int core_num) {
	instr_operands[1].value = -1 * instr_operands[0].value;
	instr_operands[1].fix = WRITE_TO_MEM;

	PC += 1;
}


///////////////////////////////////////////////////////////////////////////// New class
AssInstr::AssInstr(int i_type, int i_content, int out)
{
	if (i_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i_content;
		// address field is pointless here and won't be used anywhere
	}

	instr_operands[1].fix = NO_FIX;  // will be set to WRITE_TO_MEM after execution once the value is calculated to pass it to the memory
	instr_operands[1].address = out;
}

AssInstr::~AssInstr() {

}

void AssInstr::FixOperands(DataMemory& data_mem) {
	for (int i = 0; i < 2; i++) {
		if (instr_operands[i].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
		{
			instr_operands[i].value = data_mem.readVal(instr_operands[i].address);
			instr_operands[i].fix = NO_FIX;
		}

		else
			if (instr_operands[i].fix == WRITE_TO_MEM)  // update mem[address] with the value of this operand 
			{
				data_mem.writeVal(instr_operands[i].address, instr_operands[i].value);
				instr_operands[i].fix = NO_FIX;
			}
	}
}

void AssInstr::exec(int& PC, int core_num) {
	instr_operands[1].value = instr_operands[0].value;
	instr_operands[1].fix = WRITE_TO_MEM;

	PC += 1;
}

///////////////////////////////////////////////////////////////////////////// New class
JmpInstr::JmpInstr(int out)
{
	instr_operands[0].fix = NO_FIX;
	instr_operands[0].address = out;
}

JmpInstr::~JmpInstr()
{

}

void JmpInstr::FixOperands(DataMemory& data_mem) {
}

void JmpInstr::exec(int& PC, int core_num) {
	if (PC == instr_operands[0].address) {
		throw JumpAddressException();
	}// don't jump to yourself

	PC = instr_operands[0].address;
}

///////////////////////////////////////////////////////////////////////////// New class
Jmp_0Instr::Jmp_0Instr(int i_type, int i_content, int out)
{
	if (i_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i_content;
		// address field is pointless here and won't be used anywhere
	}

	instr_operands[1].fix = NO_FIX;
	instr_operands[1].address = out;
}

Jmp_0Instr::~Jmp_0Instr()
{

}

void Jmp_0Instr::FixOperands(DataMemory& data_mem)
{
	// the only operand that might need to be read from memory is in, incase it was passed as an address instead of a constant 
	if (instr_operands[0].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
	{
		instr_operands[0].value = data_mem.readVal(instr_operands[0].address);
		instr_operands[0].fix = NO_FIX;
	}
}

void Jmp_0Instr::exec(int& PC, int core_num)
{
	if (PC == instr_operands[1].address) {
		throw JumpAddressException();
	}// don't jump to yourself

	if (instr_operands[0].value == 0) {
		PC = instr_operands[1].address;
	}
	else {
		PC += 1;
	}
}

///////////////////////////////////////////////////////////////////////////// New class
ReadInstr::ReadInstr(int x)
{
	instr_operands[0].fix = NO_FIX;    // Inside exec it'll be set to WRITE_TO_MEM to update the address content with the read value 
	instr_operands[0].address = x;
}

ReadInstr::~ReadInstr()
{

}

void ReadInstr::FixOperands(DataMemory& data_mem)
{
	if (instr_operands[0].fix == WRITE_TO_MEM)  // update mem[address] with the value of this operand 
	{
		data_mem.writeVal(instr_operands[0].address, instr_operands[0].value);
		instr_operands[0].fix = NO_FIX;
	}
}

void ReadInstr::exec(int& PC, int core_num)
{
	printf("\nPlease enter a value for Read Instruction number %d in Core number %d:\n\n", PC, core_num);
	scanf_s("%d", &(instr_operands[0].value));
	instr_operands[0].fix = WRITE_TO_MEM;  // to update this value in data memory after execution
	PC += 1;
}

///////////////////////////////////////////////////////////////////////////// New class
WriteInstr::WriteInstr(int i_type, int i_content)
{
	if (i_type == 1)  // indicates that it's an address
	{
		instr_operands[0].fix = READ_FROM_MEM;
		instr_operands[0].address = i_content;
		// value will remain empty! Should be later filled by the processor 
	}

	else
	{
		instr_operands[0].fix = NO_FIX;
		instr_operands[0].value = i_content;
		// address field is pointless here and won't be used anywhere
	}

}

WriteInstr::~WriteInstr()
{

}

void WriteInstr::FixOperands(DataMemory& data_mem)
{
	if (instr_operands[0].fix == READ_FROM_MEM)  // need to fill the value field of this operand with mem[address]
	{
		instr_operands[0].value = data_mem.readVal(instr_operands[0].address);
		instr_operands[0].fix = NO_FIX;
	}
}

void WriteInstr::exec(int& PC, int core_num)
{
	printf("\nValue required by Write Instruction number %d in Core number %d is %d\n\n", PC, core_num, instr_operands[0].value);
	PC += 1;
}

///////////////////////////////////////////////////////////////////////////// New class
HaltInstr::HaltInstr()
{

}

HaltInstr::~HaltInstr()
{
}

void HaltInstr::FixOperands(DataMemory& data_mem)
{

}

void HaltInstr::exec(int& PC, int core_num)
{
	PC = -1; // this tells the Processor that it has to stop exceuting and return to the main
	// std::cout << "HALT Instruction so will stop the simulator" << std::endl;
}