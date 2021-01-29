#include "div.h"
#include "../../utils.h"

asmF1DivInstruction::asmF1DivInstruction(std::vector<std::string> tokens) : asmF1Instruction(tokens){

}

std::string asmF1DivInstruction::getMnemonicStatic(){
	return std::string("div");
}

std::string asmF1DivInstruction::getMnemonic(){
	return asmF1DivInstruction::getMnemonicStatic();
}

int asmF1DivInstruction::getOpCodeStatic(){
	return 9;
}

int asmF1DivInstruction::getOpCode(){
	return asmF1DivInstruction::getOpCodeStatic();
}

std::string asmF1DivInstruction::getUsage(){
	return std::string("r1 <-- (r1) / (r2)");
}

int asmF1DivInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF1DivInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF1DivInstruction::run(std::vector<int> registers){
	registers[this->getR1()] = registers[this->getR1()]/registers[this->getR2()];
	return registers;
}