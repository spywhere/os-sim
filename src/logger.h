#ifndef LOGGER_HEADER
#define LOGGER_HEADER

#include <iostream>
#include <string>

class Logger {
private:
public:
	Logger();
	std::string filename;
	bool outIO;
	// void toFile(const char *fileName);
	void toIO(bool toIO);
	void pause();
};

template<class T>
inline Logger& operator<<(Logger& s, T val) {
	if(s.outIO){
		std::cout << val;
	}
	std::cout << std::flush;
	return s;
}

#endif