//
//  MCenterUtility.h
//  MCenter
//
//  Created by Tran Manh Tuan on 7/21/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

#pragma mark - NSData + Base64

@interface NSData (Base64)

- (NSString *)base64EncodedString;

+ (NSData *)dataWithBase64EncodedString:(NSString *)encodedString;

@end

#pragma mark - NSString + URLEncodeDecode

@interface NSString (URLEncodeDecode)

- (NSString *)URLEncode;

- (NSString *)URLDecode;

@end

#pragma mark - NSDictionary + JSON

@interface NSDictionary (JSON)

- (NSString *)jsonStringWithPrettyPrint:(BOOL)prettyPrint;

@end

#pragma mark - MCenter Utils

@interface MOGUtils : NSObject

#pragma mark - Get device info

+ (NSString *)getDeviceModel;

+ (NSString *)getDeviceName;

+ (NSString *)getDeviceCarrierName;

+ (NSString *)getDeviceCountryCode;

+ (NSArray *)getDeviceResolution;

+ (NSString *)getDeviceOSVersion;

+ (NSString *)getDeviceLanguage;

+ (NSString *)getDeviceId;

+ (NSString *)getDeviceTimeZone;

+ (NSString *)getDeviceBrand;

+ (CGRect)screenBound;

#pragma mark - Get app info

+ (NSString *)getAppVersion;

+ (NSString *)getAppBundleIdentitier;

+ (NSString *)getAppName;

#pragma mark - Other

+ (void)showAlertWithTitle:(NSString *)title andMessage:(NSString *)message;

+ (void)showAlertWithMessage:(NSString *)message;

+ (NSNumberFormatter *)numberFormatter;

+ (NSString *)stringFromAmount:(MOGSMSAmount)amount;

+ (MOGSMSAmount)amountFromString:(NSString *)amountString;

@end
