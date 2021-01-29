#include "add.h"
#include "../../utils.h"

asmF1AddInstruction::asmF1AddInstruction(std::vector<std::string> tokens) : asmF1Instruction(tokens){

}

std::string asmF1AddInstruction::getMnemonicStatic(){
	return std::string("add");
}

std::string asmF1AddInstruction::getMnemonic(){
	return asmF1AddInstruction::getMnemonicStatic();
}

int asmF1AddInstruction::getOpCodeStatic(){
	return 13;
}

int asmF1AddInstruction::getOpCode(){
	return asmF1AddInstruction::getOpCodeStatic();
}

std::string asmF1AddInstruction::getUsage(){
	return std::string("r1 <-- (r1) + (r2)");
}

int asmF1AddInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF1AddInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF1AddInstruction::run(std::vector<int> registers){
	registers[this->getR1()] = registers[this->getR1()]+registers[this->getR2()];
	return registers;
}