#ifndef TABLE_HEADER
#define TABLE_HEADER

#define UITABLE_LEFT -1
#define UITABLE_CENTER 0
#define UITABLE_RIGHT 1

#include <string>
#include <vector>
#include "../logger.h"

class uiTable {
private:
	Logger logger;
	bool headerVisible;
	std::vector<int> colSize;
	std::vector<int> colAlignment;
	std::vector<std::string> tableHeader;
	std::vector<std::vector<std::string> > tableRow;
	void checkColumn(int index, std::string col);
	void printAlign(std::string str, int width, int alignment);
	int totalColumnLength();
	std::string toString(int num);
public:
	uiTable(Logger logger);
	void showHeader();
	void hideHeader();
	void addColumn(std::string col, int alignment);
	void addColumn(const char* col, int alignment);
	void setColumn(int index, std::string col, int alignment);
	void setColumn(int index, const char* col, int alignment);
	std::string getColumn(int index);
	void addRow(std::vector<std::string> row);
	void addRow(std::vector<const char*> row);
	void setRow(int index, std::vector<std::string> row);
	void setRow(int index, std::vector<const char*> row);
	void clear();
	void print();
};

#endif