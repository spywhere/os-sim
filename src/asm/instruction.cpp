#include "instruction.h"
#include "f0instruction.h"
#include "f1instruction.h"
#include "f2instruction.h"
#include "f3instruction.h"

int asmInstruction::getInstructionSet(){
	//Pure virtual
	return -1;
}

int asmInstruction::getSize(){
	return 4;
}

int asmInstruction::getTypeStatic(){
	return -1;
}

int asmInstruction::getType(){
	return asmInstruction::getTypeStatic();
}

std::string asmInstruction::getMnemonic(){
	return asmInstruction::getMnemonicStatic();
}

std::string asmInstruction::getMnemonicStatic(){
	return std::string("");
}

asmInstruction* asmInstruction::getInstruction(std::vector<std::string> tokens){
	int valid=asmInstruction::isValid(tokens);
	if(valid==1){
		return asmF0Instruction::getInstruction(tokens);
	}else if(valid==2){
		return asmF1Instruction::getInstruction(tokens);
	}else if(valid==4){
		return asmF2Instruction::getInstruction(tokens);
	}else if(valid==8){
		return asmF3Instruction::getInstruction(tokens);
	}
	return NULL;
}

std::vector<int> asmInstruction::run(std::vector<int> registers){
	//Pure virtual
	return registers;
}

int asmInstruction::getIOTime(int ioTime){
	//Pure virtual
	return ioTime;
}

int asmInstruction::getTargetPC(int flag, int pc){
	return ++pc;
}

int asmInstruction::isValid(std::vector<std::string> tokens){
	int v=0;
	if(asmF0Instruction::isValid(tokens)==1){
		v|=1;
	}
	if(asmF1Instruction::isValid(tokens)==1){
		v|=2;
	}
	if(asmF2Instruction::isValid(tokens)==1){
		v|=4;
	}
	if(asmF3Instruction::isValid(tokens)==1){
		v|=8;
	}
	return v;
}