//
//  AppScopeID.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/1/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

#import "MOGScopedUser.h"
#import "MOGSession.h"
#import "MOGSessionManager.h"
#import "MOGConstants.h"
#import "MOGUtils.h"

@interface App360SDK : NSObject

/**
 *  @abstract Initialize SDK. This function does not open any session at all.
 *
 *  @param applicationId Id of the app that the token is issued for
 *  @param clientKey     secret key of the app that the token is issued for
 */
+ (void)initializeWithApplicationId:(NSString *)applicationId
                          clientKey:(NSString *)clientKey;

/*!
 * @abstract Initialize SDK. This method will open active session with info you provide
 *
 * @param applicationId   ID of the app that the token is issued for
 * @param clientKey       secret key of the app that the token is issued for
 * @param block           The block to execute
 * It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 *
 *  @deprecated Please use +initializeWithApplicationId:clientKey: instead.
 */
+ (void)initializeWithApplicationId:(NSString *)applicationId
                          clientKey:(NSString *)clientKey
                              block:(MOGSessionResultBlock)block APP360SDK_DEPRECATED("Please use +initializeWithApplicationId:clientKey: instead.");

/*!
 @abstract The current application id that was used to configure App360 SDK framework.
 */
+ (NSString *)getApplicationId;

/*!
 @abstract The current application secret that was used to configure App360 SDK framework.
 */
+ (NSString *)getClientKey;

/*!
 @abstract The current application channel that was used to configure App360 SDK framework.
 */
+ (NSString *)getChannel;

/*!
 @abstract The current application sub channel that was used to configure App360 SDK framework.
 */
+ (NSString *)getSubChannel;

/*!
 @abstract Get SDK version
 */
+ (NSString *)getSDKVersion;

/**
 *  Get update URL for app
 *
 *  @param block The block to execute
 *  It should have the following argument signature: `^(NSURL *url, NSError *error)`.
 */
+ (void)getUpdateURLWithBlock:(MOGURLResultBlock)block;

@end

#define APP360_SDK_VERSION_STRING @"1.5.0"