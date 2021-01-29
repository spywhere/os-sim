#include "jneg.h"
#include "../../utils.h"

asmF3JnegInstruction::asmF3JnegInstruction(std::vector<std::string> tokens) : asmF3Instruction(tokens){

}

std::string asmF3JnegInstruction::getMnemonicStatic(){
	return std::string("jneg");
}

std::string asmF3JnegInstruction::getMnemonic(){
	return asmF3JnegInstruction::getMnemonicStatic();
}

int asmF3JnegInstruction::getOpCodeStatic(){
	return 10;
}

int asmF3JnegInstruction::getOpCode(){
	return asmF3JnegInstruction::getOpCodeStatic();
}

std::string asmF3JnegInstruction::getUsage(){
	return std::string("PC <-- addr; if signed flags = 1");
}

int asmF3JnegInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF3JnegInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF3JnegInstruction::getTargetPC(int flag, int pc){
	if((flag>>31&1)==1){
		return this->getAddress();
	}
	return ++pc;
}