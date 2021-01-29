#include "f2instruction.h"
#include "format2/in.h"
#include "format2/mov.h"
#include "format2/out.h"
#include "../utils.h"

#include <sstream>

asmF2Instruction::asmF2Instruction(std::vector<std::string> tokens){
	this->ltr = isRegister(tokens[1]);
	if(this->ltr){
		this->r1 = toInteger(tokens[1].substr(1))+1;
		if(tokens[2][0]=='#'){
			this->imm = toInteger(tokens[2].substr(1));
		}else{
			this->imm = toInteger(tokens[2]);
		}
	}else{
		if(tokens[1][0]=='#'){
			this->imm = toInteger(tokens[1].substr(1));
		}else{
			this->imm = toInteger(tokens[1]);
		}
		this->r1 = toInteger(tokens[2].substr(1))+1;
	}
}

int asmF2Instruction::getInstructionSet(){
	int is = (this->getOpCode() & 0xf) << 28;
	is |= (this->r1 & 0xf) << 24;
	is |= (this->imm & 0x3fffff) << 2;
	is |= asmF2Instruction::getType() & 0x3;
	return is;
}

int asmF2Instruction::getOpCode(){
	return asmF2Instruction::getOpCodeStatic();
}

int asmF2Instruction::getOpCodeStatic(){
	return -1;
}

int asmF2Instruction::getTypeStatic(){
	return 2;
}

int asmF2Instruction::getType(){
	return asmF2Instruction::getTypeStatic();
}

int asmF2Instruction::getR1(){
	return this->r1;
}

int asmF2Instruction::getImmediate(){
	return this->imm;
}

bool asmF2Instruction::isLtoR(){
	return this->ltr;
}

void asmF2Instruction::addUsage(uiTable* table){
	std::vector<std::string> row;

	row.push_back(asmF2InInstruction::getMnemonicStatic()+" r1, imm");
	row.push_back(toString(asmF2Instruction::getTypeStatic()));
	row.push_back(hexString(asmF2InInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF2InInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF2MovInstruction::getMnemonicStatic()+" r1, imm");
	row.push_back(toString(asmF2Instruction::getTypeStatic()));
	row.push_back(hexString(asmF2MovInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF2MovInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF2OutInstruction::getMnemonicStatic()+" imm, r1");
	row.push_back(toString(asmF2Instruction::getTypeStatic()));
	row.push_back(hexString(asmF2OutInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF2OutInstruction::getUsage());
	table->addRow(row);
}

asmInstruction* asmF2Instruction::getInstruction(std::vector<std::string> tokens){
	if(asmF2InInstruction::isValid(tokens)==1){
		return new asmF2InInstruction(tokens);
	}else if(asmF2MovInstruction::isValid(tokens)==1){
		return new asmF2MovInstruction(tokens);
	}else if(asmF2OutInstruction::isValid(tokens)==1){
		return new asmF2OutInstruction(tokens);
	}
	return NULL;
}

int asmF2Instruction::isValid(std::vector<std::string> tokens){
	if(tokens.size()!=3 || (isRegister(tokens[1]) && isRegister(tokens[2])) || (!isRegister(tokens[1]) && !isRegister(tokens[2]))){
		return 0;
	}
	if(asmF2InInstruction::isValid(tokens)!=1 && asmF2MovInstruction::isValid(tokens)!=1 && asmF2OutInstruction::isValid(tokens)!=1){
		return 0;
	}
	return 1;
}