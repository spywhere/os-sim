#include "out.h"
#include "../../utils.h"

asmF2OutInstruction::asmF2OutInstruction(std::vector<std::string> tokens) : asmF2Instruction(tokens){

}

std::string asmF2OutInstruction::getMnemonicStatic(){
	return std::string("out");
}

std::string asmF2OutInstruction::getMnemonic(){
	return asmF2OutInstruction::getMnemonicStatic();
}

int asmF2OutInstruction::getOpCodeStatic(){
	return 7;
}

int asmF2OutInstruction::getOpCode(){
	return asmF2OutInstruction::getOpCodeStatic();
}

std::string asmF2OutInstruction::getUsage(){
	return std::string("PORT[imm] <-- (r1)");
}

int asmF2OutInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF2OutInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF2OutInstruction::getIOTime(int ioTime){
	return 10;
}