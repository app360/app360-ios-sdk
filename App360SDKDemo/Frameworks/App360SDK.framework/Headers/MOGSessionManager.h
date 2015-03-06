//
//  MOGSessionManager.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 3/6/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MOGSession.h"

@interface MOGSessionManager : NSObject

/**
 *  Get active session
 *
 *  @return current active session
 */
+ (MOGSession *)getCurrentSession;

/**
 *  Before the application could use any API requiring user context, it must create a user context by creating an app-scoped session.
 *  When the session is created, it’s the application’s responsibility to cache the session token returned together with the app-scoped ID.
 *  There’s no way to re-retrieve this token, other than creating a new token altogether.
 *
 *  @param scopeId   random UUID with lowercase hexadecimal digits. Optional
 *  @param userInfo  additional key/value defined by application
 *  @param block     The block to execute
 *  It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
+ (void)openActiveSessionWithScopeId:(NSString *)scopeId
                            userInfo:(NSDictionary *)userInfo
                               block:(MOGSessionResultBlock)block;

/**
 *  Before the application could use any API requiring user context, it must create a user context by creating an app-scoped session.
 *  When the session is created, it’s the application’s responsibility to cache the session token returned together with the app-scoped ID.
 *  There’s no way to re-retrieve this token, other than creating a new token altogether.
 *
 *  @param serviceName  Name of OpenID service like facebook, app360, google
 *  @param token        Access token of service above
 *  @param block        The block to execute
 *  It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
+ (void)openActiveSessionWithService:(NSString *)serviceName
                               token:(NSString *)token
                               block:(MOGSessionResultBlock)block;

/**
 *  To open session with token information
 *
 *  @param sessionId Id of the session want to get info
 *  @param block     The block to execute
 *  It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
+ (void)openSessionWithId:(NSString *)sessionId
                    block:(MOGSessionResultBlock)block;

@end
