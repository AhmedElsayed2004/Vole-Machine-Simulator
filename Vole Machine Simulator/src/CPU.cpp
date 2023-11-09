#include "CPU.h"


CPU::CPU()
{
	m_validInstructions[0] = "1RXY";
	m_validInstructions[1] = "2RXY";
	m_validInstructions[2] = "3RXY";
	m_validInstructions[3] = "40RS";
	m_validInstructions[4] = "5RST";
	m_validInstructions[5] = "6RST";
	m_validInstructions[6] = "BRXY";
	m_validInstructions[7] = "C000";
}

int CPU::ToDecimal(std::string HEX)
{
	int decimal = 0, power = 1;
	for (int i = 0;i < HEX.size();++i)
	{
		if (HEX[i] >= '1' && HEX[i] <= '9') decimal += HEX[i] - '0';
		else decimal += HEX[i] - 'A' + 10;
		decimal *= power;
		power *= 16;
	}
	return decimal;
}
std::string CPU::ToHEX(int number)
{
	std::string result = "";
	while (number)
	{
		int m = number % 16;
		if (m >= 10) result.push_back('A' + m - 10);
		else result.push_back(m + '0');
		number /= 16;
	}
	std::reverse(result.begin(), result.end());
	return result;
}

Byte CPU::add(Byte b1, Byte b2)
{
	std::string HEXNum1 = "";
	std::string HEXNum2 = "";
	HEXNum1.push_back(b1.nibble[0]);
	HEXNum1.push_back(b1.nibble[1]);
	HEXNum2.push_back(b2.nibble[0]);
	HEXNum2.push_back(b2.nibble[1]);
	int num1 = ToDecimal(HEXNum1);
	int num2 = ToDecimal(HEXNum2);
	int adding = num1 + num2;
	adding &= ((1 << 8) - 1);
	std::string HEXAdding = ToHEX(adding);

	Byte result;
	if (HEXAdding.size() == 1)
	{
		result.nibble[0] = '0';
		result.nibble[1] = HEXAdding[0];
	}
	else
	{
		result.nibble[0] = HEXAdding[0];
		result.nibble[1] = HEXAdding[1];
	}

	return result;

}
void CPU::FetchInstruction(int& programCounter)
{
	m_IR[0] = (m_memory + programCounter)->nibble[0];
	m_IR[1] = (m_memory + programCounter)->nibble[1];
	m_IR[2] = (m_memory + programCounter + 1)->nibble[0];
	m_IR[3] = (m_memory + programCounter + 1)->nibble[1];
}

bool CPU::IsValidInstruction()
{
	for (auto& instruction : m_validInstructions)
	{
		if (m_IR[0] == instruction[0])
		{
			for (int i = 0;i < 4;++i)
			{
				if (instruction[i] == 'R' || instruction[i] == 'S' || instruction[i] == 'T' || instruction[i] == 'X' || instruction[i] == 'Y')
				{
					if (!(m_IR[i] >= '0' && m_IR[i] <= '9') || !(m_IR[i] >= 'A' && m_IR[i] <= 'F')) return false;
				}
				else
				{
					if (m_IR[0] != instruction[i]) return false;
				}
			}
			return true;
		}
	}

}

void CPU::ExecuteInstruction()
{
	if (m_IR[0] == '1')
	{
		std::string numberOfRegister = "";
		std::string address = "";
		numberOfRegister.push_back(m_IR[1]);
		address.push_back(m_IR[2]);
		address.push_back(m_IR[3]);
		m_register[ToDecimal(numberOfRegister)] = *(m_memory + ToDecimal(address));
	}
	if (m_IR[0] == '2')
	{
		std::string numberOfRegister = "";
		Byte bitPattern;
		numberOfRegister.push_back(m_IR[1]);
		bitPattern.nibble[0] = m_IR[2];
		bitPattern.nibble[1] = m_IR[3];
		m_register[ToDecimal(numberOfRegister)] = bitPattern;
	}
	if (m_IR[0] == '3')
	{
		std::string numberOfRegister = "";
		std::string address = "";
		numberOfRegister.push_back(m_IR[1]);
		address.push_back(m_IR[2]);
		address.push_back(m_IR[3]);
		*(m_memory + ToDecimal(address)) = m_register[ToDecimal(numberOfRegister)];
	}
	if (m_IR[0] == '4')
	{
		std::string numberOfRegister1 = "";
		std::string numberOfRegister2 = "";
		numberOfRegister1.push_back(m_IR[2]);
		numberOfRegister2.push_back(m_IR[3]);
		m_register[ToDecimal(numberOfRegister2)] = m_register[ToDecimal(numberOfRegister1)];
	}
	if (m_IR[0] == '5')
	{
		std::string numberOfRegister1 = "";
		std::string numberOfRegister2 = "";
		std::string numberOfRegister3 = "";
		numberOfRegister1.push_back(m_IR[1]);
		numberOfRegister2.push_back(m_IR[2]);
		numberOfRegister2.push_back(m_IR[3]);
		m_register[ToDecimal(numberOfRegister1)] = add(m_register[ToDecimal(numberOfRegister2)], m_register[ToDecimal(numberOfRegister3)]);
	}
	if (m_IR[0] == '6')
	{

	}
	if (m_IR[0] == 'B')
	{

	}
	if (m_IR[0] == 'C')
	{
		m_isHalt = true;
	}


}