//
//  PaymentSDK.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/17/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MOGSMSItem.h"

#import "MOGPaymentResponseObject.h"
#import "MOGSMSResponseObject.h"
#import "MOGCardResponseObject.h"
#import "MOGBankingResponseObject.h"

@interface MOGPaymentSDK : NSObject

#pragma mark - SMS charging method

/**
 *  Get SMS syntax with given amount. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param amount                Available amount value. (required)
 *                               This param in NS_OPTIONS type, so you can add multi values and separate them with charactor '|'.
 *                               Eg: MOGSMSAmount500 | MOGSMSAmount4000
 *  @param payload               Custom payload string generate by applecation, wanna sent with transaction (optional)
 *  @param block                 The block to execute
 *  It should have the following argument signature: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 *
 *  @deprecated       Please use +requestSMSSyntaxWithAmount:vendor:payload:block: instead.
 */
+ (void)getSMSSyntaxWithSMSAmount:(MOGSMSAmount)amount
                          payload:(NSString *)payload
                            block:(MOGSMSResponseBlock)block APP360SDK_DEPRECATED("Please use +requestSMSSyntaxWithAmount:vendor:payload:block: instead.");

/**
 *  Send request to get sms syntax
 *
 *  @param amount  money in vietnam dong. Accept multiple values, separate by commas. For example: `@"500, 1000, 10000, 15000"` (required)
 *  @param vendor  Mobile network provider. Accepted value: vinaphone, mobifone, viettel (optional)
 *  @param payload Custom string generate by application to send with transaction. Common usecase of payload is sending gamer_id, server_id with transaction. (optional)
 *  @param block   The block to execute
 *  It should have the following argument signature: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)requestSMSSyntaxWithAmount:(NSString *)amount
                            vendor:(NSString *)vendor
                           payload:(NSString *)payload
                             block:(MOGSMSResponseBlock)block;

#pragma mark - Phone card charging method

/**
 *  Make transaction via phone card. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param vendor     Name of service provider. Supported values are vinaphone, mobifone, viettel (required)
 *  @param cardCode   PIN number of phone card (required)
 *  @param cardSerial Serial number (required)
 *  @param payload    Custom payload string generate by applecation, wanna sent with transaction (optional)
 *  @param block      The block to execute
 *  It should have the following argument signature: `^(MOGCardResponseObject *responseObject, NSError *error)`.
 *  
 *  @deprecated       Please use +makeCardTransactionWithVendor:cardCode:cardSerial:payload:block: instead.
 */
+ (void)makePhoneCardTransactionWithVendor:(MOGVendor)vendor
                                  cardCode:(NSString *)cardCode
                                cardSerial:(NSString *)cardSerial
                                   payload:(NSString *)payload
                                     block:(MOGCardResponseBlock)block APP360SDK_DEPRECATED("Please use +makeCardTransactionWithVendor:cardCode:cardSerial:payload:block: instead.");

/**
 *  Make transaction via phone/game card. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param vendor     card provider. Supported values are vinaphone, mobifone, viettel, gate, vcoin, zing, bit... (required)
 *  @param cardCode   PIN number of card (required)
 *  @param cardSerial Serial number (required)
 *  @param payload    Custom payload string generate by application, wanna sent with transaction (optional)
 *  @param block      The block to execute
 *  It should have the following argument signature: `^(MOGCardResponseObject *responseObject, NSError *error)`.
 */
+ (void)makeCardTransactionWithVendor:(NSString *)vendor
                             cardCode:(NSString *)cardCode
                           cardSerial:(NSString *)cardSerial
                              payload:(NSString *)payload
                                block:(MOGCardResponseBlock)block;

#pragma mark - Banking charging method

/**
 *  Make transaction via e-banking. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *  This method returns a URL, which use to charge for this transaction. User must make transaction via that URL
 *  You should request to that URL and show it to user
 *
 *  @param amount      Number of cash want to charge > 1000 (required)
 *  @param payload     Custom payload string generate by applecation, wanna sent with transaction (optional)
 *  @param block       The block to execute
 *  It should have the following argument signature: `^(MOGBankingResponseObject *responseObject, NSError *error)`.
 */
+ (void)makeBankingTransactionWithAmount:(NSUInteger)amount
                                 payload:(NSString *)payload
                                   block:(MOGBankingResponseBlock)block;

#pragma mark - Check transaction status

/**
 *  Check status of a transaction if you know its Id
 *
 *  @param transactionID Id of transaction that you wanna check
 *  @param block         The block to execute
 *  It should have the following argument signature: `^(MOGPaymentResponseObject *responseObject, NSError *error)`.
 */
+ (void)checkStatusOfTransaction:(NSString *)transactionID
                           block:(MOGPaymentResponseBlock)block;

@end
