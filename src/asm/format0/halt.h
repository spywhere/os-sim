#ifndef F0HALT_INST_HEADER
#define F0HALT_INST_HEADER

#include <string>
#include <vector>

#include "../f0instruction.h"

class asmF0HaltInstruction : public asmF0Instruction{
public:
	asmF0HaltInstruction(std::vector<std::string> tokens);
	std::string getMnemonic();
	int getOpCode();
	static std::string getMnemonicStatic();
	static int getOpCodeStatic();
	static std::string getUsage();
	static int isValid(std::vector<std::string> tokens);
};

#endif