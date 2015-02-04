//
//  PaymentSDK.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/17/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MOGSMSItem.h"

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
 *                               Eg: MOGAmount500 | MOGAmount4000
 *  @param block                 The block to execute
 *  It should have the following argument signature: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)getSMSSyntaxWithAmount:(MOGAmount)amount
                         block:(MOGSMSResponseBlock)block;

/**
 *  Get SMS syntax with given amount. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param amount                Available amount value. (required)
 *                               This param in NS_OPTIONS type, so you can add multi values and separate them with charactor '|'.
 *                               Eg: MOGAmount500 | MOGAmount4000
 *  @param payload               Custom payload string generate by applecation, wanna sent with transaction (optional)
 *  @param block                 The block to execute
 *  It should have the following argument signature: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)getSMSSyntaxWithAmount:(MOGAmount)amount
                       payload:(NSString *)payload
                         block:(MOGSMSResponseBlock)block;

#pragma mark - Phone card charging method

/**
 *  Make transaction via phone card. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param vendor     Name of service provider. Supported values are vinaphone, mobifone, viettel (required)
 *  @param cardCode   PIN number of phone card (required)
 *  @param cardSerial Serial number (required)
 *  @param block      The block to execute
 *  It should have the following argument signature: `^(MOGCardResponseObject *responseObject, NSError *error)`.
 */
+ (void)makePhoneCardTransactionWithVendor:(MOGVendor)vendor
                                  cardCode:(NSString *)cardCode
                                cardSerial:(NSString *)cardSerial
                                     block:(MOGCardResponseBlock)block;

/**
 *  Make transaction via phone card. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param vendor     Name of service provider. Supported values are vinaphone, mobifone, viettel (required)
 *  @param cardCode   PIN number of phone card (required)
 *  @param cardSerial Serial number (required)
 *  @param payload    Custom payload string generate by applecation, wanna sent with transaction (optional)
 *  @param block      The block to execute
 *  It should have the following argument signature: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)makePhoneCardTransactionWithVendor:(MOGVendor)vendor
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
 *  @param block       The block to execute
 *  It should have the following argument signature: `^(MOGBankingResponseObject *responseObject, NSError *error)`.
 */
+ (void)makeBankingTransactionWithAmount:(NSUInteger)amount
                                   block:(MOGBankingResponseBlock)block;

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
