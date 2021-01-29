#ifndef F2INSTRUCTION_HEADER
#define F2INSTRUCTION_HEADER

#include <string>
#include <vector>

#include "../ui/table.h"
#include "instruction.h"

class asmF2Instruction : public asmInstruction{
protected:
	int r1;
	int imm;
	bool ltr;
public:
	asmF2Instruction(std::vector<std::string> tokens);
	int getInstructionSet();
	int getType();
	int getR1();
	int getImmediate();
	bool isLtoR();
	static int getOpCodeStatic();
	virtual int getOpCode();
	static int getTypeStatic();
	static void addUsage(uiTable* table);
	static asmInstruction* getInstruction(std::vector<std::string> tokens);
	static int isValid(std::vector<std::string> tokens);
};

#endif