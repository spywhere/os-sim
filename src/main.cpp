#include <cstdlib>
#include <string>
#include <vector>
#include "asm/f0instruction.h"
#include "asm/f1instruction.h"
#include "asm/f2instruction.h"
#include "asm/f3instruction.h"
#include "ui/table.h"
#include "os.h"
#include "logger.h"
#include "utils.h"

void printAssemblyHelp(Logger logger);
void printHelp(Logger logger);

int main(){
	Logger logger;
	osOS* os = new osOS(logger);
	logger << "OS Simulator v0.1\n";
	logger << "Copyright (c) 2006-2014 The Well Software. All rights reserved.\n";
	logger << "========\n";
	std::string cmd;
	std::vector<std::string> args;
	while(true){
		logger << ":";
		std::getline(std::cin, cmd);
		args = split(cmd, ' ');
		if(toLower(args[0])=="run"){
			os->hideInfo();
			while(os->step());
		}else if(toLower(args[0])=="step" || toLower(args[0])=="t"){
			int step = 1;
			if(args.size() > 1){
				if(isNumber(args[1])){
					if(toInteger(args[1]) > 1){
						step = toInteger(args[1]);
					}else{
						logger << "Time step must be at least 2";
						continue;
					}
				}else{
					logger << "Time step must be a number";
					continue;
				}
			}
			os->showInfo();
			while(step-->0){
				os->step();
			}
		}else if(toLower(args[0])=="load"){
			if(args.size() < 2){
				logger << "Usage: load <filename>\n";
				continue;
			}
			int code = os->load(args[1]);
			if(code == 1){
				logger << "Error: Unable to open file \"" << args[1] << "\"\n";
			}else if((code & 3) == 0){
				logger << "Process \"" << args[1] <<"\" is loaded\n";
			}
		}else if(toLower(args[0])=="kill" || toLower(args[0])=="terminate"){
			if(args.size() > 1 && !isNumber(args[1])){
				logger << "Process must be a number";
				continue;
			}
			osProcess* process = os->getCurrentProcess();
			if(args.size() >= 2){
				process = os->getProcess(toInteger(args[1]));
			}
			if(process && process->kill()){
				logger << "Process " << process->getName() << "#" << process->getID() << " will be terminated\n";
			}else{
				logger << "No process found\n";
			}
		}else if(toLower(args[0])=="fcfs"){
			os->useFCFS();
			logger << "Scheduling Mode -> First-Come-First-Serve\n";
		}else if(toLower(args[0])=="roundrobin" || toLower(args[0])=="rr"){
			if(args.size() < 2){
				logger << "Usage: " << args[0] << " <time quantum>\n";
				continue;
			}
			if(isNumber(args[1])){
				if(toInteger(args[1])<1){
					logger << "Time quantum must be at least 1\n";
				}else{
					os->useRoundRobin(toInteger(args[1]));
					logger << "Scheduling Mode -> Round Robin\n";
				}
			}else{
				logger << "Time quantum must be a number";
			}
		}else if(toLower(args[0])=="init" || toLower(args[0])=="restart"){
			os->reinit();
			logger << "System reinitialized\n";
		}else if(toLower(args[0])=="status"){
			os->showStatus();
		}else if(toLower(args[0])=="trace"){
			if(args.size() < 2 || !(toLower(args[1])=="on" || toLower(args[1])=="off")){
				logger << "Usage: trace <on/off>\n";
				continue;
			}
			if(toLower(args[1])=="on"){
				os->enableTraceMode();
				logger << "Trace Mode -> Enabled\n";
			}else{
				os->disableTraceMode();
				logger << "Trace Mode -> Disabled\n";
			}
		}else if(toLower(args[0])=="stepinfo"){
			if(args.size() < 2 || !(toLower(args[1])=="on" || toLower(args[1])=="off")){
				logger << "Usage: stepinfo <on/off>\n";
				continue;
			}
			if(toLower(args[1])=="on"){
				os->showStepInfo();
				logger << "Step Info -> Visible\n";
			}else{
				os->hideStepInfo();
				logger << "Step Info -> Hidden\n";
			}
		}else if(toLower(args[0])=="system" || toLower(args[0])=="sys"){
			if(args.size() < 2){
				logger << "Usage: " << args[0] <<" <cmd> [cmd]...\n";
				continue;
			}
			std::system(join(args, args.begin()+1, args.end(), std::string(" ")).c_str());
		}else if(toLower(args[0])=="quit" || toLower(args[0])=="exit"){
			break;
		}else if(toLower(args[0])=="assembly" || toLower(args[0])=="asm"){
			printAssemblyHelp(logger);
		}else if(toLower(args[0])=="help" || toLower(args[0])=="?"){
			printHelp(logger);
		}else{
			logger << "Unknown command. Try \"help\" for more info.\n";
		}
	}
	return 0;
}

void printHelp(Logger logger){
	logger << "   run\n";
	logger << "      Continue running until all process terminated\n";
	logger << "   step/t [n]\n";
	logger << "      Continue running by n time step (default is 1)\n";
	logger << "   load <filename>\n";
	logger << "      Load assembly file for running\n";
	logger << "   kill/terminate [process no.]\n";
	logger << "      Mark current/selected process to be terminated on their cycle\n";
	logger << "   fcfs\n";
	logger << "      Switch to First-Come-First-Serve scheduling mode\n";
	logger << "   roundrobin/rr <time quantum>\n";
	logger << "      Switch to Round Robin scheduling mode\n";
	logger << "   trace <on/off>\n";
	logger << "      Switch trace mode\n";
	logger << "   stepinfo <on/off>\n";
	logger << "      Switch process step informations\n";
	logger << "   init/restart\n";
	logger << "      Reset system to initial state\n";
	logger << "   status\n";
	logger << "      Show system status\n";
	logger << "   system/sys <cmd> [cmd]...\n";
	logger << "      Run system command\n";
	logger << "   assembly/asm\n";
	logger << "      Help on Assembly Language used in OS Simulator\n";
	logger << "   help/?\n";
	logger << "      This message\n";
	logger << "   quit/exit\n";
	logger << "      Quit OS Simulator\n";
}

void printAssemblyHelp(Logger logger){
	logger << "4 Instruction types:\n";
	logger << "   Format 0: [OpCode] [Unused] [InstructionType]\n";
	logger << "             [XXXX][0000 00000000 00000000 000000][00]\n";
	logger << "   Format 1: [OpCode] [R1] [R2] [Unused] [InstructionType]\n";
	logger << "             [XXXX][XXXX][XXXX][00000000 00000000][01]\n";
	logger << "   Format 2: [OpCode] [R] [Immediate] [InstructionType]\n";
	logger << "             [XXXX][XXXX][XXXXXXXX XXXXXXXX XXXXXX][10]\n";
	logger << "   Format 3: [OpCode] [Address] [InstructionType]\n";
	logger << "             [XXXX][XXXX XXXXXXXX XXXXXXXX XXXXXX][11]\n";
	logger << "\n";
	logger << "Instruction Set Table\n";
	uiTable* table = new uiTable(logger);
	table->addColumn("Mnemonic", UITABLE_LEFT);
	table->addColumn("Format", UITABLE_CENTER);
	table->addColumn("OpCode", UITABLE_CENTER);
	table->addColumn("Effect", UITABLE_LEFT);
	asmF0Instruction::addUsage(table);
	asmF1Instruction::addUsage(table);
	asmF2Instruction::addUsage(table);
	asmF3Instruction::addUsage(table);
	table->print();
}