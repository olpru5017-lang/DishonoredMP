#pragma once

#include <mutex>
#include <string>

namespace dmp {

class Logger {
  public:
    static Logger& instance();

    void setLogFile(const std::string& filePath);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void error(const std::string& msg);

  private:
    Logger() = default;
    void write(const std::string& level, const std::string& msg);

    std::mutex mutex_;
    std::string filePath_{"dishonored_mp.log"};
};

} // namespace dmp
