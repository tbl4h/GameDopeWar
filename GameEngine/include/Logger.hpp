#ifndef LOGGER_HPP
#define LOGGER_HPP
#include <cstddef>
#include <fstream>

// Data acquisition macro
#define __METHOD_NAME__ Logger::methodName(__PRETTY_FUNCTION__)

/**
 * @brief Use class inside Locator class. Class will be potencially
 * rebuild for a reason to due a proggramer must closed a open files
 * usied by the class: std_fstream and err_fstream.
 *
 *
 */
class Logger {
  // Priveate member
  static std::ofstream std_fstream;
  static std::ofstream err_fstream;
  static Logger *logger;
  // Protected constructor for singleton ensure
private:
  Logger();
  Logger(const Logger &LoggerCopy) = delete;
  Logger(const Logger &&LoggerMove) noexcept = delete;
  // Operators
  auto operator=(const Logger &Rhs) -> Logger & = delete;
  auto operator=(Logger &&Rhs) noexcept -> Logger & = delete;

public:
  // Constructors and destructor
  ~Logger();
  // Singleton constructor method
  static auto get_logger() -> Logger *;
  static auto close_logger() -> void;
  static inline std::string methodName(const std::string &prettyFunction) {
    size_t colons = prettyFunction.find("::");
    size_t begin = prettyFunction.substr(0, colons).rfind(" ") + 1;
    size_t end = prettyFunction.rfind("(") - begin;
    std::string ret_string = prettyFunction.substr(begin, end) + "()";
    return ret_string;
  }

  // Arguments should be separated by whitespace char for readability.
  template <typename... Args>
  static inline auto error_msg(Args &&...args) -> std::string {
    std::string ret_str;
    (ret_str += ... += args) += '\n';
    return ret_str;
  }

  // Arguments should be separated by whitespace char for readability.
  template <typename... Args> inline auto log_msg(Args &&...args) -> void {
    (std_fstream << ... << args) << '\n';
  }

  // Arguments should be separated by whitespace char for readability.
  template <typename... Args> inline auto log_err_msg(Args &&...args) -> void {
    (err_fstream << ... << args) << '\n';
  }
};

#endif