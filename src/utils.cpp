#include "utils.h"

#include <sstream>

std::string fillString(char ch, int length){
	std::stringstream s;
	for(int i=0;i<length;i++){
		s << ch;
	}
	return s.str();
}

std::string hexString(int number, int bit){
	static const char* hexc = "0123456789ABCDEF";
	std::stringstream s;
	for(int i=bit-1;i>=0;i--){
		s << hexc[(number >> i*4) & 0xf];
	}
	return s.str();
}

std::string binString(int number, int bit){
	std::stringstream s;
	for(int i=bit-1;i>=0;i--){
		s << ((number >> i) & 1);
	}
	return s.str();
}

std::string toLower(std::string str){
	for(int i=0;i<str.length();i++){
		str[i] = tolower(str[i]);
	}
	return str;
}

std::string toString(int number){
	std::stringstream s;
	s << number;
	return s.str();
}

int toInteger(std::string str){
	std::istringstream istr(str);
	int i;
	istr >> i;
	return i;
}

std::vector<std::string> split(std::vector<std::string> v, std::string delims){
	for(int i=0;i<delims.length();i++){
		v = split(v, delims[i]);
	}
	return v;
}

std::vector<std::string> split(std::vector<std::string> v, char delim){
	std::vector<std::string> ov;
	for(std::vector<std::string>::iterator i = v.begin(); i != v.end(); ++i){
		std::vector<std::string> spv = split(*i, delim);
		for(std::vector<std::string>::iterator j = spv.begin(); j != spv.end(); ++j){
			ov.push_back(*j);
		}
	}
	return ov;
}

std::vector<std::string> split(std::string s, char delim){
	std::vector<std::string> elems;
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim)) {
		elems.push_back(item);
	}
	return elems;
}

std::string join(std::vector<std::string> v, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, std::string delim){
	std::string str;
	for (std::vector<std::string>::iterator i = begin; i != end; ++i){
		if(!str.empty()){
			str+=delim;
		}
		str+=*i;
	}
	return str;
}

std::string join(std::vector<std::string> v, std::string delim){
	return join(v, v.begin(), v.end(), delim);
}

int countToken(std::vector<std::string> tokens, std::string delims){
	int c = 0;
	for(std::vector<std::string>::iterator i = tokens.begin(); i != tokens.end(); ++i){
		if((*i).length() > 0 && !isWhitespace(*i, delims)){
			c++;
		}
	}
	return c;
}

int countToken(std::vector<std::string> tokens){
	return countToken(tokens, std::string("\n\r\t "));
}

bool isWhitespace(std::string str, std::string wsChars){
	for(int i=0;i<str.length();i++){
		bool isWhite = false;
		for(int d=0;d<wsChars.length();d++){
			if(str[i]==wsChars[d]){
				isWhite = true;
			}
		}
		if(!isWhite){
			return false;
		}
	}
	return true;
}

bool isNumber(std::string str){
	for(int i=0;i<str.length();i++){
		if(!std::isdigit(str[i])){
			return false;
		}
	}
	return true;
}

bool isWhitespace(std::string str){
	return isWhitespace(str, std::string("\n\r\t "));
}

bool isRegister(std::string str){
	str = toLower(str);
	if(str.length()<2 || str[0]!='r' || !isNumber(str.substr(1))){
		return false;
	}
	return true;
}

bool isImmediate(std::string str){
	if(str.length()<2){
		return false;
	}
	if(str[0]=='#'){
		return isNumber(str.substr(1));
	}else{
		return isNumber(str);
	}
}