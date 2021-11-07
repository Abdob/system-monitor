#ifndef SYSTEM_H
#define SYSTEM_H

#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"

class System {
 public:
  System();
  Processor& Cpu();                   
  std::vector<Process>& Processes();
  float MemoryUtilization();          
  long UpTime();                      // TODO: See src/system.cpp
  int TotalProcesses();               
  int RunningProcesses();             // TODO: See src/system.cpp
  std::string Kernel();
  std::string OperatingSystem();

  // TODO: Define any necessary private members
 private:
  Processor cpu_ = {};
  std::vector<Process> processes_ = {};
  std::string os_;
  std::string kernel_;
  float memoryUtilization_;
  int totalProcesses_;
  int runningProcesses_;
};

#endif