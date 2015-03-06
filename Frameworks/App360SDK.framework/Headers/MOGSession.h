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

@end
