#pragma once

#include <optional>
#include <string>

namespace mx::health_risks {

enum class Gender { male, female, other };

enum class Race { white, african_american, other };

struct RisksFactors {
  std::optional<int> age;
  std::optional<float> cholesterol;
  std::optional<float> cholesterol_hdl;
  std::optional<float> sbp;
  std::optional<bool> is_smoker;
  std::optional<bool> hypertension_treatment;
  std::optional<bool> has_diabetes;
  std::optional<float> body_height;  // centimeters
  std::optional<float> body_weight;  // kilograms
  std::optional<Gender> gender;
  std::string country;  // country name ISO code: https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
  std::optional<Race> race;
};

}  // namespace mx::health_risks