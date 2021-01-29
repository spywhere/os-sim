#ifndef F1CMP_INST_HEADER
#define F1CMP_INST_HEADER

#include <string>
#include <vector>

#include "../f1instruction.h"

class asmF1CmpInstruction : public asmF1Instruction{
public:
	asmF1CmpInstruction(std::vector<std::string> tokens);
	std::string getMnemonic();
	int getOpCode();
	static std::string getMnemonicStatic();
	static int getOpCodeStatic();
	static std::string getUsage();
	static int isValid(std::vector<std::string> tokens);
	std::vector<int> run(std::vector<int> registers);
};

#endif