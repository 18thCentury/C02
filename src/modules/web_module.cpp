#include "iot/modules/web_module.hpp"

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace iot {

std::string WebModule::name() const { return "web"; }

bool WebModule::initialize(const ConfigStore& config, Logger& logger) {
  const auto bind = config.get_or("web_bind", "0.0.0.0:8080");
  logger.log(LogLevel::kInfo, "web init: bind=" + bind);
  return true;
}

bool WebModule::start(Logger& logger) {
  logger.log(LogLevel::kInfo, "web start: management API online");
  return true;
}

void WebModule::stop(Logger& logger) { logger.log(LogLevel::kInfo, "web stop"); }

}  // namespace iot
