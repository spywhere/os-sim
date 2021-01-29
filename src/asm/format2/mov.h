#ifndef F2MOV_INST_HEADER
#define F2MOV_INST_HEADER

#include <string>
#include <vector>

#include "../f2instruction.h"

class asmF2MovInstruction : public asmF2Instruction{
public:
	asmF2MovInstruction(std::vector<std::string> tokens);
	std::string getMnemonic();
	int getOpCode();
	static std::string getMnemonicStatic();
	static int getOpCodeStatic();
	static std::string getUsage();
	static int isValid(std::vector<std::string> tokens);
	std::vector<int> run(std::vector<int> registers);
};

#endif