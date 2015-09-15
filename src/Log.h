#ifndef LOG_H
#define LOG_H
#include <iostream>
#include <fstream>
#include "AgendaUI.h"

class Log {
 public:
  Log() {}
  ~Log() {}
  void writeToFile(std::string s);
};

#endif
