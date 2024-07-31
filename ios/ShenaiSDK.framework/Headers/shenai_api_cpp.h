#pragma once
#include <optional>
#include <string>
#include <vector>
#include <functional>

#define SHEN_PUBLIC_API __attribute__((visibility("default"))) __attribute__((used))

/**
 * This is a minimal C++ API surface for Shen AI SDK.
 * Only one instance of the SDK exists at a time.
 */

namespace shen {

/**
 * The precision mode of the SDK.
 */
enum class PrecisionMode { Strict = 0, Relaxed };

/**
 * The current screen displayed by the SDK.
 */
enum class Screen { Initialization = 0, Onboarding, Measurement, Instructions };

/**
 * The operating mode of the SDK.
 */
enum class OperatingMode { Positioning = 0, Measure, SystemOverloaded };

/**
 * Publicly available presets for the measurement session.
 */
enum class MeasurementPreset {
  OneMinuteHrHrvBr = 0,
  OneMinuteBetaMetrics,
  InfiniteHr,
  InfiniteMetrics,
  FourtyFiveSecondsUnvalidated,
  ThirtySecondsUnvalidated,
  Custom
};

/**
 * Configuration for a custom measurement session.
 */
struct custom_measurement_config {
  std::optional<float> duration_seconds{60};
  std::optional<bool> infinite_measurement{false};

  std::optional<bool> show_heart_rate{true};
  std::optional<bool> show_hrv_sdnn{true};
  std::optional<bool> show_breathing_rate{true};
  std::optional<bool> show_systolic_blood_pressure{true};
  std::optional<bool> show_diastolic_blood_pressure{true};
  std::optional<bool> show_cardiac_stress{true};

  std::optional<float> realtime_hr_period_seconds{10};
  std::optional<float> realtime_hrv_period_seconds{30};
  std::optional<float> realtime_cardiac_stress_period_seconds{30};
};

/**
 * Configuration for a custom color theme.
 */
struct custom_color_theme {
  std::string theme_color;
  std::string text_color;
  std::string background_color;
  std::string tile_color;
};

/**
 * Camera modes for the SDK.
 */
enum class CameraMode { Off = 0, FacingUser, FacingEnvironment, DeviceId };

/**
 * User onboarding mode
 */
enum class OnboardingMode { Hidden = 0, ShowOnce, ShowAlways };

/**
 * Events that can be sent to the event callback.
 */
enum class Event { START_BUTTON_CLICKED, STOP_BUTTON_CLICKED, MEASUREMENT_FINISHED };

/**
 * Additional settings for the initialization.
 */
struct initialization_settings {
  PrecisionMode precisionMode{PrecisionMode::Strict};
  OperatingMode operatingMode{OperatingMode::Positioning};
  MeasurementPreset measurementPreset{MeasurementPreset::OneMinuteBetaMetrics};
  CameraMode cameraMode{CameraMode::FacingUser};
  OnboardingMode onboardingMode{OnboardingMode::ShowOnce};

  bool showUserInterface{true};
  bool showFacePositioningOverlay{true};
  bool showVisualWarnings{true};
  bool enableCameraSwap{true};
  bool showFaceMask{true};
  bool showBloodFlow{true};
  bool proVersionLock{false};
  bool hideShenaiLogo{true};

  std::optional<custom_measurement_config> customMeasurementConfig;
  std::optional<custom_color_theme> customColorTheme;

  std::function<void(Event)> eventCallback = [](Event) {};
};

/**
 * The result of the SDK initialization.
 */
enum class InitializationResult { Success = 0, FailureInvalidApiKey, FailureConnectionError, FailureInternalError };

/**
 * Gets version of the SDK.
 */
SHEN_PUBLIC_API std::string GetVersion();

/**
 * Initializes the SDK.
 * This function must be called before any other function in this API (except for IsInitialized()).
 *
 * @param api_key The API key to use for license validation.
 * @param user_id The user ID to use for license validation (optional).
 * @param settings Additional settings for the initialization (optional).
 * @return The result of the initialization. If the SDK has previously been initialized and not deinitialized, this
 * function will return Success immediately.
 */
SHEN_PUBLIC_API InitializationResult Initialize(std::string api_key, std::string user_id = "",
                                                initialization_settings settings = {});

/**
 * Checks if the SDK has been successfully initialized.
 * @return True if the SDK has been successfully initialized, false otherwise.
 */
SHEN_PUBLIC_API bool IsInitialized();

/**
 * Deinitializes the SDK, releasing all resources.
 * This function must be called before the application exits.
 */
SHEN_PUBLIC_API void Deinitialize();

/**
 * Terminates tracing and sends remaining telemetry data to the server.
 * To be used as a last measure if the SDK wasn't deinitialized and the runtime is about to be terminated.
 */
SHEN_PUBLIC_API void FinalizeTracing();

/**
 * Sets the operational mode of the SDK.
 * @param mode The operational mode to set.
 */
SHEN_PUBLIC_API void SetOperatingMode(OperatingMode mode);

/**
 * Gets the operational mode of the SDK.
 * @return The operational mode of the SDK.
 */
SHEN_PUBLIC_API OperatingMode GetOperatingMode();

/**
 * Sets the view mode of the SDK.
 * @param mode The view mode to set.
 */
SHEN_PUBLIC_API void SetScreen(Screen screen);

/**
 * Gets the view mode of the SDK.
 * @return The view mode of the SDK.
 */
SHEN_PUBLIC_API Screen GetScreen();

/**
 * Sets the precision mode of the SDK.
 * @param mode The precision mode to set.
 */
SHEN_PUBLIC_API void SetPrecisionMode(PrecisionMode mode);

/**
 * Gets the precision mode of the SDK.
 * @return The precision mode of the SDK.
 */
SHEN_PUBLIC_API PrecisionMode GetPrecisionMode();

/**
 * Sets the measurement preset of the SDK.
 * @param preset The measurement preset to set.
 */
SHEN_PUBLIC_API void SetMeasurementPreset(MeasurementPreset preset);

/**
 * Sets the custom measurement configuration of the SDK.
 * Causes the SDK to enter Custom measurement mode.
 * @param config The custom measurement configuration to set.
 */
SHEN_PUBLIC_API void SetCustomMeasurementConfig(custom_measurement_config config);

/**
 * Gets the measurement preset of the SDK.
 * @return The measurement preset of the SDK.
 */
SHEN_PUBLIC_API MeasurementPreset GetMeasurementPreset();

/**
 * Sets the camera mode of the SDK.
 * @param mode The camera mode to set.
 */
SHEN_PUBLIC_API void SetCameraMode(CameraMode mode);

/**
 * Gets the camera mode of the SDK.
 * @return The camera mode of the SDK.
 */
SHEN_PUBLIC_API CameraMode GetCameraMode();

/**
 *  Selects the camera by ID (and changes to DeviceID mode if needed)
 *  and optionally specifies whether the camera is facing the user
 * @param device_id The ID of the selected camera device.
 * @param facing_user Whether the camera is facing the user.
 */
SHEN_PUBLIC_API void SelectCameraByDeviceId(std::string device_id, std::optional<bool> facing_user = std::nullopt);

/**
 * Sets the custom color theme of the SDK.
 * @param theme The custom color theme to set.
 */
SHEN_PUBLIC_API void SetCustomColorTheme(custom_color_theme theme);

/**
 * Sets whether the user interface should be shown.
 * @param show True if the user interface should be shown, false otherwise.
 */
SHEN_PUBLIC_API void SetShowUserInterface(bool show);

/**
 * Gets whether the user interface should be shown.
 * @return True if the user interface should be shown, false otherwise.
 */
SHEN_PUBLIC_API bool GetShowUserInterface();

/**
 * Sets whether the face positioning interface should be shown.
 * @param show True if the face positioning interface should be shown, false otherwise.
 */
SHEN_PUBLIC_API void SetShowFacePositioningOverlay(bool show);

/**
 * Gets whether the face positioning interface should be shown.
 * @return True if the face positioning interface should be shown, false otherwise.
 */
SHEN_PUBLIC_API bool GetShowFacePositioningOverlay();

/**
 * Sets whether the visual warnings should be shown.
 * @param show True if the visual warnings should be shown, false otherwise.
 */
SHEN_PUBLIC_API void SetShowVisualWarnings(bool show);

/**
 * Gets whether the visual warnings should be shown.
 * @return True if the visual warnings should be shown, false otherwise.
 */
SHEN_PUBLIC_API bool GetShowVisualWarnings();

/**
 * Sets whether the camera swap button should be shown.
 * @param enable True if the camera swap button should be shown, false otherwise.
 */
SHEN_PUBLIC_API void SetEnableCameraSwap(bool enable);

/**
 * Gets whether the camera swap button should be shown.
 * @return True if the camera swap button should be shown, false otherwise.
 */
SHEN_PUBLIC_API bool GetEnableCameraSwap();

/**
 * Sets whether the face mask should be shown.
 * @param show True if the face mask should be shown, false otherwise.
 */
SHEN_PUBLIC_API void SetShowFaceMask(bool show);

/**
 * Gets whether the face mask should be shown.
 * @return True if the face mask should be shown, false otherwise.
 */
SHEN_PUBLIC_API bool GetShowFaceMask();

/**
 * Sets whether the blood flow visualization should be shown.
 * @param show True if the blood flow should be shown, false otherwise.
 */
SHEN_PUBLIC_API void SetShowBloodFlow(bool show);

/**
 * Gets whether the blood flow visualization should be shown.
 * @return True if the blood flow should be shown, false otherwise.
 */
SHEN_PUBLIC_API bool GetShowBloodFlow();

/**
 * Sets whether it should be possible to start another measurement after the measurement has succeeded.
 * @param show True if it should be possible to start another measurement after the measurement has succeeded, false
 */
SHEN_PUBLIC_API void SetEnableStartAfterSuccess(bool show);

/**
 * Gets whether it should be possible to start another measurement after the measurement has succeeded.
 * @return True if it should be possible to start another measurement after the measurement has succeeded, false
 * otherwise.
 */
SHEN_PUBLIC_API bool GetEnableStartAfterSuccess();

/**
 * Face states for the SDK.
 */
enum class FaceState { Ok = 0, TooFar, TooClose, NotCentered, NotVisible, Unknown };

/**
 * Gets the current face state.
 * @return The current face state.
 */
SHEN_PUBLIC_API FaceState GetFaceState();

struct NormalizedFaceBbox {
  float x;
  float y;
  float width;
  float height;
};

/**
 * Gets the current face bounding box.
 * @return The current face bounding box.
 */
SHEN_PUBLIC_API std::optional<NormalizedFaceBbox> GetNormalizedFaceBbox();

enum class MeasurementState {
  NotStarted = 0,                  // Measurement has not started yet
  WaitingForFace,                  // Waiting for face to be properly positioned in the frame
  RunningSignalShort,              // Measurement started: Signal is too short for any conclusions
  RunningSignalGood,               // Measurement proceeding: Signal quality is good
  RunningSignalBad,                // Measurement stalled due to poor signal quality
  RunningSignalBadDeviceUnstable,  // Measurement stalled due to poor signal quality (because of unstable device)
  Finished,                        // Measurement has finished successfully
  Failed,                          // Measurement has failed
};

/**
 * Gets the current measurement state.
 * @return The current measurement state.
 */
SHEN_PUBLIC_API MeasurementState GetMeasurementState();

/**
 * Gets the current measurement progress percentage.
 * @return The current measurement progress percentage.
 */
SHEN_PUBLIC_API float GetMeasurementProgressPercentage();

/**
 * Gets the current heart rate based on the last 10 seconds of signal
 * @return The current heart rate based on the last 10 seconds of signal
 */
SHEN_PUBLIC_API std::optional<int> GetHeartRate10s();

/**
 * Gets the current heart rate based on the last 4 seconds of signal
 * @return The current heart rate based on the last 4 seconds of signal
 */
SHEN_PUBLIC_API std::optional<int> GetHeartRate4s();

struct heartbeat {
  double start_location_sec;  // exact start location in seconds
  double end_location_sec;    // exact end location in seconds
  double duration_ms;         // heartbeat duration, rounded to 1 ms
};

struct measurement_results {
  double heart_rate_bpm;                                // Heart rate, rounded to 1 BPM
  std::optional<double> hrv_sdnn_ms;                    // Heart rate variability, SDNN metric, rounded to 1 ms
  std::optional<double> hrv_lnrmssd_ms;                 // Heart rate variability, lnRMSSD metric, rounded to 0.1 ms
  std::optional<double> stress_index;                   // Cardiac Stress, rounded to 0.1
  std::optional<double> breathing_rate_bpm;             // Breathing rate, rounded to 1 BPM
  std::optional<double> systolic_blood_pressure_mmhg;   // Systolic blood pressure, rounded to 1 mmHg
  std::optional<double> diastolic_blood_pressure_mmhg;  // Diastolic blood pressure, rounded to 1 mmHg
  std::vector<heartbeat> heartbeats;                    // Heartbeat locations
  double average_signal_quality;                        // Average signal quality metric value
};

/**
 * Gets the realtime heartbeat metrics based on the last `period_sec` seconds of signal
 * @param period_sec The duration in seconds of the period of interest
 * @return The realtime heartbeat metrics based on the last `period_sec` seconds of signal
 */
SHEN_PUBLIC_API std::optional<measurement_results> GetRealtimeMetrics(float period_sec);

/**
 * Gets the result of the latest measurement.
 * @return The current measurement results.
 */
SHEN_PUBLIC_API std::optional<measurement_results> GetMeasurementResults();

struct momentary_hr_value {
  double timestamp_sec;  // exact timestamp in seconds
  int hr_bpm;            // Heart rate, rounded to 1 BPM
};

/**
 * Gets the heart rate history using a 10 second window.
 * @param max_time The maximum time to return values for. If not specified, all values are returned.
 * @return The heart rate history.
 */
SHEN_PUBLIC_API std::vector<momentary_hr_value> GetHeartRateHistory10s(std::optional<double> max_time = std::nullopt);

/**
 * Gets the heart rate history using a 4 second window.
 * @param max_time The maximum time to return values for. If not specified, all values are returned.
 * @return The heart rate history.
 */
SHEN_PUBLIC_API std::vector<momentary_hr_value> GetHeartRateHistory4s(std::optional<double> max_time = std::nullopt);

/**
 * Gets heartbeats detected in realtime.
 * @param max_time The maximum time to return values for. If not specified, all values are returned.
 * @return The heartbeats detected in realtime.
 */
SHEN_PUBLIC_API std::vector<heartbeat> GetRealtimeHeartbeats(std::optional<double> max_time = std::nullopt);

/**
 * Sets whether the SDK should record the measurement and send it to MX Labs.
 * @param enabled True if the SDK should record the measurement, false otherwise.
 */
SHEN_PUBLIC_API void SetRecordingEnabled(bool enabled);

/**
 * Gets whether the SDK is recording the measurement and sending it to MX Labs.
 * @return True if the SDK is recording the measurement, false otherwise.
 */
SHEN_PUBLIC_API bool GetRecordingEnabled();

/**
 * Gets the total number of seconds of bad signal since tracking started.
 * @return The total number of seconds of bad signal since tracking started.
 */
SHEN_PUBLIC_API float GetTotalBadSignalSeconds();

/**
 * Gets the current value of the signal quality metric.
 * Higher values indicate better signal quality.
 */
SHEN_PUBLIC_API float GetCurrentSignalQualityMetric();

/**
 * Gets a small PNG image representing the map of signal quality across the face.
 * @return A small PNG image representing the map of signal quality across the face
 * @note Will return an empty vector if the measurement hasn't finished yet
 */
SHEN_PUBLIC_API std::vector<uint8_t> GetSignalQualityMapPng();

/**
 * Gets a small PNG image representing the average analyzed texture of the face.
 * @return A small PNG image representing the average analyzed texture of the face
 * @note Will return an empty vector if the measurement hasn't finished yet
 */
SHEN_PUBLIC_API std::vector<uint8_t> GetFaceTexturePng();

/**
 * Gets the full PPG signal computed as part of the measurement.
 * @return The full PPG signal computed as part of the measurement
 * @note Will return an empty vector if the measurement hasn't finished yet
 */
SHEN_PUBLIC_API std::vector<float> GetFullPPGSignal();

/**
 * Gets the Shen Trace ID of the current SDK session.
 * @return The Trace ID of the current SDK session.
 * @note Will return an empty string if the SDK hasn't been initialized yet
 */
SHEN_PUBLIC_API std::string GetTraceID();

/**
 * Sets the language of the SDK.
 * @param language The language to set.
 */
SHEN_PUBLIC_API void SetLanguage(std::string language);

}  // namespace shen