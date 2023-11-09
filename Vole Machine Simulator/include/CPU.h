#pragma once
#include "Byte.h"
#include<string>

class CPU
{
private:
	Byte m_register[15];
	Byte* m_memory;
	std::string m_IR;
	std::string m_validInstructions[8];
	int ToDecimal(std::string HEX);
	std::string ToHEX(int number);
	Byte add(Byte b1, Byte b2);
public:
	bool isHalt = false;
	int programCounter{};
	CPU();
	void FetchInstruction();
	bool IsValidInstruction();
	void ExecuteInstruction();
	void ResetCPU();

};

