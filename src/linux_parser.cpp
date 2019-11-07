#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include <iostream>
#include <unistd.h>

#include "linux_parser.h"

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
  string key, value;
  string line;
  float memTotal,memFree,memAvailable,buffer;
  float totalUsedMemory;
  vector<float> meminfo;
  
  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    for(int i = 0 ; i < 4 ; i++ ){
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> key >> value;
    meminfo.push_back(std::stof(value));
    }
    memTotal = meminfo[0]; memFree = meminfo[1]; memAvailable = meminfo[2]; buffer = meminfo[3];
    
  }
  return  (memTotal - memFree ) / memTotal;
  }

// TODO: Read and return the system uptime
long LinuxParser::UpTime() { 
   long key, value;
  	string line;
    std::ifstream stream(kProcDirectory + kUptimeFilename);
   if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> key >> value;
  }
 
return key;

}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
    string cpu, user, nice ,system_ ,idle ,iowait , irq ,softirq, steal, guest, guest_nice;
  	string line;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user>> nice >> system_ >>idle >>iowait >> irq >> softirq>>  steal>> guest>> guest_nice;
    }
   
 
  return stol(user)+stol(nice)+stol(system_)+stol(idle)+stol(iowait)+stol(irq)+stol(softirq)+stol(steal); 
 
     }

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid) {
   string strpid = to_string(1);
    std::ifstream stream(kProcDirectory + strpid + kStatFilename);
    string line ;
  long utime , stime,cutime , cstime , starttime ;
  string value;
    if (stream.is_open()) {
 		getline(stream, line);
   std::istringstream linestream(line);

    for (int i = 1 ; i <= 22 ; i++ ){
      linestream >> value ;
      if (i == 14 )
   		  utime = stol(value) ;
      else if (i == 15 )
   		 stime  = stol(value);
      else if (i ==16 )
   	  cutime = stol(value) ;
     else  if (i == 17 )
   		 cstime  = stol(value);
     else  if (i == 22 )
   		 starttime  = stol(value) ;
     
     
        }
    }
  	float total_time = utime + stime;
  	total_time = total_time + cutime + cstime;
    float  seconds = UpTime() - (starttime / sysconf(_SC_CLK_TCK));
    //  std::cerr <<  ((total_time / (float)sysconf(_SC_CLK_TCK)) / seconds) << "gggggggggggggggggggg";

  return  100 * ((total_time / (float)sysconf(_SC_CLK_TCK)) / seconds);/// (float)sysconf(_SC_CLK_TCK)) / seconds);
   }




// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() {  return Jiffies() - IdleJiffies(); }

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
    string cpu, user, nice ,system_ ,idle ,iowait , irq ,softirq, steal, guest, guest_nice;
  	string line;
  
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user>> nice >>system_ >>idle >>iowait >> irq >> softirq>>  steal>> guest>> guest_nice;
    }

  return stol(idle)+stol(iowait);
}







// TODO: Read and return CPU utilization
vector<string> LinuxParser::CpuUtilization() {
  
  
  return {}; }

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
  int totalProcesses;
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line, key, value;
  if (stream.is_open()) {
    while (getline(stream, line )) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "processes") {
          totalProcesses = stoi(value);
        }
      }
    }
  }
  return totalProcesses; 
  
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
  int runningProcesses;
  std::ifstream stream(kProcDirectory + kStatFilename);
  string line, key, value;
  if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "procs_running") {
          runningProcesses = stoi(value);
        }
      }
    }
  }
  return runningProcesses; 
   }

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) { 
  string strpid = to_string(pid);
    std::ifstream stream(kProcDirectory + strpid + kCmdlineFilename);
    string line;
    if (stream.is_open()) 
 		getline(stream, line);
  return line; }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
  string strpid = to_string(pid);
    std::ifstream stream(kProcDirectory + strpid + kStatusFilename);
    string line, key, value, kb;
    if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value >> kb) {
        if (key == "VmSize:" && kb == "kB") {
          long mb = stol(value);
  mb /= 1000 ;
  value = to_string(mb);
          return value ;
        }
      }
    }
  }
  
  
  return value; }

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) { 
    string strpid = to_string(pid);
    std::ifstream stream(kProcDirectory + strpid + kStatusFilename);
    string line, key, value;
    if (stream.is_open()) {
    while (getline(stream, line)) {
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "Uid:") {
          return value;
        }
      }
    }
  }
  return value;
  }

// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::User(int pid) { 
   string strpid = to_string(pid);
    std::ifstream stream(kPasswordPath);
    string line, key;
    if (stream.is_open()) {
    while (getline(stream, line)) {
       std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      while (linestream >> key ) {
        if (key == "root") {
                    std::replace(line.begin(), line.end(), ' ', ':');
          return key;
        }
      }
    }
  }
  return key;
  
   }

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
  	 string strpid = to_string(pid);
    std::ifstream stream(kProcDirectory+strpid+kStatFilename);
    string line, key;
    if (stream.is_open()) {
          getline(stream, line);
            std::istringstream linestream(line);
      for (int i = 0 ; i < 22 ; i++ )
   				 linestream >> key ;
        //  std::cerr  << key<< " fdfffffffffffff";
          return stol(key) ;
        }
                std::cerr  << key<< " fdfffffffffffff";

  return stol(key)/(long)sysconf(_SC_CLK_TCK);
   }