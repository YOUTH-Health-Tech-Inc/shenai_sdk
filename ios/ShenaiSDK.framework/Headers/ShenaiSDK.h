#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, InitializationResult) {
  InitializationResultSuccess = 0,
  InitializationResultFailureInvalidApiKey,
  InitializationResultFailureConnectionError,
  InitializationResultFailureInternalError,
};

typedef NS_ENUM(NSInteger, OperatingMode) {
  OperatingModePositioning = 0,
  OperatingModeMeasure = 1,
  OperatingModeSystemOverloaded = 2,
};

typedef NS_ENUM(NSInteger, PrecisionMode) {
  PrecisionModeStrict = 0,
  PrecisionModeRelaxed = 1,
};

typedef NS_ENUM(NSInteger, MeasurementPreset) {
  MeasurementPresetOneMinuteHrHrvBr = 0,
  MeasurementPresetOneMinuteBetaMetrics = 1,
  MeasurementPresetInfiniteHr = 2,
  MeasurementPresetInfiniteMetrics = 3,
  MeasurementPresetFourtyFiveSecondsUnvalidated = 4,
  MeasurementPresetThirtySecondsUnvalidated = 5,
};

typedef NS_ENUM(NSInteger, CameraMode) {
  CameraModeOff = 0,
  CameraModeFacingUser = 1,
  CameraModeFacingEnvironment = 2,
};

typedef NS_ENUM(NSInteger, OnboardingMode) {
  OnboardingModeHidden = 0,
  OnboardingModeShowOnce = 1,
  OnboardingModeShowAlways = 2,
};

typedef NS_ENUM(NSInteger, FaceState) {
  FaceStateOk = 0,
  FaceStateTooFar = 1,
  FaceStateTooClose = 2,
  FaceStateNotCentered = 3,
  FaceStateNotVisible = 4,
  FaceStateUnknown = 5,
};

typedef NS_ENUM(NSInteger, MeasurementState) {
  MeasurementStateNotStarted = 0,
  MeasurementStateWaitingForFace = 1,
  MeasurementStateRunningSignalShort = 2,
  MeasurementStateRunningSignalGood = 3,
  MeasurementStateRunningSignalBad = 4,
  MeasurementStateRunningSignalBadDeviceUnstable = 5,
  MeasurementStateFinished = 6,
  MeasurementStateFailed = 7,
};

__attribute__((visibility("default")))
@interface InitializationSettings : NSObject

@property(nonatomic) PrecisionMode precisionMode;
@property(nonatomic) OperatingMode operatingMode;
@property(nonatomic) MeasurementPreset measurementPreset;
@property(nonatomic) CameraMode cameraMode;
@property(nonatomic) OnboardingMode onboardingMode;

@property(nonatomic) BOOL showUserInterface;
@property(nonatomic) BOOL showFacePositioningOverlay;
@property(nonatomic) BOOL showVisualWarnings;
@property(nonatomic) BOOL enableCameraSwap;
@property(nonatomic) BOOL showFaceMask;
@property(nonatomic) BOOL showBloodFlow;
@property(nonatomic) BOOL hideShenaiLogo;

- (nonnull instancetype)init;

@end

__attribute__((visibility("default")))
@interface CustomMeasurementConfig : NSObject
@property(nonatomic, nullable, strong) NSNumber *durationSeconds;
@property(nonatomic) BOOL infiniteMeasurement;
@property(nonatomic) BOOL showHeartRate;
@property(nonatomic) BOOL showHrvSdnn;
@property(nonatomic) BOOL showBreathingRate;
@property(nonatomic) BOOL showSystolicBloodPressure;
@property(nonatomic) BOOL showDiastolicBloodPressure;
@property(nonatomic) BOOL showCardiacStress;
@property(nonatomic, nullable, strong) NSNumber *realtimeHrPeriodSeconds;
@property(nonatomic, nullable, strong) NSNumber *realtimeHrvPeriodSeconds;
@property(nonatomic, nullable, strong) NSNumber *realtimeCardiacStressPeriodSeconds;

- (nonnull instancetype)init;
@end

__attribute__((visibility("default")))
@interface CustomColorTheme : NSObject
@property(nonatomic, copy, nonnull) NSString *themeColor;
@property(nonatomic, copy, nonnull) NSString *textColor;
@property(nonatomic, copy, nonnull) NSString *backgroundColor;
@property(nonatomic, copy, nonnull) NSString *tileColor;
@end

__attribute__((visibility("default")))
@interface NormalizedFaceBbox : NSObject
@property(nonatomic, assign) float x;
@property(nonatomic, assign) float y;
@property(nonatomic, assign) float width;
@property(nonatomic, assign) float height;
@end

__attribute__((visibility("default")))
@interface Heartbeat : NSObject
@property(nonatomic, assign) double startLocationSec;
@property(nonatomic, assign) double endLocationSec;
@property(nonatomic, assign) double durationMs;
@end

__attribute__((visibility("default")))
@interface MeasurementResults : NSObject
@property(nonatomic, assign) double heartRateBpm;
@property(nonatomic, nullable, strong) NSNumber *hrvSdnnMs;
@property(nonatomic, nullable, strong) NSNumber *hrvLnrmssdMs;
@property(nonatomic, nullable, strong) NSNumber *stressIndex;
@property(nonatomic, nullable, strong) NSNumber *breathingRateBpm;
@property(nonatomic, nullable, strong) NSNumber *systolicBloodPressureMmhg;
@property(nonatomic, nullable, strong) NSNumber *diastolicBloodPressureMmhg;
@property(nonatomic, nonnull, strong) NSArray<Heartbeat *> *heartbeats;
@property(nonatomic, assign) double averageSignalQuality;
@end

__attribute__((visibility("default")))
@interface ShenaiSDK : NSObject

+ (InitializationResult)initialize:(nonnull NSString *)apiKey
                            userID:(nullable NSString *)userID
                          settings:(nullable InitializationSettings *)settings;

+ (BOOL)isInitialized;
+ (void)deinitialize;
+ (void)setOperatingMode:(OperatingMode)mode;
+ (OperatingMode)getOperatingMode;
+ (void)setPrecisionMode:(PrecisionMode)mode;
+ (PrecisionMode)getPrecisionMode;
+ (void)setMeasurementPreset:(MeasurementPreset)preset;
+ (MeasurementPreset)getMeasurementPreset;
+ (void)setCameraMode:(CameraMode)mode;
+ (CameraMode)getCameraMode;

+ (void)setShowUserInterface:(BOOL)show;
+ (BOOL)getShowUserInterface;
+ (void)setShowFacePositioningOverlay:(BOOL)show;
+ (BOOL)getShowFacePositioningOverlay;
+ (void)setShowVisualWarnings:(BOOL)show;
+ (BOOL)getShowVisualWarnings;
+ (void)setEnableCameraSwap:(BOOL)enable;
+ (BOOL)getEnableCameraSwap;
+ (void)setShowFaceMask:(BOOL)show;
+ (BOOL)getShowFaceMask;
+ (void)setShowBloodFlow:(BOOL)show;
+ (BOOL)getShowBloodFlow;
+ (void)setEnableStartAfterSuccess:(BOOL)show;
+ (BOOL)getEnableStartAfterSuccess;

+ (FaceState)getFaceState;
+ (nullable NormalizedFaceBbox *)getNormalizedFaceBbox;

+ (MeasurementState)getMeasurementState;

+ (float)getMeasurementProgressPercentage;

+ (nullable NSNumber *)getHeartRate10s;
+ (nullable NSNumber *)getHeartRate4s;

+ (nullable MeasurementResults *)getRealtimeMetrics:(double)period_sec;
+ (nullable MeasurementResults *)getMeasurementResults;

+ (nonnull NSArray<Heartbeat *> *)getRealtimeHeartbeats:(nullable NSNumber *)maxTime;

+ (void)setRecordingEnabled:(BOOL)enabled;
+ (BOOL)isRecordingEnabled;
+ (float)getTotalBadSignalSeconds;
+ (float)getCurrentSignalQualityMetric;

+ (nullable NSData *)getSignalQualityMapPng;
+ (nullable NSData *)getFaceTexturePng;

+ (nonnull NSArray<NSNumber *> *)getFullPPGSignal;

+ (void)setCustomMeasurementConfig:(nonnull CustomMeasurementConfig *)config;
+ (void)setCustomColorTheme:(nonnull CustomColorTheme *)theme;

+ (void)setLanguage:(nonnull NSString *)language;

@end