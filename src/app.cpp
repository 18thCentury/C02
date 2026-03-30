#include "iot/app.hpp"

#include "iot/legacy_bootstrap.hpp"
#include "iot/parameter_collector.hpp"

namespace iot {

Application::Application(std::string config_path)
    : config_path_(std::move(config_path)), logger_("iot-industrial") {}

void Application::register_module(std::unique_ptr<Module> module) { modules_.push_back(std::move(module)); }

int Application::run() {
  logger_.log(LogLevel::kInfo, "Application start");

  if (!config_.load(config_path_)) {
    logger_.log(LogLevel::kWarn, "Config file not found, creating default config");
    config_.set("system_started", "1");
    config_.set("tech_mode", "0");
    if (!config_.save(config_path_)) {
      logger_.log(LogLevel::kError, "failed to save default config");
      return 10;
    }
  }

  LegacyBootstrap bootstrap;
  if (!bootstrap.run(config_, logger_)) {
    logger_.log(LogLevel::kError, "legacy bootstrap flow failed");
    return 11;
  }

  ParameterCollector collector;
  const auto snapshot = collector.collect(logger_);
  for (const auto& [key, value] : snapshot) {
    config_.set("runtime." + key, value);
  }
  config_.save(config_path_);

  for (auto& module : modules_) {
    logger_.log(LogLevel::kInfo, "Initializing module: " + module->name());
    if (!module->initialize(config_, logger_)) {
      logger_.log(LogLevel::kError, "Failed to initialize module: " + module->name());
      return 1;
    }
  }

  for (auto& module : modules_) {
    logger_.log(LogLevel::kInfo, "Starting module: " + module->name());
    if (!module->start(logger_)) {
      logger_.log(LogLevel::kError, "Failed to start module: " + module->name());
      return 2;
    }
  }

  logger_.log(LogLevel::kInfo, "Application started successfully");

  for (auto it = modules_.rbegin(); it != modules_.rend(); ++it) {
    logger_.log(LogLevel::kInfo, "Stopping module: " + (*it)->name());
    (*it)->stop(logger_);
  }

  logger_.log(LogLevel::kInfo, "Application shutdown complete");
  return 0;
}

}  // namespace iot
