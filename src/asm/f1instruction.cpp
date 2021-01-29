#include "f1instruction.h"
#include "format1/add.h"
#include "format1/cmp.h"
#include "format1/div.h"
#include "format1/mov.h"
#include "format1/mul.h"
#include "format1/sub.h"
#include "../utils.h"

#include <sstream>

asmF1Instruction::asmF1Instruction(std::vector<std::string> tokens){
	this->r1 = toInteger(tokens[1].substr(1))+1;
	this->r2 = toInteger(tokens[2].substr(1))+1;
}

int asmF1Instruction::getInstructionSet(){
	int is = (this->getOpCode() & 0xf) << 28;
	is |= (this->r1 & 0xf) << 24;
	is |= (this->r2 & 0xf) << 20;
	is |= asmF1Instruction::getType() & 0x3;
	return is;
}

int asmF1Instruction::getOpCode(){
	return asmF1Instruction::getOpCodeStatic();
}

int asmF1Instruction::getOpCodeStatic(){
	return -1;
}

int asmF1Instruction::getTypeStatic(){
	return 1;
}

int asmF1Instruction::getType(){
	return asmF1Instruction::getTypeStatic();
}

int asmF1Instruction::getR1(){
	return this->r1;
}

int asmF1Instruction::getR2(){
	return this->r2;
}

void asmF1Instruction::addUsage(uiTable* table){
	std::vector<std::string> row;

	row.push_back(asmF1AddInstruction::getMnemonicStatic()+" r1, r2");
	row.push_back(toString(asmF1Instruction::getTypeStatic()));
	row.push_back(hexString(asmF1AddInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF1AddInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF1CmpInstruction::getMnemonicStatic()+" r1, r2");
	row.push_back(toString(asmF1Instruction::getTypeStatic()));
	row.push_back(hexString(asmF1CmpInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF1CmpInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF1DivInstruction::getMnemonicStatic()+" r1, r2");
	row.push_back(toString(asmF1Instruction::getTypeStatic()));
	row.push_back(hexString(asmF1DivInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF1DivInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF1MovInstruction::getMnemonicStatic()+" r1, r2");
	row.push_back(toString(asmF1Instruction::getTypeStatic()));
	row.push_back(hexString(asmF1MovInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF1MovInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF1MulInstruction::getMnemonicStatic()+" r1, r2");
	row.push_back(toString(asmF1Instruction::getTypeStatic()));
	row.push_back(hexString(asmF1MulInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF1MulInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF1SubInstruction::getMnemonicStatic()+" r1, r2");
	row.push_back(toString(asmF1Instruction::getTypeStatic()));
	row.push_back(hexString(asmF1SubInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF1SubInstruction::getUsage());
	table->addRow(row);
}

asmInstruction* asmF1Instruction::getInstruction(std::vector<std::string> tokens){
	if(asmF1AddInstruction::isValid(tokens)==1){
		return new asmF1AddInstruction(tokens);
	}else if(asmF1CmpInstruction::isValid(tokens)==1){
		return new asmF1CmpInstruction(tokens);
	}else if(asmF1DivInstruction::isValid(tokens)==1){
		return new asmF1DivInstruction(tokens);
	}else if(asmF1MovInstruction::isValid(tokens)==1){
		return new asmF1MovInstruction(tokens);
	}else if(asmF1MulInstruction::isValid(tokens)==1){
		return new asmF1MulInstruction(tokens);
	}else if(asmF1SubInstruction::isValid(tokens)==1){
		return new asmF1SubInstruction(tokens);
	}
	return NULL;
}

int asmF1Instruction::isValid(std::vector<std::string> tokens){
	if(tokens.size()!=3 || !isRegister(tokens[1]) || !isRegister(tokens[2])){
		return 0;
	}
	if(asmF1AddInstruction::isValid(tokens)!=1 && asmF1CmpInstruction::isValid(tokens)!=1 && asmF1DivInstruction::isValid(tokens)!=1 && asmF1MovInstruction::isValid(tokens)!=1 && asmF1MulInstruction::isValid(tokens)!=1 && asmF1SubInstruction::isValid(tokens)!=1){
		return 0;
	}
	return 1;
}