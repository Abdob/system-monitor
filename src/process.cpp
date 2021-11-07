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
      uptime_(LinuxParser::UpTime(pid)), command_(LinuxParser::Command(pid)),
      ram_(LinuxParser::Ram(pid)) {}

int Process::Pid() { return pid_; }

string Process::User() { return user_; }

float Process::CpuUtilization() {
  long int jiffies = LinuxParser::ActiveJiffies(pid_);
  cpuUtilization_ = (float)jiffies / uptime_;
  return cpuUtilization_;
}

string Process::Command() { return command_; }

string Process::Ram() { return ram_; }

long int Process::UpTime() {
  long int seconds = uptime_ / sysconf(_SC_CLK_TCK);
  return seconds;
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const &a [[maybe_unused]]) const {
  return true;
}