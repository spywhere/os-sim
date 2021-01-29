#ifndef PROCESSREPORT_HEADER
#define PROCESSREPORT_HEADER

#include "process.h"

class osProcessReport{
private:
	int id;
	int totalWaitTime;
	int totalIOTime;
	int totalTime;
public:
	osProcessReport(osProcess* process);
	int getID();
	int getWaitTime();
	int getIOTime();
	int getTotalTime();
};

#endif