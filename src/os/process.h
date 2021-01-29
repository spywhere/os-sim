#ifndef PROCESS_HEADER
#define PROCESS_HEADER

#include <string>
#include <vector>
#include "../asm/instruction.h"
#include "../logger.h"

class osProcess{
private:
	std::vector<int> registers;
	std::string name;
	int returnCode;
	int id;
	int pc;
	int ioTime;
	int totalWaitTime;
	int totalIOTime;
	int totalTime;
	int startPC;
	// int startAddress;
	bool terminated;
	std::vector<asmInstruction*> insts;
public:
	osProcess(int id, std::string name, std::vector<asmInstruction*> insts, int startPC);
	asmInstruction* fetchInstruction();
	std::vector<int> run(Logger logger, std::vector<int> registers);
	std::string getName();
	bool kill();
	void wait();
	int getPC();
	int getID();
	int getSize();
	int getReturnCode();
	int getWaitTime();
	int getIOTime();
	int getTotalTime();
	bool isTerminated();
	bool isUsingIO();
	void printStatus(Logger logger);
	void saveState(std::vector<int> registers);
	std::vector<int> loadState();
};

#endif