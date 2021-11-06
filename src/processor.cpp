#include "processor.h"

Processor::Processor() : activeJiffies_(0), idleJiffies_(0) {}

float Processor::Utilization() {
    long lastActiveJiffies  = activeJiffies_;
    long lastIdleJiffies = idleJiffies_;
    activeJiffies_ = LinuxParser::ActiveJiffies();
    idleJiffies_ = LinuxParser::IdleJiffies();
    unsigned int dActive = activeJiffies_ - lastActiveJiffies;
    unsigned int dIdle = idleJiffies_ - lastIdleJiffies;
    utilization_ = (float) dActive / (dActive + dIdle);
    return utilization_;
}