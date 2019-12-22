#ifndef INSTR_H
#define INSTR_H

#include <iostream>
#include "SimulatorExceptions.h"
#include "DataMemory.h"



enum FixType
{
	READ_FROM_MEM,  // needs to read values from memory at its address
	WRITE_TO_MEM,   // needs to fill the memory address with its value 
	NO_FIX   // needs no fixing 
};


struct operand
{
	int value;
	int address;
	FixType fix;
};

class Instr    // Abstract/ Interface class 
{
public:
	virtual void exec(int&, int) = 0;
	virtual void FixOperands(DataMemory&) = 0;

};

class AddInstr : public Instr
{
public:
	AddInstr(int i1_type, int i1_content, int i2_type, int i2_content, int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~AddInstr();

private:
	operand instr_operands[3];  // because this type of instruction has 3 operands 

};

class MulInstr : public Instr
{
public:
	MulInstr(int i1_type, int i1_content, int i2_type, int i2_content, int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~MulInstr();

private:
	operand instr_operands[3];  // because this type of instruction has 3 operands 

};

class LeInstr : public Instr
{
public:
	LeInstr(int i1_type, int i1_content, int i2_type, int i2_content, int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~LeInstr();

private:
	operand instr_operands[3];  // because this type of instruction has 3 operands 

};

class NegInstr : public Instr
{
public:
	NegInstr(int i_type, int i_content, int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~NegInstr();

private:
	operand instr_operands[2];  // because this type of instruction has just 2 operands 

};

class AssInstr : public Instr
{
public:
	AssInstr(int i_type, int i_content, int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~AssInstr();

private:
	operand instr_operands[2];  // because this type of instruction has just 2 operands 

};

class JmpInstr : public Instr
{
public:
	JmpInstr(int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~JmpInstr();

private:
	operand instr_operands[1];  // because this type of instruction has just 1 operand

};

class Jmp_0Instr : public Instr
{
public:
	Jmp_0Instr(int i_type, int i_content, int out);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~Jmp_0Instr();

private:
	operand instr_operands[2];  // because this type of instruction has just 2 operands

};

class ReadInstr : public Instr
{
public:
	ReadInstr(int x);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~ReadInstr();

private:
	operand instr_operands[1];  // because this type of instruction has just 1 operand

};

class WriteInstr : public Instr
{
public:
	WriteInstr(int i_type, int i_content);
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~WriteInstr();

private:
	operand instr_operands[1];  // because this type of instruction has just 1 operand

};

class HaltInstr : public Instr
{
public:
	HaltInstr();
	void exec(int& PC, int core_num);
	void FixOperands(DataMemory&);
	~HaltInstr();

	//  this type of instruction has just no operands 

};

#endif