#include "process.h"

#include <sstream>
#include "../asm/f0instruction.h"
#include "../asm/f1instruction.h"
#include "../asm/f2instruction.h"
#include "../asm/f3instruction.h"
#include "../asm/format0/halt.h"
#include "../ui/table.h"
#include "../utils.h"

osProcess::osProcess(int id, std::string name, std::vector<asmInstruction*> insts, int startPC){
	this->id = id;
	this->name = name;
	this->pc = 0;
	this->startPC = startPC;
	this->ioTime = -1;
	this->totalWaitTime = 0;
	this->totalIOTime = 0;
	this->totalTime = 0;
	this->insts = insts;
	this->returnCode = -1;
	this->terminated = false;
}

bool osProcess::isTerminated(){
	return this->terminated;
}

bool osProcess::isUsingIO(){
	return this->ioTime > 0;
}

std::string osProcess::getName(){
	return this->name;
}

int osProcess::getID(){
	return this->id;
}

int osProcess::getWaitTime(){
	return this->totalWaitTime;
}

int osProcess::getIOTime(){
	return this->totalIOTime;
}

int osProcess::getTotalTime(){
	return this->totalTime;
}

asmInstruction* osProcess::fetchInstruction(){
	if(this->pc<this->insts.size()){
		return this->insts[this->pc];
	}
	return NULL;
}

int osProcess::getPC(){
	return this->startPC+this->pc;
}

int osProcess::getSize(){
	int size = 0;
	for (std::vector<asmInstruction*>::iterator i = this->insts.begin(); i != this->insts.end(); ++i){
		size+=(*i)->getSize();
	}
	return size;
}

int osProcess::getReturnCode(){
	return this->returnCode;
}

void osProcess::wait(){
	this->totalTime++;
	if(this->isUsingIO()){
		this->totalIOTime++;
		this->ioTime--;
	}else{
		this->totalWaitTime++;
	}
}

std::vector<int> osProcess::run(Logger logger, std::vector<int> registers){
	if(this->terminated){
		return registers;
	}
	returnCode = 0;
	this->totalTime++;
	this->terminated = this->fetchInstruction()->getMnemonic()==asmF0HaltInstruction::getMnemonicStatic();
	this->ioTime = this->fetchInstruction()->getIOTime(this->ioTime);
	registers = this->fetchInstruction()->run(registers);
	this->pc = this->fetchInstruction()->getTargetPC(registers[0], this->pc);
	return registers;
}

bool osProcess::kill(){
	this->terminated = true;
	this->returnCode = -1;
	return this->terminated;
}

void osProcess::saveState(std::vector<int> registers){
	this->registers = registers;
}

std::vector<int> osProcess::loadState(){
	return this->registers;
}

void osProcess::printStatus(Logger logger){
	uiTable* table = new uiTable(logger);
	table->addColumn("Line", UITABLE_RIGHT);
	table->addColumn("Mnemonic", UITABLE_RIGHT);
	table->addColumn("   ", UITABLE_CENTER);
	table->addColumn("Param1", UITABLE_LEFT);
	table->addColumn("Param2", UITABLE_LEFT);
	table->addColumn("Type", UITABLE_CENTER);
	table->addColumn("Instruction Set", UITABLE_CENTER);
	int ln=0;
	std::vector<std::string> row;
	for (std::vector<asmInstruction*>::iterator i = this->insts.begin(); i != this->insts.end(); ++i){
		ln++;
		row.clear();
		row.push_back("#" + toString(ln) + ":");

		asmInstruction* inst = *i;
		row.push_back(inst->getMnemonic());
		row.push_back("");
		if(inst->getType()==0){
			asmF0Instruction* f0inst = (asmF0Instruction*)inst;
			row.push_back("");
			row.push_back("");
		}else if(inst->getType()==1){
			asmF1Instruction* f1inst = (asmF1Instruction*)inst;
			row.push_back("r"+ toString(f1inst->getR1()) + ",");
			row.push_back("r"+ toString(f1inst->getR2()));
		}else if(inst->getType()==2){
			asmF2Instruction* f2inst = (asmF2Instruction*)inst;
			if(f2inst->isLtoR()){
				row.push_back("r"+ toString(f2inst->getR1()) + ",");
				row.push_back("#" + toString(f2inst->getImmediate()));
			}else{
				row.push_back("#" + toString(f2inst->getImmediate()) + ",");
				row.push_back("r"+ toString(f2inst->getR1()));
			}
		}else if(inst->getType()==3){
			asmF3Instruction* f3inst = (asmF3Instruction*)inst;
			row.push_back(toString(f3inst->getAddress()));
			row.push_back("");
		}
		row.push_back(toString(inst->getType()));
		row.push_back(binString(inst->getInstructionSet()>>24, 8) + " " + binString(inst->getInstructionSet()>>16, 8) + " " + binString(inst->getInstructionSet()>>8, 8) + " " + binString(inst->getInstructionSet(), 8)+ "b");
		table->addRow(row);
	}
	table->print();
}