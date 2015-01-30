//
//  Session.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/10/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MOGSession : NSObject

/**
*  Session id
*/
@property (nonatomic, strong, readonly) NSString *sessionID;

/**
 *  Expiration time in UTC, ISO 8601-format
 */
@property (nonatomic, strong, readonly) NSString *expirationTime;

/**
 *  Creation time in UTC, ISO 8601-format
 */
@property (nonatomic, strong, readonly) NSString *creationTime;

/**
 *  ID of the app that the token is issued for
 */
@property (nonatomic, strong, readonly) NSString *clientID;

/**
 *  App-scoped ID of the user that issued the token
 */
@property (nonatomic, strong, readonly) NSString *userID;

/**
 *  BOOL: whether the token is still valid
 */
@property (nonatomic, assign, readonly) BOOL isValid;

/**
 *  Init method using JSON dictionary
 *
 *  @param JSON input dictionary
 *
 *  @return session with value from JSON
 */
- (instancetype)initWithJSON:(NSDictionary *)JSON;

/**
 *  Get active session
 *
 *  @return current active session
 */
+ (instancetype)activeSession;

/**
 *  Set session as current active session
 *
 *  @param session the session want to set to active session
 */
+ (void)setActiveSession:(MOGSession *)session;

/**
 *  Before the application could use any API requiring user context, it must create a user context by creating an app-scoped session. 
 *  When the session is created, it’s the application’s responsibility to cache the session token returned together with the app-scoped ID. 
 *  There’s no way to re-retrieve this token, other than creating a new token altogether.
 *
 *  @param scopeID   random UUID with lowercase hexadecimal digits. Optional
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
 *  To retrieve session token information
 *
 *  @param sessionId Id of the session want to get info
 *  @param block     The block to execute
 *  It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
+ (void)getSessionWithId:(NSString *)sessionId
                   block:(MOGSessionResultBlock)block;

@end
