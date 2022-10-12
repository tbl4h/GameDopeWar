#include "Logger.hpp"
#include "Constants.hpp"
#include <fstream>
#include <stdexcept>

using std::ofstream;
using std::runtime_error;
using std::string;

// Constant declaration for Logger class
/////////////////////////////////////////////////////
const std::string std_logfile_name = "DrugGame.log";
const std::string err_logfile_name = "DrugGame_err.log";

// Static declaration
/////////////////////////////////////////////////////

ofstream Logger::std_fstream{std_logfile_name};
ofstream Logger::err_fstream{err_logfile_name};

Logger *Logger::logger = nullptr;

Logger::Logger() {
  if (!std_fstream.is_open()) {
    std_fstream.open(std_logfile_name);
    if (!std_fstream.is_open()) {
      throw runtime_error(Logger::error_msg(
          __METHOD_NAME__, ":Standard Logfile opening failed."));
    }
  }
  if (!err_fstream.is_open()) {
    err_fstream.open(err_logfile_name);
    if (!std_fstream.is_open()) {
      throw runtime_error(
          Logger::error_msg(__METHOD_NAME__, ":Error Logfile opening failed."));
    }
  }
}

auto Logger::get_logger() -> Logger * {
  if (logger == nullptr) {
    logger = new Logger;
  }
  return logger;
}

auto Logger::close_logger() -> void {
  if (std_fstream.is_open() == true && err_fstream.is_open() == true) {
    std_fstream.close();
    err_fstream.close();
  }
}

Logger::~Logger() {
  delete logger;
  close_logger();
}