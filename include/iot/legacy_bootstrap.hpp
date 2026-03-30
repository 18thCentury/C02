#pragma once

#include <string>

namespace iot {

class ConfigStore;
class Logger;

class LegacyBootstrap {
 public:
  bool run(const ConfigStore& config, Logger& logger) const;

 private:
  bool ensure_system_ini(Logger& logger) const;
  bool sync_his_tech(bool tech_mode, Logger& logger) const;
  static std::string bool_to_flag(bool value);
};

}  // namespace iot
