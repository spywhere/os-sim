#include "jne.h"
#include "../../utils.h"

asmF3JneInstruction::asmF3JneInstruction(std::vector<std::string> tokens) : asmF3Instruction(tokens){

}

std::string asmF3JneInstruction::getMnemonicStatic(){
	return std::string("jne");
}

std::string asmF3JneInstruction::getMnemonic(){
	return asmF3JneInstruction::getMnemonicStatic();
}

int asmF3JneInstruction::getOpCodeStatic(){
	return 1;
}

int asmF3JneInstruction::getOpCode(){
	return asmF3JneInstruction::getOpCodeStatic();
}

std::string asmF3JneInstruction::getUsage(){
	return std::string("PC <-- addr; if zero flags = 0");
}

int asmF3JneInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF3JneInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF3JneInstruction::getTargetPC(int flag, int pc){
	if((flag>>1&1)==0){
		return this->getAddress();
	}
	return ++pc;
}