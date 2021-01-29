#include "logger.h"

Logger::Logger(){
	this->outIO = true;
}

void Logger::toIO(bool toIO){
	this->outIO = toIO;
}

void Logger::pause(){
	std::string str;
	std::getline(std::cin, str);
}