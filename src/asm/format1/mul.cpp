#include "mul.h"
#include "../../utils.h"

asmF1MulInstruction::asmF1MulInstruction(std::vector<std::string> tokens) : asmF1Instruction(tokens){

}

std::string asmF1MulInstruction::getMnemonicStatic(){
	return std::string("mul");
}

std::string asmF1MulInstruction::getMnemonic(){
	return asmF1MulInstruction::getMnemonicStatic();
}

int asmF1MulInstruction::getOpCodeStatic(){
	return 2;
}

int asmF1MulInstruction::getOpCode(){
	return asmF1MulInstruction::getOpCodeStatic();
}

std::string asmF1MulInstruction::getUsage(){
	return std::string("r1 <-- (r1) * (r2)");
}

int asmF1MulInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF1MulInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF1MulInstruction::run(std::vector<int> registers){
	registers[this->getR1()] = registers[this->getR1()]*registers[this->getR2()];
	return registers;
}