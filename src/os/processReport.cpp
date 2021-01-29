#include "processReport.h"

osProcessReport::osProcessReport(osProcess* process){
	this->id = process->getID();
	this->totalWaitTime = process->getWaitTime();
	this->totalIOTime = process->getIOTime();
	this->totalTime = process->getTotalTime();
}

int osProcessReport::getID(){
	return this->id;
}

int osProcessReport::getWaitTime(){
	return this->totalWaitTime;
}

int osProcessReport::getIOTime(){
	return this->totalIOTime;
}

int osProcessReport::getTotalTime(){
	return this->totalTime;
}