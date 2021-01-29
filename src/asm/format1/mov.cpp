#include "mov.h"
#include "../../utils.h"

asmF1MovInstruction::asmF1MovInstruction(std::vector<std::string> tokens) : asmF1Instruction(tokens){

}

std::string asmF1MovInstruction::getMnemonicStatic(){
	return std::string("mov");
}

std::string asmF1MovInstruction::getMnemonic(){
	return asmF1MovInstruction::getMnemonicStatic();
}

int asmF1MovInstruction::getOpCodeStatic(){
	return 11;
}

int asmF1MovInstruction::getOpCode(){
	return asmF1MovInstruction::getOpCodeStatic();
}

std::string asmF1MovInstruction::getUsage(){
	return std::string("r1 <-- (r2)");
}

int asmF1MovInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF1MovInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF1MovInstruction::run(std::vector<int> registers){
	registers[this->getR1()] = registers[this->getR2()];
	return registers;
}