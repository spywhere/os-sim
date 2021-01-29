#include "os.h"

#include <fstream>
#include <sstream>
#include "asm/instruction.h"
#include "asm/f0instruction.h"
#include "asm/f1instruction.h"
#include "asm/f2instruction.h"
#include "asm/f3instruction.h"
#include "os/process.h"
#include "os/processReport.h"
#include "ui/table.h"
#include "utils.h"

osOS::osOS(Logger logger){
	this->logger = logger;
	this->reinit();
}

void osOS::showInfo(){
	this->showOSInfo = true;
}

void osOS::hideInfo(){
	this->showOSInfo = false;
}

void osOS::showStepInfo(){
	this->stepInfo = true;
}

void osOS::hideStepInfo(){
	this->stepInfo = false;
}

void osOS::enableTraceMode(){
	this->traceMode = true;
}

void osOS::disableTraceMode(){
	this->traceMode = false;
}

void osOS::useRoundRobin(int timeQuantum){
	this->timeQuantum = timeQuantum;
}

void osOS::useFCFS(){
	this->timeQuantum = 0;
}

void osOS::reinit(){
	this->workTime = 0;
	this->totalTime = 0;
	this->totalMemory = 8*1024;
	this->timeQuantum = 0;
	this->traceMode = false;
	this->showOSInfo = false;
	this->stepInfo = true;
	this->pcEnd = 0;
	this->currentTimeQuantum = 0;
	this->currentProcess = NULL;
	this->registers.clear();
	//Flag
	this->registers.push_back(0);
	//Registers
	for(int r=0;r<16;r++){
		this->registers.push_back(0);
	}
	while(!this->processes.empty()){
		this->processes.pop_front();
	}
	while(!this->processReport.empty()){
		this->processReport.pop_front();
	}
}

bool osOS::step(){
	//Pre-running
	if(this->currentProcess == NULL){
		if(this->timeQuantum>0){
			this->currentTimeQuantum = this->timeQuantum;
			//RR
			if(!this->processes.empty()){
				currentProcess = this->processes.front();
				this->processes.pop_front();
			}
		}else{
			//FCFS
			if(!this->processes.empty()){
				currentProcess = this->processes.front();
				this->processes.pop_front();
			}
		}
		if(this->currentProcess == NULL){
			if(this->showOSInfo){
				this->logger << "No process in memory\n";
			}
			return false;
		}else{
			if(this->traceMode){
				this->logger << "Next process is " << this->currentProcess->getName() << "#" << this->currentProcess->getID() << "\n";
			}
		}
	}
	asmInstruction* inst = this->currentProcess->fetchInstruction();

	if(this->stepInfo){
		uiTable* table = new uiTable(this->logger);
		table->hideHeader();
		table->addColumn("Instruction:", UITABLE_LEFT);
		table->addColumn("", UITABLE_RIGHT);
		table->addColumn("", UITABLE_CENTER);
		table->addColumn("", UITABLE_LEFT);
		table->addColumn("", UITABLE_LEFT);
		table->addColumn("", UITABLE_CENTER);
		table->addColumn("", UITABLE_CENTER);
		std::vector<std::string> row;
		row.push_back("");
		row.push_back(inst->getMnemonic());
		row.push_back("");
		if(inst->getType()==0){
			asmF0Instruction* f0inst = (asmF0Instruction*)inst;
			row.push_back("");
			row.push_back("");
		}else if(inst->getType()==1){
			asmF1Instruction* f1inst = (asmF1Instruction*)inst;
			row.push_back("r"+ toString(f1inst->getR1()-1) + ",");
			row.push_back("r"+ toString(f1inst->getR2()-1));
		}else if(inst->getType()==2){
			asmF2Instruction* f2inst = (asmF2Instruction*)inst;
			if(f2inst->isLtoR()){
				row.push_back("r"+ toString(f2inst->getR1()-1) + ",");
				row.push_back("#" + toString(f2inst->getImmediate()));
			}else{
				row.push_back("#" + toString(f2inst->getImmediate()) + ",");
				row.push_back("r"+ toString(f2inst->getR1()-1));
			}
		}else if(inst->getType()==3){
			asmF3Instruction* f3inst = (asmF3Instruction*)inst;
			row.push_back(toString(f3inst->getAddress()));
			row.push_back("");
		}
		row.push_back("=>");
		row.push_back(binString(inst->getInstructionSet()>>24, 8) + " " + binString(inst->getInstructionSet()>>16, 8) + " " + binString(inst->getInstructionSet()>>8, 8) + " " + binString(inst->getInstructionSet(), 8)+ "b");
		table->addRow(row);
		table->print();
	}

	//Running
	this->totalTime++;
	if(this->currentProcess->isUsingIO()){
		this->currentProcess->wait();
		if(this->stepInfo){
			this->logger << "Process " << this->currentProcess->getName() << "#" << this->currentProcess->getID() << " is waiting for IO\n";
		}
	}else{
		this->workTime++;
		this->registers = this->currentProcess->run(this->logger, this->registers);
		if(this->stepInfo){
			this->showRegisters();
			if(this->currentProcess->isTerminated()){
				this->logger << "NextPC: Terminated\n";
			}else{
				this->logger << "NextPC: " << toString(this->currentProcess->getPC()) << "\n";
			}
		}
	}
	for (std::list<osProcess*>::iterator i = this->processes.begin(); i != this->processes.end(); ++i){
		(*i)->wait();
	}

	//Post-running
	if(this->currentProcess->isTerminated()){
		if(this->stepInfo){
			this->logger << "Process " << this->currentProcess->getName() << "#" << this->currentProcess->getID() << " is terminated\n";
		}
		this->processReport.push_back(new osProcessReport(this->currentProcess));
		this->currentProcess = NULL;
		if(this->processes.empty()){
			this->printSummary();
		}
	}
	if(this->timeQuantum>0 && this->currentProcess && --this->currentTimeQuantum<=0){
		this->processes.push_back(currentProcess);
		this->currentProcess = NULL;
	}
	return true;
}

int osOS::newProcessID(){
	int id = 0;
	for (std::list<osProcess*>::iterator i = this->processes.begin(); i != this->processes.end(); ++i){
		if(id<=(*i)->getID()){
			id=(*i)->getID()+1;
		}
	}
	return id;
}

int osOS::load(std::string filename){
	int retcode = 0;
	std::vector<asmInstruction*> instructionList;

	std::string line;
	std::ifstream assembly(filename.c_str());
	if(assembly.is_open()){
		int ln=0;
		bool isEmpty = true;
		bool isHalt = false;
		bool foundF3 = false;
		int deadCode = 0;
		int progSize = 0;
		while(std::getline(assembly, line)){
			ln++;
			if(line.length()<1 || line[0]=='\r' || line[0]=='\n' || line[0]==';'){
				continue;
			}
			std::vector<std::string> tokens = split(line, ' ');
			tokens = split(tokens, std::string("\n\r\t,"));
			int p=0;
			if(isEmpty && tokens.size() > 0){
				isEmpty = false;
			}
			if(isHalt && !foundF3 && tokens.size() > 0 && deadCode < 1){
				deadCode = ln;
			}
			if(tokens.size() > 0 && toLower(tokens[0]) == "halt"){
				isHalt = true;
			}

			int valid=asmInstruction::isValid(tokens);
			if(valid==0){
				this->logger << "Line " << ln << ": " << line << "\n";
				this->logger << "   Instruction is invalid\n";
				retcode = 2;
			}else if(valid!=1&&valid!=2&&valid!=4&&valid!=8){
				this->logger << "Line " << ln << ": " << line << "\n";
				this->logger << "   Instruction is ambiguous between type ";
				bool first=true;
				for(int i=0;i<=3;i++){
					if(((valid >> i) & 1) == 1){
						if(!first){
							this->logger << ", ";
						}
						this->logger << i;
						first=false;
					}
				}
				retcode = 3;
			}else{
				asmInstruction* inst = asmInstruction::getInstruction(tokens);
				if(inst){
					if(isHalt && inst->getType()==3){
						foundF3 = true;
					}
					progSize++;
					instructionList.push_back(inst);
				}else{
					this->logger << "Line " << ln << ": " << line << "\n";
					this->logger << "   Instruction cannot be parsed\n";
					retcode = 2;
				}
			}
		}
		if(retcode==0){
			osProcess* process = new osProcess(this->newProcessID(), filename, instructionList, this->pcEnd);
			process->printStatus(this->logger);

			if(!isHalt || isEmpty){
				this->logger << "Warning! Code is not properly terminated (";
				if(!isHalt){
					this->logger << "\"halt\" not found";
				}else{
					this->logger << "file is empty";
				}
				this->logger << ")\n";
			}
			if(!foundF3 && deadCode > 0){
				this->logger << "Info! Dead code since line: " << deadCode << "\n";
			}

			uiTable* table = new uiTable(logger);
			std::vector<std::string> row;
			table->addColumn("", UITABLE_RIGHT);
			table->addColumn("", UITABLE_LEFT);
			table->hideHeader();

			row.push_back("ProcessID:");
			row.push_back(toString(process->getID()));
			table->addRow(row);

			row.clear();
			row.push_back("PC:");
			row.push_back(toString(this->pcEnd));
			table->addRow(row);

			row.clear();
			row.push_back("Start Address:");
			row.push_back(toString(this->getUsedMemory()));
			table->addRow(row);

			row.clear();
			row.push_back("Size:");
			row.push_back(toString(process->getSize()));
			table->addRow(row);


			if(this->getUsedMemory()+process->getSize() > this->totalMemory){
				this->logger << "Error: Memory exceed limits (Size: " << process->getSize() << ")\n";
				return 3;
			}else{
				table->print();
				if(this->processes.empty()){
					this->workTime = 0;
					this->totalTime = 0;
				}
				this->processes.push_back(process);
				this->pcEnd += progSize;
				retcode = (process->getID() << 2) | 0;
			}
		}
		assembly.close();
	}else{
		return 1;
	}
	return retcode;
}

osProcess* osOS::getCurrentProcess(){
	return this->currentProcess;
}

osProcess* osOS::getProcess(int procno){
	for (std::list<osProcess*>::iterator i = this->processes.begin(); i != this->processes.end(); ++i)
	{
		if((*i)->getID()==procno){
			return *i;
		}
	}
	return NULL;
}

int osOS::getUsedMemory(){
	int usedMemory = 0;
	for (std::list<osProcess*>::iterator i = this->processes.begin(); i != this->processes.end(); ++i)
	{
		usedMemory += (*i)->getSize();
	}
	if(this->currentProcess){
		usedMemory += this->currentProcess->getSize();
	}
	return usedMemory;
}

void osOS::printSummary(){
	uiTable* table = new uiTable(this->logger);
	std::vector<std::string> row;
	table->hideHeader();
	table->addColumn("", UITABLE_RIGHT);
	table->addColumn("", UITABLE_LEFT);
	table->addColumn("", UITABLE_LEFT);
	int ioTime=0, avg=0, totalProcess=0;
	while(!this->processReport.empty()){
		totalProcess++;
		osProcessReport* report = this->processReport.front();
		this->processReport.pop_front();
		avg+=report->getWaitTime();
		ioTime+=report->getIOTime();
		row.clear();
		row.push_back("PID#"+toString(report->getID())+" Waiting Time:");
		row.push_back(toString(report->getWaitTime()));
		table->addRow(row);
	}
	row.clear();
	row.push_back("Average Waiting Time:");
	row.push_back(toString(avg/totalProcess));
	table->addRow(row);
	row.clear();
	row.push_back("Total IO Time:");
	row.push_back(toString(ioTime));
	table->addRow(row);
	row.clear();
	row.push_back("CPU Run/Idle Time:");
	row.push_back(toString(this->workTime)+"/"+toString(this->totalTime-this->workTime));
	table->addRow(row);
	row.clear();
	row.push_back("CPU Utilization:");
	row.push_back(toString(this->workTime*100/this->totalTime)+"%");
	table->addRow(row);

	this->logger << "==== Summary ====\n";
	table->print();
}

void osOS::showRegisters(){
	uiTable* table = new uiTable(this->logger);
	std::vector<std::string> row;
	table->hideHeader();
	table->addColumn("", UITABLE_RIGHT);
	table->addColumn("", UITABLE_LEFT);
	table->addColumn("", UITABLE_RIGHT);
	table->addColumn("", UITABLE_LEFT);
	table->addColumn("", UITABLE_RIGHT);
	table->addColumn("", UITABLE_LEFT);
	table->addColumn("", UITABLE_RIGHT);
	table->addColumn("", UITABLE_LEFT);

	row.clear();
	for(int i=1;i<this->registers.size();i++){
		row.push_back("r"+toString(i-1)+":");
		row.push_back(hexString(this->registers[i], 8)+"h");
		if(row.size()%8==0){
			table->addRow(row);
			row.clear();
		}
	}
	if(row.size()<8){
		while(row.size()<8){
			row.push_back("");
		}
		table->addRow(row);
	}
	table->print();

	this->logger << "Flags: ";
	this->logger << binString(this->registers[0]>>24, 8) << " ";
	this->logger << binString(this->registers[0]>>16, 8) << " ";
	this->logger << binString(this->registers[0]>>8, 8) << " ";
	this->logger << binString(this->registers[0], 8) << "b\n";
}

void osOS::showStatus(){
	uiTable* table = new uiTable(this->logger);
	std::vector<std::string> row;
	table->hideHeader();
	table->addColumn("", UITABLE_RIGHT);
	table->addColumn("", UITABLE_LEFT);

	row.push_back("Process in memory:");
	row.push_back(toString(this->processes.size()+((this->currentProcess)?1:0)) + " process(es)");
	table->addRow(row);

	row.clear();
	row.push_back("");
	row.push_back("");
	table->addRow(row);

	row.clear();
	row.push_back("Active memory:");
	row.push_back(toString(osOS::getUsedMemory()) + " byte(s)");
	table->addRow(row);

	row.clear();
	row.push_back("Free memory:");
	row.push_back(toString(this->totalMemory - osOS::getUsedMemory()) + " byte(s)");
	table->addRow(row);

	row.clear();
	row.push_back("Total memory:");
	row.push_back(toString(this->totalMemory) + " byte(s)");
	table->addRow(row);

	row.clear();
	row.push_back("");
	row.push_back("");
	table->addRow(row);

	int ioProcess = 0;
	for (std::list<osProcess*>::iterator i = this->processes.begin(); i != this->processes.end(); ++i)
	{
		if((*i)->isUsingIO()){
			ioProcess++;
		}
	}
	if(this->currentProcess && this->currentProcess->isUsingIO()){
		ioProcess++;
	}
	row.clear();
	row.push_back("Process waiting for I/O:");
	row.push_back(toString(ioProcess) + " process(es)");
	table->addRow(row);

	row.clear();
	row.push_back("Scheduling Mode:");
	if(this->timeQuantum > 0){
		row.push_back("Round-Robin with time quantum = " + toString(this->timeQuantum));
	}else{
		row.push_back("First-Come-First-Serve");
	}
	table->addRow(row);

	row.clear();
	row.push_back("Trace Mode:");
	if(this->traceMode){
		row.push_back("Enabled");
	}else{
		row.push_back("Disabled");
	}
	table->addRow(row);
	row.clear();
	row.push_back("Process Step Info:");
	if(this->stepInfo){
		row.push_back("Visible");
	}else{
		row.push_back("Hidden");
	}
	table->addRow(row);

	row.clear();
	row.push_back("");
	row.push_back("");
	table->addRow(row);

	row.clear();
	row.push_back("Current Process:");
	if(this->currentProcess){
		row.push_back(this->currentProcess->getName() + "#" + toString(this->currentProcess->getID()));
	}else{
		row.push_back("No process running");
	}
	table->addRow(row);

	table->print();

	this->logger << "\n";

	this->showRegisters();
}