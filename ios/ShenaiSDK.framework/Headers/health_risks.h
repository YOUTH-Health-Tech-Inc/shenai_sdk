#pragma once

#include <optional>

#include "health_risks_factors.h"

namespace mx::health_risks {

//////////////////////////////////////////////////////////////////////////////////////////////////
/// 10-year risk of hard or fatal cardiovascular events
struct HardAndFatalEventsRisks {
  // Risk of fatal cardiovascular event: coronary death based on Euro SCORE
  std::optional<float> coronary_death_event_risk;
  // Risk of fatal cardiovascular event: stroke based on Euro SCORE
  std::optional<float> fatal_stroke_event_risk;
  // Total risk of cardiovascular mortality (coronary + stroke) based on Euro SCORE
  std::optional<float> total_cv_mortality_risk;
  // Risk of hard cardiovascular event (coronary death, myocardial infarction, or stroke)
  // based on Pooled Cohort Equations (USA)
  std::optional<float> hard_cv_event_risk;
};

////////////////////////////////////////////////////////////////////////////////////////////////
/// 10-year risk of atherosclerotic cardiovascular disease (CVD) based on Framingham Heart Study
struct CVDiseasesRisks {
  // Risk of atherosclerotic cardiovascular disease (CVD) – overall risk
  std::optional<float> overall_risk;
  // Risk of coronary heart disease (myocardial infarction, coronary death, coronary insufficiency, angina)
  std::optional<float> coronary_heart_disease_risk;
  // Risk of stroke (ischemic stroke, hemorrhagic stroke, transient ischemic attack)
  std::optional<float> stroke_risk;
  // Risk of heart failure
  std::optional<float> heart_failure_risk;
  // Risk of peripheral vascular disease (intermittent claudication)
  std::optional<float> peripheral_vascular_disease_risk;
};

////////////////////////////////////////////////////////////////////////////////////////////////
/// Risk factors scores
struct RisksFactorsScores {
  std::optional<int> age_score;
  std::optional<int> sbp_score;
  std::optional<int> smoking_score;
  std::optional<int> diabetes_score;
  std::optional<int> bmi_score;
  std::optional<int> cholesterol_score;
  std::optional<int> cholesterol_hdl_score;
  std::optional<int> total_score;
};

// summary struct for all risks-related results
struct HealthRisks {
  HardAndFatalEventsRisks hard_and_fatal_events;
  CVDiseasesRisks cv_diseases;
  std::optional<int> vascular_age;
  RisksFactorsScores scores;
};

// Reference risks factors - the same age, gender, country and race but normal other factors
RisksFactors getReferenceRisksFactors(const RisksFactors& risk_factors);

// Compute all metrics available from provided risk factors
__attribute__((visibility("default"))) __attribute__((used)) HealthRisks computeHealthRisks(
    const RisksFactors& risk_factors);

HardAndFatalEventsRisks computeHardAndFatalEventsRisks(const RisksFactors& risk_factors);

CVDiseasesRisks computeCVDRisks(const RisksFactors& risk_factors);

// Vascular age - age of a person with the same predicted overall risk for developing CVD but with all risk factors
// at a normal level
std::optional<int> vascularAge(const RisksFactors& risk_factors);

// total risk score, based on Framingham Risk factors
RisksFactorsScores computeScores(const RisksFactors& risk_factors);

// compute maximal and minimal risks available for provided factors (gender and base - cholesterol or BMI)
__attribute__((visibility("default"))) __attribute__((used)) HealthRisks getMaximalRisks(
    const RisksFactors& risk_factors);
__attribute__((visibility("default"))) __attribute__((used)) HealthRisks getMinimalRisks(
    const RisksFactors& risk_factors);

}  // namespace mx::health_risks
