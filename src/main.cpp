#include <memory>

#include "iot/app.hpp"
#include "iot/modules/modbus_module.hpp"
#include "iot/modules/mqtt_module.hpp"
#include "iot/modules/network_module.hpp"
#include "iot/modules/power_module.hpp"
#include "iot/modules/serial_module.hpp"
#include "iot/modules/web_module.hpp"

int main() {
  iot::Application app("config/system.ini");

  app.register_module(std::make_unique<iot::SerialModule>());
  app.register_module(std::make_unique<iot::NetworkModule>());
  app.register_module(std::make_unique<iot::MqttModule>());
  app.register_module(std::make_unique<iot::ModbusModule>());
  app.register_module(std::make_unique<iot::WebModule>());
  app.register_module(std::make_unique<iot::PowerModule>());

  return app.run();
}
