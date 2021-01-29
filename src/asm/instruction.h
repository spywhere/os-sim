#ifndef INSTRUCTION_HEADER
#define INSTRUCTION_HEADER

#include <string>
#include <vector>

class asmInstruction {
protected:
	int type;
public:
	virtual int getInstructionSet();
	virtual int getSize();
	static int getTypeStatic();
	virtual int getType();
	static std::string getMnemonicStatic();
	virtual std::string getMnemonic();
	virtual int getIOTime(int ioTime);
	virtual int getTargetPC(int flag, int pc);
	virtual std::vector<int> run(std::vector<int> registers);
	static asmInstruction* getInstruction(std::vector<std::string> tokens);
	static int isValid(std::vector<std::string> tokens);
};

#endif