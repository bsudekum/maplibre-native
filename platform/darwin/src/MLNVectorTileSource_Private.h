#import "MLNVectorTileSource.h"

NS_ASSUME_NONNULL_BEGIN

@interface MLNVectorTileSource (Private)

@property (nonatomic, readonly, getter=isMapboxStreets) BOOL mapboxStreets;

+ (NSSet<NSString *> *)mapboxStreetsLanguages;

+ (nullable NSString *)preferredMapboxStreetsLanguage;
+ (nullable NSString *)preferredMapboxStreetsLanguageForPreferences:
    (NSArray<NSString *> *)preferencesArray;

@end

NS_ASSUME_NONNULL_END
