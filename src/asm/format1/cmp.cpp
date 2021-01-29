#include "cmp.h"
#include "../../utils.h"

asmF1CmpInstruction::asmF1CmpInstruction(std::vector<std::string> tokens) : asmF1Instruction(tokens){

}

std::string asmF1CmpInstruction::getMnemonicStatic(){
	return std::string("cmp");
}

std::string asmF1CmpInstruction::getMnemonic(){
	return asmF1CmpInstruction::getMnemonicStatic();
}

int asmF1CmpInstruction::getOpCodeStatic(){
	return 8;
}

int asmF1CmpInstruction::getOpCode(){
	return asmF1CmpInstruction::getOpCodeStatic();
}

std::string asmF1CmpInstruction::getUsage(){
	return std::string("(r1) : (r2)");
}

int asmF1CmpInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF1CmpInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF1CmpInstruction::run(std::vector<int> registers){
	registers[0]&=(~(1<<1));
	registers[0]&=(~(1<<31));
	if(registers[this->getR1()]==registers[this->getR2()]){
		registers[0]|=(1<<1);
	}
	if(registers[this->getR1()]<registers[this->getR2()]){
		registers[0]|=(1<<31);
	}
	return registers;
}