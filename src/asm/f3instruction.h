#ifndef F3INSTRUCTION_HEADER
#define F3INSTRUCTION_HEADER

#include <string>
#include <vector>

#include "../ui/table.h"
#include "instruction.h"

class asmF3Instruction : public asmInstruction{
protected:
	int address;
public:
	asmF3Instruction(std::vector<std::string> tokens);
	int getInstructionSet();
	int getType();
	int getAddress();
	static int getOpCodeStatic();
	virtual int getOpCode();
	static int getTypeStatic();
	static void addUsage(uiTable* table);
	static asmInstruction* getInstruction(std::vector<std::string> tokens);
	static int isValid(std::vector<std::string> tokens);
};

#endif