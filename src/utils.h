#ifndef UTILS_HEADER
#define UTILS_HEADER

#include <string>
#include <vector>

std::string fillString(char ch, int length);
std::string hexString(int number, int bit);
std::string binString(int number, int bit);
std::string toLower(std::string str);
std::string toString(int number);
int toInteger(std::string str);
std::vector<std::string> split(std::vector<std::string> v, std::string delims);
std::vector<std::string> split(std::vector<std::string> v, char delim);
std::vector<std::string> split(std::string s, char delim);
std::string join(std::vector<std::string> v, std::vector<std::string>::iterator begin, std::vector<std::string>::iterator end, std::string delim);
std::string join(std::vector<std::string> v, std::string delim);
int countToken(std::vector<std::string> tokens, std::string delims);
int countToken(std::vector<std::string> tokens);
bool isWhitespace(std::string str, std::string wsChars);
bool isWhitespace(std::string str);
bool isNumber(std::string str);
bool isRegister(std::string str);
bool isImmediate(std::string str);

#endif