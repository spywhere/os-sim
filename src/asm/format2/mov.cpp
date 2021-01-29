#include "mov.h"
#include "../../utils.h"

asmF2MovInstruction::asmF2MovInstruction(std::vector<std::string> tokens) : asmF2Instruction(tokens){

}

std::string asmF2MovInstruction::getMnemonicStatic(){
	return std::string("mov");
}

std::string asmF2MovInstruction::getMnemonic(){
	return asmF2MovInstruction::getMnemonicStatic();
}

int asmF2MovInstruction::getOpCodeStatic(){
	return 14;
}

int asmF2MovInstruction::getOpCode(){
	return asmF2MovInstruction::getOpCodeStatic();
}

std::string asmF2MovInstruction::getUsage(){
	return std::string("r1 <-- imm");
}

int asmF2MovInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF2MovInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

std::vector<int> asmF2MovInstruction::run(std::vector<int> registers){
	registers[this->getR1()] = this->getImmediate();
	return registers;
}