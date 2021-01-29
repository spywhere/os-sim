#ifndef F1DIV_INST_HEADER
#define F1DIV_INST_HEADER

#include <string>
#include <vector>

#include "../f1instruction.h"

class asmF1DivInstruction : public asmF1Instruction{
public:
	asmF1DivInstruction(std::vector<std::string> tokens);
	std::string getMnemonic();
	int getOpCode();
	static std::string getMnemonicStatic();
	static int getOpCodeStatic();
	static std::string getUsage();
	static int isValid(std::vector<std::string> tokens);
	std::vector<int> run(std::vector<int> registers);
};

#endif