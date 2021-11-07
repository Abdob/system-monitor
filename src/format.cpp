#include "format.h"

#include <iomanip>
#include <sstream>
#include <string>

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds) {
  int hours = seconds / 3600;
  int mins = (seconds / 60) % 60;
  int secs = seconds % 60;
  std::stringstream ss;

  ss << std::setw(2) << std::setfill('0') << hours << ":";
  ss << std::setw(2) << std::setfill('0') << mins << ":";
  ss << std::setw(2) << std::setfill('0') << secs << "\n";
  return ss.str();
}