#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <iostream> 
#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
// int Process::Pid(){ return 0;}
 int Process::Pid(){ 
 return this->pid ; 
}
  

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 

  return  LinuxParser::ActiveJiffies(pid); }

// TODO: Return the command that generated this process
string Process::Command() { return LinuxParser::Command(pid); }
// string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return LinuxParser::Ram(pid); }
// string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return LinuxParser::User(pid); }
// string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return LinuxParser::UpTime(pid); }
// long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }