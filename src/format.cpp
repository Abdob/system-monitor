#include "format.h"

#include <string>
#include <sstream>

using std::string;

// INPUT: Long int measuring seconds
// OUTPUT: HH:MM:SS
string Format::ElapsedTime(long seconds ) {
    int hours = seconds / 3600;
    int mins = (seconds / 60 ) % 60;
    int secs = seconds % 60;
    std::stringstream ss;
    ss << hours << ":" << mins << ":" << secs;
    return ss.str();
}