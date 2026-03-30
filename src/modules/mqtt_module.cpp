#include "iot/modules/mqtt_module.hpp"

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace iot {

std::string MqttModule::name() const { return "mqtt"; }

bool MqttModule::initialize(const ConfigStore& config, Logger& logger) {
  const auto broker = config.get_or("mqtt_broker", "tcp://127.0.0.1:1883");
  logger.log(LogLevel::kInfo, "mqtt init: broker=" + broker);
  return true;
}

bool MqttModule::start(Logger& logger) {
  logger.log(LogLevel::kInfo, "mqtt start: publish/subscribe loop online");
  return true;
}

void MqttModule::stop(Logger& logger) { logger.log(LogLevel::kInfo, "mqtt stop"); }

}  // namespace iot
