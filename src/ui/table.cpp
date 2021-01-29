#include "table.h"

#include <sstream>

uiTable::uiTable(Logger logger){
	this->logger = logger;
	this->showHeader();
}

void uiTable::showHeader(){
	this->headerVisible = true;
}

void uiTable::hideHeader(){
	this->headerVisible = false;
}

void uiTable::checkColumn(int index, std::string col){
	if(this->colSize.size() >= index){
		if(this->colSize[index] < col.length()){
			this->colSize[index] = col.length();
		}
	}
}

void uiTable::printAlign(std::string str, int width, int alignment){
	int w = width-str.length();
	int lp = w/2;
	int rp = w-lp;

	if(alignment==UITABLE_RIGHT){
		while(w-->0){
			this->logger << " ";
		}
	}
	if(alignment==UITABLE_CENTER){
		while(lp-->0){
			this->logger << " ";
		}
	}
	this->logger << str;
	if(alignment==UITABLE_CENTER){
		while(rp-->0){
			this->logger << " ";
		}
	}
	if(alignment==UITABLE_LEFT){
		while(w-->0){
			this->logger << " ";
		}
	}
}

int uiTable::totalColumnLength(){
	int sum=0;
	for(int i=0;i<this->colSize.size();i++){
		sum+=this->colSize[i];
	}
	return sum;
}

std::string uiTable::toString(int num){
	std::stringstream ss;
	ss << num;
	return ss.str();
}

void uiTable::addColumn(std::string col, int alignment){
	this->colSize.push_back(col.length());
	this->tableHeader.push_back(col);
	this->colAlignment.push_back(alignment);
}

void uiTable::addColumn(const char* col, int alignment){
	this->addColumn(std::string(col), alignment);
}

void uiTable::setColumn(int index, std::string col, int alignment){
	this->checkColumn(index, col);
	this->tableHeader[index] = col;
	this->colAlignment[index] = alignment;
}

void uiTable::setColumn(int index, const char* col, int alignment){
	this->setColumn(index, std::string(col), alignment);
}

std::string uiTable::getColumn(int index){
	if(index <= this->tableHeader.size()){
		return this->tableHeader[index];
	}
	return std::string();
}

void uiTable::addRow(std::vector<std::string> row){
	for(int i=0;i<row.size();i++){
		this->checkColumn(i, row[i]);
	}
	this->tableRow.push_back(row);
}

void uiTable::addRow(std::vector<const char*> row){
	std::vector<std::string> nrow;
	for(int i=0;i<row.size();i++){
		nrow.push_back(std::string(row[i]));
	}
	this->addRow(nrow);
}

void uiTable::setRow(int index, std::vector<std::string> row){
	this->tableRow[index] = row;
	for(int i=0;i<row.size();i++){
		this->checkColumn(i, row[i]);
	}
}

void uiTable::setRow(int index, std::vector<const char*> row){
	std::vector<std::string> nrow;
	for(int i=0;i<row.size();i++){
		nrow.push_back(std::string(row[i]));
	}
	this->setRow(index, nrow);
}

void uiTable::clear(){
	this->colSize.clear();
	this->colAlignment.clear();
	this->tableHeader.clear();
	this->tableRow.clear();
}

void uiTable::print(){
	if(this->headerVisible){
		for(int i=0;i<this->tableHeader.size();i++){
			this->logger << " ";
			this->printAlign(this->tableHeader[i], this->colSize[i], this->colAlignment[i]);
		}
		this->logger << " \n";
		for(int i=0;i<this->totalColumnLength()+(this->tableHeader.size()+1);i++){
			this->logger << "=";
		}
		this->logger << "\n";
	}
	for(int r=0;r<this->tableRow.size();r++){
		for(int i=0;i<this->tableRow[r].size();i++){
			this->logger << " ";
			this->printAlign(this->tableRow[r][i], this->colSize[i], this->colAlignment[i]);
		}
		this->logger << " \n";
	}
}