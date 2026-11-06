#pragma once
#include <algorithm>
#include <cctype>
#include <initializer_list>
#include <string>

namespace esphome::waste_collection {

// Calendar names stay as supplied by Home Assistant. Only their colour is classified here, without LVGL or a clock.
// The host test in tests/test_waste_kind.cpp covers Norwegian, Dutch and English names, including mixed packaging.
enum class WasteKind { GENERAL, PAPER, ORGANIC, PLASTIC, GLASS_METAL };

inline WasteKind waste_kind(const std::string &what) {
  std::string low = what;
  std::transform(low.begin(), low.end(), low.begin(), [](unsigned char c) { return std::tolower(c); });
  auto has = [&](std::initializer_list<const char *> words) {
    for (const char *word : words)
      if (low.find(word) != std::string::npos) return true;
    return false;
  };
  if (has({"papier", "paper", "karton", "cardboard", "papir", "papp"})) return WasteKind::PAPER;
  if (has({"gft", "groen", "green", "garden", "tuin", "bio", "organic", "food", "compost", "matavfall", "hageavfall"}))
    return WasteKind::ORGANIC;
  // Glass and metal packaging must be recognised before the general word for packaging (emballasje).
  if (has({"glas", "glass", "metall", "metal"})) return WasteKind::GLASS_METAL;
  if (has({"plastic", "pmd", "pbd", "packag", "verpakking", "blik", "plast", "emballasje"})) return WasteKind::PLASTIC;
  return WasteKind::GENERAL;
}

}  // namespace esphome::waste_collection
