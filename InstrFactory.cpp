#include "InstrFactory.h"

InstrFactory::InstrFactory(int dataMemorySize, int instructionMemorySize) :dataMemorySize(dataMemorySize), instructionMemorySize(instructionMemorySize)
{
}

InstrFactory::~InstrFactory()
{
}


opcode InstrFactory::decideInstrType(std::string str_opcode)
{
	opcode int_opcode;
	if (str_opcode == "ADD") {
		int_opcode = ADD;
	}
	else {
		if (str_opcode == "NEG") {
			int_opcode = NEG;
		}

		else {
			if (str_opcode == "MUL") {
				int_opcode = MUL;
			}

			else {
				if (str_opcode == "JMP") {
					int_opcode = JMP;
				}

				else {
					if (str_opcode == "JMP0") {
						int_opcode = JMP0;
					}

					else {
						if (str_opcode == "ASS") {
							int_opcode = ASS;
						}

						else {
							if (str_opcode == "LE") {
								int_opcode = LE;
							}

							else {
								if (str_opcode == "READ") {
									int_opcode = READ;
								}

								else {
									if (str_opcode == "WRITE") {
										int_opcode = WRITE;
									}

									else {
										if (str_opcode == "HALT") {
											int_opcode = HALT;
										}

										else {
											int_opcode = UNDEFINED;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}

	return int_opcode;
}

Instr* InstrFactory::StrtoInstr(std::string instr, int instruction_num)  // need to parse the line and extract useful fields from it 
{
	int space_index = instr.find(" ");   // to allocate the opcode 
	std::string str_opcode;
	opcode int_opcode;

	if (space_index != std::string::npos)   // if the white space is found 
	{
		// extract the opcode 
		str_opcode = instr.substr(0, space_index);
		int_opcode = decideInstrType(str_opcode);

		int in1, in2, out;
		int in, in_type;
		int in1_type, in2_type;
		int addr;

		switch (int_opcode) {
		case ADD:
			parseThreeOperandsInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), in1, in1_type, in2, in2_type, out, instruction_num); // consider the operands string only after the whitespace 
			return new AddInstr(in1_type, in1, in2_type, in2, out);

		case MUL:
			parseThreeOperandsInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), in1, in1_type, in2, in2_type, out, instruction_num); // consider the operands string only after the whitespace 
			return new MulInstr(in1_type, in1, in2_type, in2, out);

		case LE:
			parseThreeOperandsInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), in1, in1_type, in2, in2_type, out, instruction_num); // consider the operands string only after the whitespace 
			return new LeInstr(in1_type, in1, in2_type, in2, out);

		case NEG:
			parseTwoOperandInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), in, in_type, out, instruction_num); // consider the operands string only after the whitespace 
			return new NegInstr(in_type, in, out);

		case ASS:
			parseTwoOperandInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), in, in_type, out, instruction_num); // consider the operands string only after the whitespace 
			return new AssInstr(in_type, in, out);

		case JMP:
			parseJmpInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), addr, instruction_num); // consider the operands string only after the whitespace 
			return new JmpInstr(addr);

		case JMP0:
			parseJmp_0Instr(instr.substr(space_index + 1, instr.length() - space_index - 1), in, in_type, out, instruction_num); // consider the operands string only after the whitespace 
			return new Jmp_0Instr(in_type, in, out);

		case READ:
			parseReadInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), addr, instruction_num);
			return new ReadInstr(addr);

		case WRITE:
			parseWriteInstr(instr.substr(space_index + 1, instr.length() - space_index - 1), in, in_type, instruction_num);
			return new WriteInstr(in_type, in);

		case HALT:
			// has no argument so needs no parsing!
			return new HaltInstr();


		case UNDEFINED:
			throw UnsupportedOpcodeException("Instruction number " + std::to_string(instruction_num) + " is an unsupported Instruction!");   // !!!!!! raise exception!!!! unsupported instruction opcode !!!

		}

	}

	else
	{
		// wrong format 
		throw WrongInstrFormatException("Opcode in instruction number " + std::to_string(instruction_num) + " must be followed by a white space!");  // !!!!!! raise exception!!!! wrong format in the instruction, opcode must be followed by an empty space !!!
	}

}


// parses all instructions that take 2 input values and a single output value 
void InstrFactory::parseThreeOperandsInstr(std::string str_operands, int& in1, int& in1_type, int& in2, int& in2_type, int& out, int instruction_num) {
	std::string str_in1, str_in2, str_out;

	// Extract the 3 strings representing each of the 2 inputs as well as the output string 
	int index = str_operands.find(",");

	if (index != std::string::npos) {  // if the ',' is found
		if (index == 0 || index == str_operands.length() - 1) {  // this indicates that at least 1 of the 3 required operands is missing!!
			throw WrongInstrFormatException("Missing Operands for instruction number " + std::to_string(instruction_num) + "!");  // !!!!!! raise exception!!!! instruction is missing 1 or more operands!!!
		}

		// Extracting the 1st operand appearing before the ','
		str_in1 = str_operands.substr(0, index);

		// Checking if in1 address or value
		int dollar_index = str_in1.find("$");
		if (dollar_index == std::string::npos) {  // didn't find it so it's a value not address
			in1 = stoi(str_in1);
			in1_type = 0;  // indicating that it's a value not an address
		}

		else {  // found it so it's an address
			int temp_address = stoi(str_in1.substr(dollar_index + 1, str_in1.length() - dollar_index - 1));

			if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
				throw WrongMemoryAddressException(" Data Memory Address must be > 0 and < " + std::to_string(dataMemorySize) + "in instruction number " + std::to_string(instruction_num) + "!");  // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
			}

			in1 = temp_address;
			in1_type = 1; // indicating that it's an address not a value 
		}


		// searching for the next ',' preceding th 2nd operand 
		str_operands = str_operands.substr(index + 1, str_operands.length() - index - 1);
		index = str_operands.find(",");

		if (index != std::string::npos) {  // if the ',' is found
			if (index == 0 || index == str_operands.length() - 1) {  // this indicates that at least 1 of the 3 required operands is missing!!
				throw WrongInstrFormatException("Missing Operands for instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! instruction is missing 1 or more operands!!!
			}

			// Extracting the 2nd operand appearing before the ','
			str_in2 = str_operands.substr(0, index);

			// checking if in2 is address or value
			dollar_index = str_in2.find("$");
			if (dollar_index == std::string::npos) {  // didn't find it so it's a value not address
				in2 = stoi(str_in2);
				in2_type = 0;  // indicating that it's a value not an address
			}

			else {  // found it so it's an address
				int temp_address = stoi(str_in2.substr(dollar_index + 1, str_in2.length() - dollar_index - 1));

				if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
					throw WrongMemoryAddressException(" Data Memory Address must be > 0 and < " + std::to_string(dataMemorySize) + "in instruction number " + std::to_string(instruction_num) + "!");  // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
				}

				in2 = temp_address;
				in2_type = 1; // indicating that it's an address not a value 
			}


			// extracting the last operand after the 2nd ','
			str_out = str_operands.substr(index + 1, str_operands.length() - index - 1);
			dollar_index = str_out.find("$");
			if (dollar_index == std::string::npos) {  // didn't find it error!!
				throw WrongInstrFormatException("Output Operand must be sent as an address in the Data Memory not a constant in instruction number " + std::to_string(instruction_num) + "!");  // !!!!!! raise exception!!!! out operand must be an address!!!
			}

			else {  // it's an address, need to check that it's within the proper range
				int temp_address = stoi(str_out.substr(dollar_index + 1, str_out.length() - dollar_index - 1));

				if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
					throw WrongMemoryAddressException(" Data Memory Address must be > 0 and < " + std::to_string(dataMemorySize) + "in instruction number " + std::to_string(instruction_num) + "!");  // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
				}

				out = temp_address;
			}

		}
		else {
			throw WrongInstrFormatException("Operands in instruction number " + std::to_string(instruction_num) + " must be separated by a ','!");   // !!!!!! raise exception!!!! wrong format in the instruction, missing a ',' !!!
		}


	}
	else {
		throw WrongInstrFormatException("Operands in instruction number " + std::to_string(instruction_num) + " must be separated by a ','!");  // !!!!!! raise exception!!!! wrong format in the instruction, missing a ',' !!!
	}

}

void InstrFactory::parseTwoOperandInstr(std::string str_operands, int& in, int& in_type, int& out, int instruction_num) {
	std::string str_in, str_out;

	// extract the 2 strings representing each of the input and output
	int index = str_operands.find(",");

	if (index != std::string::npos) {  // if the , is found
		if (index == 0 || index == str_operands.length() - 1) {  // this indicates that at least 1 of the 2 required operands is missing!!
			throw WrongInstrFormatException("Missing Operands for instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! instruction is missing 1 or more operands!!!
		}

		// if it passed up to here then we are sure that there are 2 operands 

		// reading the first operand existing before the ,
		str_in = str_operands.substr(0, index);

		// checking if the operand is address or value
		int dollar_index = str_in.find("$");
		if (dollar_index == std::string::npos) {  // didn't find it so it's a value not address
			in = stoi(str_in);
			in_type = 0;  // indicating that it's a value not an address
		}

		else {  // found $ so it's an address
			// Extract the address coming after the $
			int temp_address = stoi(str_in.substr(dollar_index + 1, str_in.length() - dollar_index - 1));

			if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
				throw WrongMemoryAddressException(" Data Memory Address must be > 0 and < " + std::to_string(dataMemorySize) + "in instruction number " + std::to_string(instruction_num) + "!");   // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
			}

			in = temp_address;
			in_type = 1; // indicating that it's an address not a value 
		}

		// Extract the operand coming after the ,
		str_out = str_operands.substr(index + 1, str_operands.length() - index - 1);
		dollar_index = str_out.find("$");
		if (dollar_index == std::string::npos) {  // the out operand isn't passed as an address, which isn't allowed
			throw WrongInstrFormatException(" Output Operand must be sent as an address in the Data Memory not a constant in instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! out operand must be an address!!!
		}

		else {  // it's an address, need to check that it's within the proper range
			// Extract the address coming after the $
			int temp_address = stoi(str_out.substr(dollar_index + 1, str_out.length() - dollar_index - 1));

			if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
				throw WrongMemoryAddressException(" Data Memory Address must be > 0 and < " + std::to_string(dataMemorySize) + "in instruction number " + std::to_string(instruction_num) + "!");  // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
			}

			out = temp_address;
		}

	}
	else {   // missing ','
		throw WrongInstrFormatException(" Operands in instruction number " + std::to_string(instruction_num) + " must be separated by a ','!");   // !!!!!! raise exception!!!! wrong format in the instruction, missing a ',' !!!
	}

}

void InstrFactory::parseJmpInstr(std::string str_operands, int& addr, int instruction_num) {
	// must make sure that the passed operand is an address and that it's within the instruction memory range 
	int temp_addr;
	// extract the string representing the instr_mem address to move to 
	int index = str_operands.find("$");

	if (index == 0) {  // if the $ is found in the beginning, then it's an address
		temp_addr = stoi(str_operands.substr(index + 1, str_operands.length() - index - 1));

		// Check that this address is within the size of the instruction Memory!
		if (temp_addr < 0 || temp_addr >= instructionMemorySize) {  // invalid address index
			throw WrongMemoryAddressException(" Can't Jump to an address that is not within the range of the Instruction Memory in instruction number " + std::to_string(instruction_num) + "!");   // !!!!!! raise exception!!!! passed address is out of range of the Instruction memory !!!
		}

		addr = temp_addr;

	}
	else {   // it's not an address
		throw WrongInstrFormatException(" Jump Instr Operand must be sent as an address in the Instruction Memory not a constant in instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! out operand must be an address!!!
	}
}

void InstrFactory::parseJmp_0Instr(std::string str_operands, int& in, int& in_type, int& out, int instruction_num) {
	std::string str_in, str_out;

	// extract the 2 strings representing each of the input and output
	int index = str_operands.find(",");

	if (index != std::string::npos) {  // if the , is found
		if (index == 0 || index == str_operands.length() - 1) {  // this indicates that at least 1 of the 2 required operands is missing!!
			throw WrongInstrFormatException("Missing Operands for instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! instruction is missing 1 or more operands!!!
		}

		// if it passed up to here then we are sure that there are 2 operands 

		// reading the first operand existing before the ,
		str_in = str_operands.substr(0, index);

		// checking if the operand is address or value
		int dollar_index = str_in.find("$");
		if (dollar_index == std::string::npos) {  // didn't find it so it's a value not address
			in = stoi(str_in);
			in_type = 0;  // indicating that it's a value not an address
		}

		else {  // found $ so it's an address
			// Extract the address coming after the $
			int temp_address = stoi(str_in.substr(dollar_index + 1, str_in.length() - dollar_index - 1));

			if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
				throw WrongMemoryAddressException(" Data Memory Address must be > 0 and < " + std::to_string(dataMemorySize) + "in instruction number " + std::to_string(instruction_num) + "!");   // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
			}

			in = temp_address;
			in_type = 1; // indicating that it's an address not a value 
		}

		// Extract the operand coming after the ,
		str_out = str_operands.substr(index + 1, str_operands.length() - index - 1);
		dollar_index = str_out.find("$");
		if (dollar_index == std::string::npos) {  // the out operand isn't passed as an address, which isn't allowed
			throw WrongInstrFormatException("Output Operand must be sent as an address from the Instruction Memory not a constant in instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! out operand must be an address!!!
		}

		else {  // it's an address, need to check that it's within the proper range
			// Extract the address coming after the $
			int temp_address = stoi(str_out.substr(dollar_index + 1, str_out.length() - dollar_index - 1));

			// Check that this address is within the size of the instruction Memory!
			if (temp_address < 0 || temp_address >= instructionMemorySize) {  // invalid address index
				throw WrongMemoryAddressException(" Can't Jump to an address that is not within the range of the Instruction Memory in instruction number " + std::to_string(instruction_num) + "!");   // !!!!!! raise exception!!!! passed address is out of range of the Instruction memory !!!
			}

			out = temp_address;
		}

	}
	else {   // missing ','
		throw WrongInstrFormatException(" Operands in instruction number " + std::to_string(instruction_num) + " must be separated by a ','!");   // !!!!!! raise exception!!!! wrong format in the instruction, missing a ',' !!!
	}

}

void InstrFactory::parseReadInstr(std::string str_operands, int& addr, int instruction_num) {
	// must make sure that the passed operand is an address and that it's within the data memory range 
	int temp_addr;
	// extract the string representing the data_mem address to move to 
	int index = str_operands.find("$");

	if (index == 0) {  // if the $ is found in the beginning, then it's an address
		temp_addr = stoi(str_operands.substr(index + 1, str_operands.length() - index - 1));

		// Check that this address is within the size of the instruction Memory!
		if (temp_addr < 0 || temp_addr >= dataMemorySize) {  // invalid address index
			throw WrongMemoryAddressException("Can't Read from an address that is not within the range of the Data Memory in instruction number " + std::to_string(instruction_num) + "!");   // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
		}

		addr = temp_addr;

	}
	else {   // it's not an address
		throw WrongInstrFormatException("Read Instr Operand must be sent as an address in the Data Memory not a constant in instruction number " + std::to_string(instruction_num) + "!"); // !!!!!! raise exception!!!! out operand must be an address!!!
	}
}

void InstrFactory::parseWriteInstr(std::string str_operands, int& in, int& in_type, int instruction_num) {
	// checking if the operand is address or value
	int dollar_index = str_operands.find("$");
	if (dollar_index == std::string::npos) {  // didn't find it so it's a value not address
		in = stoi(str_operands);
		in_type = 0;  // indicating that it's a value not an address
	}

	else {  // found $ so it's an address
		// Extract the address coming after the $
		int temp_address = stoi(str_operands.substr(dollar_index + 1, str_operands.length() - dollar_index - 1));

		if (temp_address < 0 || temp_address >= dataMemorySize) {  // invalid address index
			throw WrongMemoryAddressException(" Read Instruction must read from a valid Data Memory Address in instruction number " + std::to_string(instruction_num) + "!");   // !!!!!! raise exception!!!! passed address is out of range of the data memory !!!
		}

		in = temp_address;
		in_type = 1; // indicating that it's an address not a value 
	}
}


int InstrFactory::ParseFile(std::string file_name, Instr* instruction_memory[]) {
	std::ifstream input_file_stream;
	std::string instruction_line;

	std::string last_line;

	int instruction_num = 0;

	// Open the file 
	input_file_stream.open(file_name);

	// check if the file wasn't successfully opened, raise exception
	if (input_file_stream.is_open()) {  // the file was successfully opened 
		while (getline(input_file_stream, instruction_line) && (instruction_num < instructionMemorySize)) {   // read a single instruction as a string 
			last_line = instruction_line;
			if (!instruction_line.empty()) {   // if the parsed line isn't empty 
				instruction_memory[instruction_num] = StrtoInstr(instruction_line, instruction_num);
				instruction_num += 1;
			}

			// ignore empty lines 
		}

		input_file_stream.close(); // closing the file 


		if (instruction_num == instructionMemorySize) {
			throw WrongMemoryAddressException(" Exceeded the size of the Instruction Memory! Can't load instructions anymore! ");  //!!!!!!!! need to raise an exception indicating that the size of instruction memory is exceeded!!!
		}

		// You might need to use this output just for debugging 
		//std::cout << "The last instruction is " << last_line << std::endl;

		// If you didn't exceed the size of the instruction memory, you are good, 
		// check if the last instruction is a Halt or else raise an exception
		int space_index = last_line.find(" ");   // to allocate the opcode 
		std::string str_opcode = last_line.substr(0, space_index);
		if (str_opcode != "HALT") {   // checking on the opcode of the last instruction 
			throw HaltException();
		}

	}

	else {
		throw FileAccessException();   //!!!!!!!!!!!! need to raise an exception indicating that the file wasn't read!!!
	}

	return (instruction_num);

}
