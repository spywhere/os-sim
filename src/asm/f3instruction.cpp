#include "f3instruction.h"
#include "format3/jeq.h"
#include "format3/jmp.h"
#include "format3/jne.h"
#include "format3/jneg.h"
#include "format3/jpl.h"
#include "../utils.h"

#include <sstream>

asmF3Instruction::asmF3Instruction(std::vector<std::string> tokens){
	this->address = toInteger(tokens[1]);
}

int asmF3Instruction::getInstructionSet(){
	int is = (this->getOpCode() & 0xf) << 28;
	is |= (this->address & 0x3ffffff) << 2;
	is |= asmF3Instruction::getType() & 0x3;
	return is;
}

int asmF3Instruction::getOpCode(){
	return asmF3Instruction::getOpCodeStatic();
}

int asmF3Instruction::getOpCodeStatic(){
	return -1;
}

int asmF3Instruction::getTypeStatic(){
	return 3;
}

int asmF3Instruction::getType(){
	return asmF3Instruction::getTypeStatic();
}

int asmF3Instruction::getAddress(){
	return this->address;
}

void asmF3Instruction::addUsage(uiTable* table){
	std::vector<std::string> row;

	row.push_back(asmF3JeqInstruction::getMnemonicStatic()+" addr");
	row.push_back(toString(asmF3Instruction::getTypeStatic()));
	row.push_back(hexString(asmF3JeqInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF3JeqInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF3JmpInstruction::getMnemonicStatic()+" addr");
	row.push_back(toString(asmF3Instruction::getTypeStatic()));
	row.push_back(hexString(asmF3JmpInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF3JmpInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF3JneInstruction::getMnemonicStatic()+" addr");
	row.push_back(toString(asmF3Instruction::getTypeStatic()));
	row.push_back(hexString(asmF3JneInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF3JneInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF3JnegInstruction::getMnemonicStatic()+" addr");
	row.push_back(toString(asmF3Instruction::getTypeStatic()));
	row.push_back(hexString(asmF3JnegInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF3JnegInstruction::getUsage());
	table->addRow(row);

	row.clear();
	row.push_back(asmF3JplInstruction::getMnemonicStatic()+" addr");
	row.push_back(toString(asmF3Instruction::getTypeStatic()));
	row.push_back(hexString(asmF3JplInstruction::getOpCodeStatic(), 1));
	row.push_back(asmF3JplInstruction::getUsage());
	table->addRow(row);
}

asmInstruction* asmF3Instruction::getInstruction(std::vector<std::string> tokens){
	if(asmF3JeqInstruction::isValid(tokens)==1){
		return new asmF3JeqInstruction(tokens);
	}else if(asmF3JmpInstruction::isValid(tokens)==1){
		return new asmF3JmpInstruction(tokens);
	}else if(asmF3JneInstruction::isValid(tokens)==1){
		return new asmF3JneInstruction(tokens);
	}else if(asmF3JnegInstruction::isValid(tokens)==1){
		return new asmF3JnegInstruction(tokens);
	}else if(asmF3JplInstruction::isValid(tokens)==1){
		return new asmF3JplInstruction(tokens);
	}
	return NULL;
}

int asmF3Instruction::isValid(std::vector<std::string> tokens){
	if(tokens.size()!=2 || !isNumber(tokens[1])){
		return 0;
	}
	if(asmF3JeqInstruction::isValid(tokens)!=1 && asmF3JmpInstruction::isValid(tokens)!=1 && asmF3JneInstruction::isValid(tokens)!=1 && asmF3JnegInstruction::isValid(tokens)!=1 && asmF3JplInstruction::isValid(tokens)!=1){
		return 0;
	}
	return 1;
}