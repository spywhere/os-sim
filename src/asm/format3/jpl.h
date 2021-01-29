#ifndef F3JPL_INST_HEADER
#define F3JPL_INST_HEADER

#include <string>
#include <vector>

#include "../f3instruction.h"

class asmF3JplInstruction : public asmF3Instruction{
public:
	asmF3JplInstruction(std::vector<std::string> tokens);
	std::string getMnemonic();
	int getOpCode();
	static std::string getMnemonicStatic();
	static int getOpCodeStatic();
	static std::string getUsage();
	static int isValid(std::vector<std::string> tokens);
	int getTargetPC(int flag, int pc);
};

#endif