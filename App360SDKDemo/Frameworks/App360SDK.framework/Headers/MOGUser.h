//
//  ScopedUser.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/9/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MOGConstants.h"

@interface MOGUser : NSObject

/*!
 @abstract Random UUID with lowercase hexadecimal digits. app-scope id
 */
@property (nonatomic, strong, readonly) NSString *scopedId;

/*!
 @abstract Creation time in UTC, ISO 8601-format
 */
@property (nonatomic, strong, readonly) NSString *createTime;

/*!
 @abstract Modification time in UTC, ISO 8601-format
 */
@property (nonatomic, strong, readonly) NSString *modificationTime;

/*!
 @abstract Additional information of user defined by application
 */
@property (nonatomic, strong, readonly) NSDictionary *userInfo;

/*!
 @abstract Channel that user subcribe
 */
@property (nonatomic, strong, readonly) NSString *channel;

/*!
 @abstract Sub channel that user subcribe
 */
@property (nonatomic, strong, readonly) NSString *subChannel;

/*!
 *  Current user object
 *
 *  @return ScopedUser object
 */
+ (instancetype)currentUser;

//FIXME: Remove it

/*!
 *  Set ScopedUser object as current user
 *
 *  @param user ScopedUser object want to set as current user
 */
+ (void)setCurrentUser:(MOGUser *)user;

/*!
 @abstract Returns the value associated with a given key.
 
 @param key The key for which to return the corresponding value.
 */
- (id)objectForKey:(NSString *)key;

/*!
 @abstract Sets the object associated with a given key.
 
 @param object  The object.
 @param key     The key.
 */
- (void)setObject:(id)object forKey:(NSString *)key;

/*!
 @abstract Returns the value associated with a given key.
 
 @discussion This method enables usage of literal syntax on `PFObject`.
 E.g. `NSString *value = object[@"key"];`
 
 @see objectForKey:
 
 @param key The key for which to return the corresponding value.
 */
- (id)objectForKeyedSubscript:(NSString *)key;

/*!
 @abstract Returns the value associated with a given key.
 
 @discussion This method enables usage of literal syntax on `PFObject`.
 E.g. `object[@"key"] = @"value";`
 
 @see setObject:forKey:
 
 @param object The object.
 @param key The key.
 */
- (void)setObject:(id)object forKeyedSubscript:(NSString *)key;

/*!
 @abstract Removes all occurrences of an object from the array associated with a given key.
 
 @param object The object to remove.
 @param key The key.
 */
- (void)removeObject:(id)object forKey:(NSString *)key;

/*!
 @abstract Saves the `MOGUser` *asynchronously* and executes the given callback block.
 
 @param block The block to execute.
 It should have the following argument signature: `^(BOOL succeeded, NSError *error)`.
 */
- (void)saveInBackgroundWithBlock:(MOGBooleanResultBlock)block;

/**
 @abstract Makes an *asynchronous* request to *link* a user with specified facebook access token.
 
 @param facebookToken Facebook access token
 @param block         The block to execute
 It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
- (void)linkWithFacebookToken:(NSString *)facebookToken block:(MOGSessionResultBlock)block;

/**
 @abstract Makes an *asynchronous* request to *link* a user with specified google access token.
 
 @param googleToken Google access token
 @param block       The block to execute
 It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
- (void)linkWithGoogleToken:(NSString *)googleToken block:(MOGSessionResultBlock)block;

/*!
 @abstract Makes an *asynchronous* request to *unlink* a user with Facebook.
 
 @param block       The block to execute
 It should have the following argument signature: `^(BOOL succeeded, NSError *error)`.
 */
- (void)unlinkFacebookInBackgroundWithBlock:(MOGBooleanResultBlock)block;

/*!
 @abstract Makes an *asynchronous* request to *unlink* a user with Google.
 
 @param block       The block to execute
 It should have the following argument signature: `^(BOOL succeeded, NSError *error)`.
 */
- (void)unlinkGoogleInBackgroundWithBlock:(MOGBooleanResultBlock)block;

/*!
 @abstract Make an *asynchronous* request to get info of current user
 
 @param block       The block to execute
 It should have the following argument signature: `^(MOGUser *user, NSError *error)`.
 */
+ (void)requestForMeWithBlock:(MOGUserResultBlock)block;

/*!
 @abstract Make an *asynchronous* request to get info of user with specific scoped_id
 
 @param scopedId    The id of scoped user that want to get info
 @param block       The block to execute
 It should have the following argument signature: `^(MOGUser *user, NSError *error)`.
 */
+ (void)requestForScopedId:(NSString *)scopedId block:(MOGUserResultBlock)block;

/*!
 @abstract Makes an *asynchronous* request to update info of current user.
 
 @param info    The new information that want to update to current user
 @param block   The block to execute
 It should have the following argument signature: `^(BOOL succeeded, NSError *error)`.
 */
- (void)updateForMeWithInfo:(NSDictionary *)info block:(MOGBooleanResultBlock)block;

@end
