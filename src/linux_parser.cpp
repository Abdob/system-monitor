#include "linux_parser.h"

#include <dirent.h>
#include <unistd.h>

#include <sstream>
#include <string>
#include <vector>

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
  string os, kernel, version;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR *directory = opendir(kProcDirectory.c_str());
  struct dirent *file;
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

float LinuxParser::MemoryUtilization() {
  std::vector<string> field(3);
  std::vector<string> value(3);

  std::ifstream stream(kProcDirectory + kMeminfoFilename);
  if (stream.is_open()) {
    for (int i = 0; i < 3; i++) {
      std::string line;
      std::getline(stream, line);
      std::istringstream linestream(line);
      linestream >> field[i] >> value[i];
    }
  }
  long int memTotal = std::atol(value[0].c_str());
  long int memFree = std::atol(value[1].c_str());
  long int memAvailable = std::atol(value[2].c_str());

  float util = (float)(memTotal - memAvailable - memFree) / memTotal;
  return util;
}

long LinuxParser::UpTime() {
  string value;
  string line;
  std::ifstream stream(kProcDirectory + kUptimeFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> value;
  }
  long uptime = std::atoll(value.c_str());
  return uptime;
}

// NOT DONE: Hasn't been needed
long LinuxParser::Jiffies() { return 0; }

// TODO: Read and return the number of active jiffies for a PID
long LinuxParser::ActiveJiffies(int pid) {
  /*string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid")
        return value;
    }
  }
  return value;*/
}

long LinuxParser::ActiveJiffies() {
  string cpu, user, nice, system;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system;
  }
  long userJiffies = std::atol(user.c_str());
  long niceJiffies = std::atol(nice.c_str());
  long systemJiffies = std::atol(system.c_str());

  return userJiffies + niceJiffies + systemJiffies;
}

long LinuxParser::IdleJiffies() {
  string cpu, user, nice, system, idle;
  string line;
  std::ifstream stream(kProcDirectory + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> cpu >> user >> nice >> system >> idle;
  }
  long idleJiffies = std::atol(idle.c_str());
  return idleJiffies;
}

// DONE: Implemented in processor.cpp with instantaneous utilization
vector<string> LinuxParser::CpuUtilization() { return {}; }

int LinuxParser::TotalProcesses() {
  std::string field;
  std::string value;
  int processes;

  std::ifstream stream(kProcDirectory + kStatFilename);
  std::string line;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> field >> value;
      if (field == "processes") {
        processes = std::atoi(value.c_str());
        return processes;
      }
    }
  }
  return 0;
}

int LinuxParser::RunningProcesses() {
  std::string field;
  std::string value;
  int processes;

  std::ifstream stream(kProcDirectory + kStatFilename);
  std::string line;
  if (stream.is_open()) {
    while (std::getline(stream, line)) {
      std::istringstream linestream(line);
      linestream >> field >> value;
      if (field == "procs_running") {
        processes = std::atoi(value.c_str());
        return processes;
      }
    }
  }
  return 0;
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid [[maybe_unused]]) { return string(); }

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid [[maybe_unused]]) { return string(); }

string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string value;
  std::ifstream filestream(kProcDirectory + "/" + std::to_string(pid) +
                           kStatusFilename);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> key >> value;
      if (key == "Uid")
        return value;
    }
  }
  return value;
}
string LinuxParser::User(int pid) {
  // get user id
  string uid = Uid(pid);
  string line, user, value, key;

  std::ifstream filestream(kPasswordPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream linestream(line);
      linestream >> user >> value >> key;
      if (key == uid)
        return user;
    }
  }
  return user;
}
#include <iostream>
long LinuxParser::UpTime(int pid) {
  long uptime;
  string line;
  string starttime;
  std::ifstream stream(kProcDirectory + "/" + std::to_string(pid) + kStatFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    for (int i = 1; i <= kUpTime_; i++) 
      linestream >> starttime;
    uptime = std::stol(starttime) / sysconf(_SC_CLK_TCK);
    return uptime;
  }
  return 0;
}

