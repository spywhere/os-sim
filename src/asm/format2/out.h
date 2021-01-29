#ifndef F2OUT_INST_HEADER
#define F2OUT_INST_HEADER

#include <string>
#include <vector>

#include "../f2instruction.h"

class asmF2OutInstruction : public asmF2Instruction{
public:
	asmF2OutInstruction(std::vector<std::string> tokens);
	std::string getMnemonic();
	int getOpCode();
	static std::string getMnemonicStatic();
	static int getOpCodeStatic();
	static std::string getUsage();
	static int isValid(std::vector<std::string> tokens);
	int getIOTime(int ioTime);
};

#endif