#include "system.h"

#include <unistd.h>

#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric
criteria "The student will be able to extract and display basic data about the
system."

You need to properly format the uptime. Refer to the comments mentioned in
format. cpp for formatting the uptime.*/
System::System()
    : os_(LinuxParser::OperatingSystem()), kernel_(LinuxParser::Kernel()),
      memoryUtilization_(0.0f), totalProcesses_(0), runningProcesses_(0),
      uptime_(0) {}

Processor &System::Cpu() { return cpu_; }

vector<Process> &System::Processes() {
  // vector<int> pids = LinuxParsers::Pids();

  // processes_(pids.size());

  return processes_;
}

std::string System::Kernel() { return kernel_; }

float System::MemoryUtilization() {
  memoryUtilization_ = LinuxParser::MemoryUtilization();
  return memoryUtilization_;
}

std::string System::OperatingSystem() { return os_; }

int System::RunningProcesses() {
  runningProcesses_ = LinuxParser::RunningProcesses();
  return runningProcesses_;
}

int System::TotalProcesses() {
  totalProcesses_ = LinuxParser::TotalProcesses();
  return totalProcesses_;
}

long System::UpTime() {
  uptime_ = LinuxParser::UpTime();
  return uptime_;
}
