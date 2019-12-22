#ifndef SIMULATOR_EXCEPTIONS_H
#define SIMULATOR_EXCEPTIONS_H

#include <stdexcept>
#include <string>

// If the format of an instruction isn't abiding to the convention OPCODE operand1,operand2,....,operandi
class WrongInstrFormatException : public std::invalid_argument {
public:
	WrongInstrFormatException(std::string specific_error = "") : std::invalid_argument("Instruction with wrong format was found!" + specific_error) {
	}

};

class UnsupportedOpcodeException : public std::invalid_argument {
public:
	UnsupportedOpcodeException(std::string specific_error = "") : std::invalid_argument("Wrong Opcode! " + specific_error) {
	}

};

class WrongMemoryAddressException : public std::out_of_range {
public:
	WrongMemoryAddressException(std::string specific_error = "") : std::out_of_range("Attempt to access a wrong memory address!" + specific_error) {
	}

};

class FileAccessException : public std::invalid_argument {
public:
	FileAccessException() : std::invalid_argument("Failed to open the .txt file!!") {
	}

};

class JumpAddressException : public std::invalid_argument {
public:
	JumpAddressException() : std::invalid_argument("Can't Jump to the same instruction's address!!") {
	}
};

class HaltException : public std::invalid_argument {
public:
	HaltException() : std::invalid_argument("The last instruction in your file should be a Halt instruction!!") {
	}

};


class WrongNException : public std::invalid_argument {
public:
	WrongNException(std::string msg) : std::invalid_argument(msg) {
	}

};


#endif
