#ifndef PROCESS_H
#define PROCESS_H

#include "linux_parser.h"
#include <string>
/*
Basic class for Process representation
It contains relevant attributes as shown below
*/
class Process {
public:
  Process(int pid);
  int Pid();
  std::string User();
  float CpuUtilization();
  std::string Command();
  std::string Ram();
  long int UpTime();
  bool operator<(Process const &a) const;

private:
  int pid_;
  std::string user_;
  float cpuUtilization_;
  long int uptime_;
  std::string command_;
  std::string ram_;
};

#endif