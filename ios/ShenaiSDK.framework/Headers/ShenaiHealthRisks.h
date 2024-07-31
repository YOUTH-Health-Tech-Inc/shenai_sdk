#import <Foundation/Foundation.h>

typedef NS_ENUM(NSInteger, Gender) { GenderMale, GenderFemale, GenderOther };

typedef NS_ENUM(NSInteger, Race) { RaceWhite, RaceAfricanAmerican, RaceOther };

__attribute__((visibility("default")))
@interface RisksFactors : NSObject

@property(nonatomic, strong, nullable) NSNumber *age;
@property(nonatomic, strong, nullable) NSNumber *cholesterol;
@property(nonatomic, strong, nullable) NSNumber *cholesterolHDL;
@property(nonatomic, strong, nullable) NSNumber *sbp;
@property(nonatomic, strong, nullable) NSNumber *isSmoker;
@property(nonatomic, strong, nullable) NSNumber *hypertensionTreatment;
@property(nonatomic, strong, nullable) NSNumber *hasDiabetes;
@property(nonatomic, strong, nullable) NSNumber *bodyHeight;
@property(nonatomic, strong, nullable) NSNumber *bodyWeight;
@property(nonatomic) Gender gender;
@property(nonatomic, strong, nullable) NSString *country;
@property(nonatomic) Race race;

- (nonnull instancetype)init;

- (nonnull instancetype)initWithAge:(nullable NSNumber *)age
                        cholesterol:(nullable NSNumber *)cholesterol
                     cholesterolHDL:(nullable NSNumber *)cholesterolHDL
                                sbp:(nullable NSNumber *)sbp
                           isSmoker:(nullable NSNumber *)isSmoker
              hypertensionTreatment:(nullable NSNumber *)hypertensionTreatment
                        hasDiabetes:(nullable NSNumber *)hasDiabetes
                         bodyHeight:(nullable NSNumber *)bodyHeight
                         bodyWeight:(nullable NSNumber *)bodyWeight
                             gender:(Gender)gender
                            country:(nullable NSString *)country
                               race:(Race)race;
@end

@interface HardAndFatalEventsRisks : NSObject
@property(nonatomic, strong, nullable) NSNumber *coronaryDeathEventRisk;
@property(nonatomic, strong, nullable) NSNumber *fatalStrokeEventRisk;
@property(nonatomic, strong, nullable) NSNumber *totalCvMortalityRisk;
@property(nonatomic, strong, nullable) NSNumber *hardCvEventRisk;
@end

@interface CVDiseasesRisks : NSObject
@property(nonatomic, strong, nullable) NSNumber *overallRisk;
@property(nonatomic, strong, nullable) NSNumber *coronaryHeartDiseaseRisk;
@property(nonatomic, strong, nullable) NSNumber *strokeRisk;
@property(nonatomic, strong, nullable) NSNumber *heartFailureRisk;
@property(nonatomic, strong, nullable) NSNumber *peripheralVascularDiseaseRisk;
@end

@interface RisksFactorsScores : NSObject
@property(nonatomic, strong, nullable) NSNumber *ageScore;
@property(nonatomic, strong, nullable) NSNumber *sbpScore;
@property(nonatomic, strong, nullable) NSNumber *smokingScore;
@property(nonatomic, strong, nullable) NSNumber *diabetesScore;
@property(nonatomic, strong, nullable) NSNumber *bmiScore;
@property(nonatomic, strong, nullable) NSNumber *cholesterolScore;
@property(nonatomic, strong, nullable) NSNumber *cholesterolHdlScore;
@property(nonatomic, strong, nullable) NSNumber *totalScore;
@end

@interface HealthRisks : NSObject
@property(nonatomic, strong, nonnull) HardAndFatalEventsRisks *hardAndFatalEvents;
@property(nonatomic, strong, nonnull) CVDiseasesRisks *cvDiseases;
@property(nonatomic, strong, nullable) NSNumber *vascularAge;
@property(nonatomic, strong, nonnull) RisksFactorsScores *scores;
@end

__attribute__((visibility("default")))
@interface ShenaiHealthRisks : NSObject

+ (nonnull HealthRisks *)computeHealthRisks:(nonnull RisksFactors *)risksFactors;
+ (nonnull HealthRisks *)getMaximalRisks:(nonnull RisksFactors *)risksFactors;
+ (nonnull HealthRisks *)getMinimalRisks:(nonnull RisksFactors *)risksFactors;

@end
