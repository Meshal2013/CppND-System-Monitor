#include "processor.h"
#include "linux_parser.h"

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  this->jiffies = LinuxParser::Jiffies();
  this->ActivJiffies = LinuxParser::ActiveJiffies();
  this->IdleJiffies = LinuxParser::IdleJiffies();

  
  return (float)this->ActivJiffies /(float)( this->jiffies); 
}