#include "jeq.h"
#include "../../utils.h"

asmF3JeqInstruction::asmF3JeqInstruction(std::vector<std::string> tokens) : asmF3Instruction(tokens){

}

std::string asmF3JeqInstruction::getMnemonicStatic(){
	return std::string("jeq");
}

std::string asmF3JeqInstruction::getMnemonic(){
	return asmF3JeqInstruction::getMnemonicStatic();
}

int asmF3JeqInstruction::getOpCodeStatic(){
	return 12;
}

int asmF3JeqInstruction::getOpCode(){
	return asmF3JeqInstruction::getOpCodeStatic();
}

std::string asmF3JeqInstruction::getUsage(){
	return std::string("PC <-- addr; if zero flags = 1");
}

int asmF3JeqInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF3JeqInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF3JeqInstruction::getTargetPC(int flag, int pc){
	if((flag>>1&1)==1){
		return this->getAddress();
	}
	return ++pc;
}