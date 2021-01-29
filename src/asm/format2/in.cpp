#include "in.h"
#include "../../utils.h"

asmF2InInstruction::asmF2InInstruction(std::vector<std::string> tokens) : asmF2Instruction(tokens){

}

std::string asmF2InInstruction::getMnemonicStatic(){
	return std::string("in");
}

std::string asmF2InInstruction::getMnemonic(){
	return asmF2InInstruction::getMnemonicStatic();
}

int asmF2InInstruction::getOpCodeStatic(){
	return 3;
}

int asmF2InInstruction::getOpCode(){
	return asmF2InInstruction::getOpCodeStatic();
}

std::string asmF2InInstruction::getUsage(){
	return std::string("r1 <-- PORT[imm]");
}

int asmF2InInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF2InInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}

int asmF2InInstruction::getIOTime(int ioTime){
	return 10;
}