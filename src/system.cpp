#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>


#include "process.h"
#include "processor.h"
#include "system.h"
#include  "linux_parser.h"
#include <iostream>
using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 

	Processor* cpu = new Processor();
  return *cpu; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { 
  
   vector<int> pids = LinuxParser::Pids();
  vector<Process> processes ;  
  for (int item : pids ){
    //std::cerr << "process # "<< item << "\n" ;
    Process *p = new Process(item);
    processes.push_back(*p);
    //std::cerr << "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee # "<< item << "\n" ;

  }
   // std::cerr << "fffffffffffffffffffffffffffffffffff # " << "\n" ;

  this->processes_ = processes;
 //return processes;
  return processes_ ;
  }

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { 
  this->kernal =LinuxParser::Kernel();
  
  return this->kernal;
  }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
    this->memoryUtilization =LinuxParser::MemoryUtilization();
  
  return this->memoryUtilization ;
  }

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  
  this->os =LinuxParser::OperatingSystem();
  
  return this->os;
}

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { 
   this->runningProcesses =LinuxParser::RunningProcesses();
  
  return this->runningProcesses;
  
  }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  this->totalProcesses =LinuxParser::TotalProcesses();
  
  return this->totalProcesses;
   }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    this->upTime =LinuxParser::UpTime();

  return this->upTime; }