#include "iot/legacy_bootstrap.hpp"

#include <filesystem>
#include <fstream>
#include <system_error>

#include "iot/config_store.hpp"
#include "iot/logger.hpp"

namespace fs = std::filesystem;

namespace iot {

bool LegacyBootstrap::run(const ConfigStore& config, Logger& logger) const {
  const bool tech_mode = config.get("tech_mode").value_or("0") == "1";

  if (!ensure_system_ini(logger)) {
    return false;
  }

  if (!sync_his_tech(tech_mode, logger)) {
    return false;
  }

  logger.log(LogLevel::kInfo, "iot started tech_mode=" + bool_to_flag(tech_mode));
  return true;
}

bool LegacyBootstrap::ensure_system_ini(Logger& logger) const {
  const fs::path system_ini{"/tmp/.system.ini"};
  std::error_code ec;

  if (!fs::exists(system_ini, ec)) {
    std::ofstream touch(system_ini);
    if (!touch.is_open()) {
      logger.log(LogLevel::kError, "failed to create /tmp/.system.ini");
      return false;
    }
    logger.log(LogLevel::kInfo, "SYSTEM   START");
  }

  logger.log(LogLevel::kInfo, "start iot");
  return true;
}

bool LegacyBootstrap::sync_his_tech(bool tech_mode, Logger& logger) const {
  const fs::path tmp_his_tech{"/tmp/hisTech.ini"};
  const fs::path local_his_tech{"hisTech.ini"};
  std::error_code ec;

  if (!fs::exists(tmp_his_tech, ec)) {
    if (!fs::exists(local_his_tech, ec)) {
      logger.log(LogLevel::kInfo, "iot init v1 START");
      return true;
    }

    if (tech_mode) {
      fs::copy_file(local_his_tech, tmp_his_tech, fs::copy_options::overwrite_existing, ec);
      if (ec) {
        logger.log(LogLevel::kError, "copy hisTech.ini -> /tmp failed: " + ec.message());
        return false;
      }
      logger.log(LogLevel::kInfo, "iot init v2 START");
    } else {
      fs::rename(local_his_tech, tmp_his_tech, ec);
      if (ec) {
        logger.log(LogLevel::kError, "move hisTech.ini -> /tmp failed: " + ec.message());
        return false;
      }
      logger.log(LogLevel::kInfo, "iot init v1 manual START");
    }

    return true;
  }

  logger.log(LogLevel::kInfo, "iot   UPDATE /tmp/hisTech.ini");
  if (tech_mode) {
    fs::copy_file(tmp_his_tech, local_his_tech, fs::copy_options::overwrite_existing, ec);
    if (ec) {
      logger.log(LogLevel::kError, "copy /tmp/hisTech.ini -> local failed: " + ec.message());
      return false;
    }
    logger.log(LogLevel::kInfo, "tech mode copy back hisTech.ini");
  }

  return true;
}

std::string LegacyBootstrap::bool_to_flag(bool value) { return value ? "1" : "0"; }

}  // namespace iot
