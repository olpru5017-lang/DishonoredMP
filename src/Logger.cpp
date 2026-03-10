#include "dmp/Logger.hpp"

#include <chrono>
#include <fstream>
#include <iomanip>

namespace dmp {

Logger& Logger::instance() {
    static Logger logger;
    return logger;
}

void Logger::setLogFile(const std::string& filePath) {
    std::scoped_lock lock(mutex_);
    filePath_ = filePath;
}

void Logger::info(const std::string& msg) { write("INFO", msg); }
void Logger::warn(const std::string& msg) { write("WARN", msg); }
void Logger::error(const std::string& msg) { write("ERROR", msg); }

void Logger::write(const std::string& level, const std::string& msg) {
    std::scoped_lock lock(mutex_);

    std::ofstream out(filePath_, std::ios::app);
    const auto now = std::chrono::system_clock::now();
    const auto tt = std::chrono::system_clock::to_time_t(now);
    out << std::put_time(std::localtime(&tt), "%F %T") << " [" << level << "] " << msg << '\n';
}

} // namespace dmp
