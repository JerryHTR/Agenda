#include "Log.h"
#include <cstdio>
#include <cstring>
#include <time.h>

void Log::writeToFile(std::string s) {
  time_t t = time(0);
  char str[100];
  std::ofstream out("./Log.data", std::ofstream::app);
  strftime(str, sizeof(str), "%Y-%m-%d/%I:%M:%S\n", localtime(&t));
  std::string ns(str);
  out << "***  " << s << " ------" << ns << std::endl;
  out.close();
}

