#include "f0instruction.h"
#include "format0/halt.h"
#include "../utils.h"

#include <sstream>

asmF0Instruction::asmF0Instruction(std::vector<std::string> tokens){

}

int asmF0Instruction::getInstructionSet(){
	int is = (this->getOpCode() & 0xf) << 28;
	is |= asmF0Instruction::getType() & 0x3;
	return is;
}

int asmF0Instruction::getOpCode(){
	return asmF0Instruction::getOpCodeStatic();
}

int asmF0Instruction::getOpCodeStatic(){
	return -1;
}

int asmF0Instruction::getTypeStatic(){
	return 0;
}

int asmF0Instruction::getType(){
	return asmF0Instruction::getTypeStatic();
}

void asmF0Instruction::addUsage(uiTable* table){
	std::vector<std::string> row;
	row.push_back(asmF0HaltInstruction::getMnemonicStatic());
	row.push_back(toString(asmF0Instruction::getTypeStatic()));
	row.push_back(hexString(asmF0HaltInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF0HaltInstruction::getUsage());
	table->addRow(row);
}

asmInstruction* asmF0Instruction::getInstruction(std::vector<std::string> tokens){
	if(asmF0HaltInstruction::isValid(tokens)==1){
		return new asmF0HaltInstruction(tokens);
	}
	return NULL;
}

int asmF0Instruction::isValid(std::vector<std::string> tokens){
	if(tokens.size()!=1){
		return 0;
	}
	if(asmF0HaltInstruction::isValid(tokens)!=1){
		return 0;
	}
	return 1;
}