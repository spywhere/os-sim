#ifndef F1INSTRUCTION_HEADER
#define F1INSTRUCTION_HEADER

#include <string>
#include <vector>

#include "../ui/table.h"
#include "instruction.h"

class asmF1Instruction : public asmInstruction{
protected:
	int r1;
	int r2;
public:
	asmF1Instruction(std::vector<std::string> tokens);
	int getInstructionSet();
	int getType();
	int getR1();
	int getR2();
	static int getOpCodeStatic();
	virtual int getOpCode();
	static int getTypeStatic();
	static void addUsage(uiTable* table);
	static asmInstruction* getInstruction(std::vector<std::string> tokens);
	static int isValid(std::vector<std::string> tokens);
};

#endif