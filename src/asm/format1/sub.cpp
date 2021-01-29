#include "sub.h"
#include "../../utils.h"

asmF1SubInstruction::asmF1SubInstruction(std::vector<std::string> tokens) : asmF1Instruction(tokens){

}

std::string asmF1SubInstruction::getMnemonicStatic(){
	return std::string("sub");
}

std::string asmF1SubInstruction::getMnemonic(){
	return asmF1SubInstruction::getMnemonicStatic();
}

int asmF1SubInstruction::getOpCodeStatic(){
	return 15;
}

int asmF1SubInstruction::getOpCode(){
	return asmF1SubInstruction::getOpCodeStatic();
}

std::string asmF1SubInstruction::getUsage(){
	return std::string("r1 <-- (r1) - (r2)");
}

int asmF1SubInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF1SubInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF1SubInstruction::run(std::vector<int> registers){
	registers[this->getR1()] = registers[this->getR1()]-registers[this->getR2()];
	return registers;
}