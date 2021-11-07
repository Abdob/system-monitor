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
    : os_(LinuxParser::OperatingSystem()), kernel_(LinuxParser::Kernel()), memoryUtilization_(0.0f) {}

Processor& System::Cpu() { return cpu_; }

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() { return processes_; }

std::string System::Kernel() { return kernel_; }

float System::MemoryUtilization() {
    memoryUtilization_ = LinuxParser::MemoryUtilization();
    return memoryUtilization_;
}

std::string System::OperatingSystem() { return os_; }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return 0; }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return 0; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { return 0; }
