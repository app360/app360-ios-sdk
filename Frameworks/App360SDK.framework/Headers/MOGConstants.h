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
@class MOGM360User;
@class MOGSMSResponseObject;
@class MOGCardResponseObject;
@class MOGBankingResponseObject;
@class MOGPaymentResponseObject;

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

/*!
 `MOGSMSAmount` enum specifies different supported value of sms amount.
 */
typedef NS_OPTIONS(NSInteger, MOGSMSAmount) {
    /*!
     Amount with value 500 VND
     */
    MOGSMSAmount500   = 1 << 0,
    /*!
     Amount with value 1000 VND
     */
    MOGSMSAmount1000  = 1 << 1,
    /*!
     Amount with value 2000 VND
     */
    MOGSMSAmount2000  = 1 << 2,
    /*!
     Amount with value 3000 VND
     */
    MOGSMSAmount3000  = 1 << 3,
    /*!
     Amount with value 4000 VND
     */
    MOGSMSAmount4000  = 1 << 4,
    /*!
     Amount with value 5000 VND
     */
    MOGSMSAmount5000  = 1 << 5,
    /*!
     Amount with value 10000 VND
     */
    MOGSMSAmount10000 = 1 << 6,
    /*!
     Amount with value 15000 VND
     */
    MOGSMSAmount15000 = 1 << 7,
    /*!
     Amount that contains all values above
     */
    MOGSMSAmountAll   = MOGSMSAmount500   |
                        MOGSMSAmount1000  |
                        MOGSMSAmount2000  |
                        MOGSMSAmount3000  |
                        MOGSMSAmount4000  |
                        MOGSMSAmount5000  |
                        MOGSMSAmount10000 |
                        MOGSMSAmount15000
};

/*!
 `MOGVendor` enum specifies different supported vendor of card transaction.
 */
typedef NS_ENUM(uint8_t, MOGVendor) {
    /*!
     Vinaphone
     */
    MOGVendorVinaphone = 0,
    /*!
     Mobifone
     */
    MOGVendorMobifone = 1,
    /*!
     Viettel
     */
    MOGVendorViettel = 2
};

/*!
 `MOGTransactionStatus` enum specifies different status of transaction.
 */
typedef NS_ENUM(uint8_t, MOGTransactionStatus) {
    /*!
     The transaction received but has not processed
     */
    MOGTransactionStatusBegin = 0,
    /*!
     The transaction received and is being processed
     */
    MOGTransactionStatusPending = 1,
    /*!
     The transaction is processed completly
     */
    MOGTransactionStatusCompleted = 2,
    /*!
     The transaction is failed
     */
    MOGTransactionStatusFailed = 3,
    /*!
     The transaction status is undefine
     */
    MOGTransactionStatusUndefine = 4,
};

/*!
 `MOGTransactionType` enum specifies different type of transaction.
 */
typedef NS_ENUM(uint8_t, MOGTransactionType) {
    /*!
     Make transaction via SMS
     */
    MOGTransactionTypeSMS = 0,
    /*!
     Make transaction via phone card
     */
    MOGTransactionTypeCard = 1,
    /*!
     Make transaction via E-Banking
     */
    MOGTransactionTypeBank = 2
};

/*!
 `MOGAPICode` enum specifies status code of API response.
 */
typedef NS_ENUM(uint8_t, MOGAPICode) {
    /*!
     Make transaction via SMS
     */
    MOGAPICodeSuccess = 0,
    /*!
     Make transaction via phone card
     */
    MOGAPICodeError = 1
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

/*! @abstract 107: Vendor name is invalid. */
extern NSInteger const kMOGErrorVendorNameInvalid;

/*! @abstract 108: Amount value is invalid. */
extern NSInteger const kMOGErrorAmountInvalid;

/*! @abstract 109: Card transtion is failed. */
extern NSInteger const kMOGErrorCardChargingFailed;

/*! @abstract 110: User cancel send SMS dialog. */
extern NSInteger const kMOGErrorUserCancelSMSDialog;

/*! @abstract 111: Send SMS failed. */
extern NSInteger const kMOGErrorSendSMSFailed;

/*! @abstract 112: Get SMS syntax failed. */
extern NSInteger const kMOGErrorGetSMSSyntax;

/*! @abstract 113: Check transaction status failed. */
extern NSInteger const kMOGErrorCheckTransactionStatusFailed;

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

/*! @abstract App360 user block. Return App360 user if success. If not, return with error */
typedef void (^MOGM360UserResultBlock)(MOGM360User *user, NSError *error);

/*! @abstract SMS charging response block. Return SMS response if success. If not,return with error */
typedef void (^MOGSMSResponseBlock)(MOGSMSResponseObject *responseObject, NSError *error);

/*! @abstract Phone card charging response block. Return phone card response if success. If not,return with error */
typedef void (^MOGCardResponseBlock)(MOGCardResponseObject *responseObject, NSError *error);

/*! @abstract E-banking charging response block. Return e-banking response if success. If not,return with error */
typedef void (^MOGBankingResponseBlock)(MOGBankingResponseObject *responseObject, NSError *error);

/*! @abstract payment response block. Return payment response if success. If not,return with error */
typedef void (^MOGPaymentResponseBlock)(MOGPaymentResponseObject *responseObject, NSError *error);

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


