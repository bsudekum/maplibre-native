#import "NSDictionary+MLNAdditions.h"

#import "NSExpression+MLNPrivateAdditions.h"
#import "NSArray+MLNAdditions.h"

@implementation NSDictionary (MLNAdditions)

- (mbgl::PropertyMap)mgl_propertyMap {
    mbgl::PropertyMap propertyMap;
    for (NSString *key in self.allKeys) {
        if ([self[key] isKindOfClass:[NSDictionary class]]) {
            propertyMap[[key UTF8String]] = [self[key] mgl_propertyMap];
        } else if ([self[key] isKindOfClass:[NSArray class]]) {
            NSArray *array = self[key];
            propertyMap[[key UTF8String]] = [array mgl_vector];
        } else {
            NSExpression *expression = [NSExpression expressionForConstantValue:self[key]];
            propertyMap[[key UTF8String]] = expression.mgl_constantMBGLValue;
        }
    }
    return propertyMap;
}

@end
