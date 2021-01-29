#ifndef F0INSTRUCTION_HEADER
#define F0INSTRUCTION_HEADER

#include <string>
#include <vector>

#include "../ui/table.h"
#include "instruction.h"

class asmF0Instruction : public asmInstruction{
public:
	asmF0Instruction(std::vector<std::string> tokens);
	int getInstructionSet();
	int getType();
	static int getOpCodeStatic();
	virtual int getOpCode();
	static int getTypeStatic();
	static void addUsage(uiTable* table);
	static asmInstruction* getInstruction(std::vector<std::string> tokens);
	static int isValid(std::vector<std::string> tokens);
};

#endif