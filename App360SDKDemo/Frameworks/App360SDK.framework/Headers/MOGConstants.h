//
//  Global.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/17/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MOGSession;
@class MOGScopedUser;

///--------------------------------------
/// @name Logging Levels
///--------------------------------------

/*!
 `MOGLogLevel` enum specifies different levels of logging that could be used to limit or display more messages in logs.
 
 @see [App360SDK setLogLevel:]
 @see [App360SDK logLevel]
 */
typedef NS_ENUM(uint8_t, MOGLogLevel) {
    /*!
     Log level that disables all logging.
     */
    MOGLogLevelNone = 0,
    /*!
     Log level that if set is going to output error messages to the log.
     */
    MOGLogLevelError = 1,
    /*!
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     */
    MOGLogLevelWarning = 2,
    /*!
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     - Informational messages
     */
    MOGLogLevelInfo = 3,
    /*!
     Log level that if set is going to output the following messages to log:
     - Errors
     - Warnings
     - Informational messages
     - Debug messages
     */
    MOGLogLevelDebug = 4
};

///--------------------------------------
/// @name Errors
///--------------------------------------

extern NSString *const MOGErrorDomain;

/*! @abstract 1: Internal server error. No information available. */
extern NSInteger const kMOGErrorInternalServer;

/*! @abstract 100: The connection to the App360 SDK servers failed. */
extern NSInteger const kMOGErrorConnectionFailed;

/*! @abstract 101: Parsing session token error. */
extern NSInteger const kMOGErrorTokenParsingError;

/*! @abstract 102: Authenticate with App360 SDK server error because of app ID or app secret is invalid. */
extern NSInteger const kMOGErrorAppInfoInvalid;

/*! @abstract 103: Session ID is invalid. */
extern NSInteger const kMOGErrorSessionIDInvalid;

/*! @abstract 104: Scope ID is invalid. */
extern NSInteger const kMOGErrorScopeIDInvalid;

/*! @abstract 105: Parsing user info error. */
extern NSInteger const kMOGErrorUserParsingError;

/*! @abstract 106: User info is invalid. */
extern NSInteger const kMOGErrorUserInfoInvalid;

/*! @abstract 114: UID is invalid. */
extern NSInteger const kMOGErrorUIDInvalid;

///--------------------------------------
/// @name Exception
///--------------------------------------

/*! Exception because of invalid application id. */
extern NSString *const kMOGExceptionApplicationIdIsInvalid;

/*! Exception because of invalid client key. */
extern NSString *const kMOGExceptionClientKeyIsInvalid;

/*! Exception because of invalid channel value. */
extern NSString *const kMOGExceptionChannelIsInvalid;

/*! Exception because of missing channel file. */
extern NSString *const kMOGExceptionMissingChannelFile;

///--------------------------------------
/// @name OpenID Service Name
///--------------------------------------

/*! @abstract facebook. */
extern NSString *const kMOGServiceNameFacebook;

/*! @abstract google. */
extern NSString *const kMOGServiceNameGoogle;

/*! @abstract app360. */
extern NSString *const kMOGServiceNameApp360;

///--------------------------------------
/// @name Blocks
///--------------------------------------

/*! @abstract Boolean block. Return result is success or not. If not, return with error object. */
typedef void (^MOGBooleanResultBlock)(BOOL succeeded, NSError *error);

/*! @abstract Session block. Return session if success. If not, return with error */
typedef void (^MOGSessionResultBlock)(MOGSession *session, NSError *error);

/*! @abstract User block. Return user if success. If not, return with error */
typedef void (^MOGUserResultBlock)(MOGScopedUser *user, NSError *error);

/*! @abstract NSURL block. Return url if success. If not,return with error */
typedef void (^MOGURLResultBlock)(NSURL *url, NSError *error);

///--------------------------------------
/// @name Deprecated Macros
///--------------------------------------

#ifndef APP360SDK_DEPRECATED
    #ifdef __deprecated_msg
        #define APP360SDK_DEPRECATED(_MSG) __deprecated_msg(_MSG)
    #else
        #ifdef __deprecated
            #define APP360SDK_DEPRECATED(_MSG) __attribute__((deprecated))
        #else
            #define APP360SDK_DEPRECATED(_MSG)
        #endif
    #endif
#endif


