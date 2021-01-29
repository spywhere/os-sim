#ifndef OS_HEADER
#define OS_HEADER

#include <vector>
#include <list>
#include "asm/instruction.h"
#include "os/process.h"
#include "os/processReport.h"
#include "logger.h"

class osOS {
private:
	int workTime;
	int totalTime;
	int totalMemory;
	int pcEnd;
	int timeQuantum;
	int currentTimeQuantum;
	osProcess* currentProcess;
	bool traceMode;
	bool showOSInfo;
	bool stepInfo;
	Logger logger;
	std::list<osProcess*> processes;
	std::list<osProcessReport*> processReport;
	std::vector<int> registers;
	int newProcessID();
	void printSummary();
	void showRegisters();
public:
	osOS(Logger logger);
	void reinit();
	int getUsedMemory();
	int load(std::string filename);
	osProcess* getCurrentProcess();
	osProcess* getProcess(int procno);
	void showInfo();
	void hideInfo();
	void showStepInfo();
	void hideStepInfo();
	void enableTraceMode();
	void disableTraceMode();
	void useRoundRobin(int timeQuantum);
	void useFCFS();
	bool step();
	void showStatus();
};

#endif