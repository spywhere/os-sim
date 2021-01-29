#include "jpl.h"
#include "../../utils.h"

asmF3JplInstruction::asmF3JplInstruction(std::vector<std::string> tokens) : asmF3Instruction(tokens){

}

std::string asmF3JplInstruction::getMnemonicStatic(){
	return std::string("jpl");
}

std::string asmF3JplInstruction::getMnemonic(){
	return asmF3JplInstruction::getMnemonicStatic();
}

int asmF3JplInstruction::getOpCodeStatic(){
	return 5;
}

int asmF3JplInstruction::getOpCode(){
	return asmF3JplInstruction::getOpCodeStatic();
}

std::string asmF3JplInstruction::getUsage(){
	return std::string("PC <-- addr; if signed flags = 0");
}

int asmF3JplInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF3JplInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF3JplInstruction::getTargetPC(int flag, int pc){
	if((flag>>31&1)==0){
		return this->getAddress();
	}
	return ++pc;
}