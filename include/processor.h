#ifndef PROCESSOR_H
#define PROCESSOR_H
#include "linux_parser.h"

class Processor {
 public:
  Processor();
  float Utilization();

 private:
  float utilization_;
  long activeJiffies_;
  long idleJiffies_;
};

#endif