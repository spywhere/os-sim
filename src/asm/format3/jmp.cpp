#include "jmp.h"
#include "../../utils.h"

asmF3JmpInstruction::asmF3JmpInstruction(std::vector<std::string> tokens) : asmF3Instruction(tokens){

}

std::string asmF3JmpInstruction::getMnemonicStatic(){
	return std::string("jmp");
}

std::string asmF3JmpInstruction::getMnemonic(){
	return asmF3JmpInstruction::getMnemonicStatic();
}

int asmF3JmpInstruction::getOpCodeStatic(){
	return 4;
}

int asmF3JmpInstruction::getOpCode(){
	return asmF3JmpInstruction::getOpCodeStatic();
}

std::string asmF3JmpInstruction::getUsage(){
	return std::string("PC <-- addr");
}

int asmF3JmpInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF3JmpInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF3JmpInstruction::getTargetPC(int flag, int pc){
	return this->getAddress();
}