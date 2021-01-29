#include "halt.h"
#include "../../utils.h"

asmF0HaltInstruction::asmF0HaltInstruction(std::vector<std::string> tokens) : asmF0Instruction(tokens){

}

std::string asmF0HaltInstruction::getMnemonicStatic(){
	return std::string("halt");
}

std::string asmF0HaltInstruction::getMnemonic(){
	return asmF0HaltInstruction::getMnemonicStatic();
}

int asmF0HaltInstruction::getOpCodeStatic(){
	return 6;
}

int asmF0HaltInstruction::getOpCode(){
	return asmF0HaltInstruction::getOpCodeStatic();
}

std::string asmF0HaltInstruction::getUsage(){
	return std::string("Terminate process");
}

int asmF0HaltInstruction::isValid(std::vector<std::string> tokens){
	if(toLower(tokens[0])!=asmF0HaltInstruction::getMnemonicStatic()){
		return 0;
	}
	return 1;
}