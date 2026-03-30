#pragma once

#include "iot/module.hpp"

namespace iot {

class WebModule final : public Module {
 public:
  std::string name() const override;
  bool initialize(const ConfigStore& config, Logger& logger) override;
  bool start(Logger& logger) override;
  void stop(Logger& logger) override;
};

}  // namespace iot
