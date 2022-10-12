#ifndef LOGGERI_HPP
#define LOGGERI_HPP
#include <string>

// Data acquisition macro
#define __METHOD_NAME__ Logger::methodName(__PRETTY_FUNCTION__)

class LoggerI {
public:
  static inline std::string methodName(const std::string &prettyFunction) {
    size_t colons = prettyFunction.find("::");
    size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
    size_t end = prettyFunction.rfind("(") - begin;

    return prettyFunction.substr(begin, end) + "()";
  }
};
#endif