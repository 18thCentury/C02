#pragma once

#include <memory>
#include <string>
#include <vector>

#include "iot/config_store.hpp"
#include "iot/logger.hpp"
#include "iot/module.hpp"

namespace iot {

class Application {
 public:
  explicit Application(std::string config_path);

  void register_module(std::unique_ptr<Module> module);
  int run();

 private:
  std::string config_path_;
  Logger logger_;
  ConfigStore config_;
  std::vector<std::unique_ptr<Module>> modules_;
};

}  // namespace iot
