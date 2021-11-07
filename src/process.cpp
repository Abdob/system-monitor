#include "process.h"

#include <unistd.h>

#include <cctype>
#include <sstream>
#include <string>
#include <vector>

using std::string;
using std::to_string;
using std::vector;

Process::Process(int pid)
    : pid_(pid), user_(LinuxParser::User(pid)),
      uptime_(LinuxParser::UpTime(pid)) {}

int Process::Pid() { return pid_; }

string Process::User() { return user_; }

float Process::CpuUtilization() {
  long int jiffies = LinuxParser::ActiveJiffies(pid_);
  cpuUtilization_ = (float)jiffies / uptime_;
  return cpuUtilization_;
  }

// TODO: Return the command that generated this process
string Process::Command() { return string(); }

// TODO: Return this process's memory utilization
string Process::Ram() { return string(); }

long int Process::UpTime() {
  long int seconds = uptime_ / sysconf(_SC_CLK_TCK);
  return seconds;
  }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a [[maybe_unused]]) const {
  return true;
}