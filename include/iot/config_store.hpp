#pragma once

#include <optional>
#include <string>
#include <unordered_map>

namespace iot {

class ConfigStore {
 public:
  bool load(const std::string& path);
  bool save(const std::string& path) const;

  std::optional<std::string> get(const std::string& key) const;
  std::string get_or(const std::string& key, const std::string& fallback) const;
  int get_int_or(const std::string& key, int fallback) const;
  bool get_bool_or(const std::string& key, bool fallback) const;

  void set(std::string key, std::string value);

 private:
  static std::string trim(std::string value);

  std::unordered_map<std::string, std::string> data_;
};

}  // namespace iot
