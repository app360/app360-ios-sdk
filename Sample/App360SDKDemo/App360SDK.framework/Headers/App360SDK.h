//
//  AppScopeID.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/1/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>

//! Project version number for AppScopeID.
FOUNDATION_EXPORT double AppScopeIDVersionNumber;

//! Project version string for AppScopeID.
FOUNDATION_EXPORT const unsigned char AppScopeIDVersionString[];

#import "MOGUser.h"
#import "MOGSession.h"
#import "MOGConstants.h"
#import "MOGPaymentSDK.h"

@interface App360SDK : NSObject

/*!
 @abstract Initialize SDK. This method will open active session with info you provide
 
 @param applicationId   ID of the app that the token is issued for
 @param clientKey       secret key of the app that the token is issued for
 @param scopedId        default scoped user id you want to login, eg. device UUID
 @param block           The block to execute
 It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
*/
+ (void)initializeWithApplicationId:(NSString *)applicationId
                          clientKey:(NSString *)clientKey
                              block:(MOGSessionResultBlock)block;

/*!
 @abstract Present login dialog.
 */
+ (void)showLoginViewController;

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

@end
