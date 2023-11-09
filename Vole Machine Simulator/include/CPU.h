#pragma once
#include "Byte.h"
#include<string>
class CPU
{
private:
	Byte m_register[15];
	int m_programCounter;
	Byte* m_memory;
	std::string m_IR;
	std::string m_validInstructions[8];
	bool m_isHalt = false;
	int ToDecimal(std::string HEX);
	std::string ToHEX(int number);
	Byte add(Byte b1, Byte b2);
public:
	CPU();
	void FetchInstruction(int& programCounter);
	bool IsValidInstruction();
	void ExecuteInstruction();


};

