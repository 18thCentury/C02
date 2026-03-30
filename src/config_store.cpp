#include "iot/config_store.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <fstream>

namespace iot {

bool ConfigStore::load(const std::string& path) {
  std::ifstream in(path);
  if (!in.is_open()) {
    return false;
  }

  data_.clear();
  std::string line;
  while (std::getline(in, line)) {
    const std::string normalized = trim(line);
    if (normalized.empty() || normalized[0] == '#') {
      continue;
    }

    const auto split = normalized.find('=');
    if (split == std::string::npos) {
      continue;
    }

    const auto key = trim(normalized.substr(0, split));
    const auto value = trim(normalized.substr(split + 1));
    if (!key.empty()) {
      data_[key] = value;
    }
  }

  return true;
}

bool ConfigStore::save(const std::string& path) const {
  std::ofstream out(path, std::ios::trunc);
  if (!out.is_open()) {
    return false;
  }

  for (const auto& [key, value] : data_) {
    out << key << '=' << value << '\n';
  }
  return true;
}

std::optional<std::string> ConfigStore::get(const std::string& key) const {
  const auto it = data_.find(key);
  if (it == data_.end()) {
    return std::nullopt;
  }
  return it->second;
}

std::string ConfigStore::get_or(const std::string& key, const std::string& fallback) const {
  return get(key).value_or(fallback);
}

int ConfigStore::get_int_or(const std::string& key, int fallback) const {
  const auto value = get(key);
  if (!value.has_value()) {
    return fallback;
  }

  int parsed = 0;
  const char* begin = value->data();
  const char* end = begin + value->size();
  const auto result = std::from_chars(begin, end, parsed);
  if (result.ec != std::errc{} || result.ptr != end) {
    return fallback;
  }
  return parsed;
}

bool ConfigStore::get_bool_or(const std::string& key, bool fallback) const {
  const auto value = get(key);
  if (!value.has_value()) {
    return fallback;
  }

  std::string lowered = *value;
  std::transform(lowered.begin(), lowered.end(), lowered.begin(), [](unsigned char c) {
    return static_cast<char>(std::tolower(c));
  });

  if (lowered == "1" || lowered == "true" || lowered == "yes" || lowered == "on") {
    return true;
  }
  if (lowered == "0" || lowered == "false" || lowered == "no" || lowered == "off") {
    return false;
  }
  return fallback;
}

void ConfigStore::set(std::string key, std::string value) { data_[std::move(key)] = std::move(value); }

std::string ConfigStore::trim(std::string value) {
  auto not_space = [](unsigned char c) { return !std::isspace(c); };
  value.erase(value.begin(), std::find_if(value.begin(), value.end(), not_space));
  value.erase(std::find_if(value.rbegin(), value.rend(), not_space).base(), value.end());
  return value;
}

}  // namespace iot
