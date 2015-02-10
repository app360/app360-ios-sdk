//
//  PaymentSDK.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/17/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MOGSMSItem.h"

//Delegate
#import "MOGSMSChargingDelegate.h"
#import "MOGCardChargingDelegate.h"
#import "MOGBankingChargingDelegate.h"

//Datasource
#import "MOGSMSChargingDataSource.h"
#import "MOGCardChargingDataSource.h"
#import "MOGBankingChargingDataSource.h"

//Response object
#import "MOGSMSResponseObject.h"
#import "MOGCardResponseObject.h"
#import "MOGBankingResponseObject.h"

@interface MOGPaymentSDK : NSObject

#pragma mark - Default payment form

/**
 *  Set image use to display on choose payment method form
 *
 *  @param icon image use to display. Normally, set your game/app 's icon as icon image
 */
+ (void)setIcon:(UIImage *)icon;

/**
 *  Set app name, use to display on choose payment method form
 *
 *  @param displayName Name of game/app
 */
+ (void)setDisplayName:(NSString *)displayName;

/**
 *  Set description for your game/app
 *
 *  @param description Description for your game/app (version, company, developer, server game, etc....)
 */
+ (void)setDescription:(NSString *)description;

/**
 *  Set datasource for sms charging form
 *
 *  @param datasource datasource for sms charging form
 */
+ (void)setSMSDatasource:(id<MOGSMSChargingDataSource>)datasource;

/**
 *  Set delegate for sms charging form
 *
 *  @param delegate delegate for sms charging form
 */
+ (void)setSMSDelegate:(id<MOGSMSChargingDelegate>)delegate;

/**
 *  Set datasource for card charging form
 *
 *  @param datasource datasource for card charging form
 */
+ (void)setCardDatasource:(id<MOGCardChargingDataSource>)datasource;

/**
 *  Set delagate for card charging form
 *
 *  @param delegate delegate for card charging form
 */
+ (void)setCardDelegate:(id<MOGCardChargingDelegate>)delegate;

/**
 *  Set datasource for banking charging form
 *
 *  @param datasource datasource for banking charging form
 */
+ (void)setBankingDatasource:(id<MOGBankingChargingDataSource>)datasource;

/**
 *  Set delegate for banking charging form
 *
 *  @param delegate delegate for banking charging form
 */
+ (void)setBankingDelegate:(id<MOGBankingChargingDelegate>)delegate;

/**
 *  Call default charging form of SDK. This form contain all supported payment method form like sms, phone card and e-banking
 *  <b>NOTE: Please set all necessary method above before call this function<b>
 *
 *  @param payload        Custom payload string
 */
+ (void)makeTransactionWithPayload:(NSString *)payload;

#pragma mark - SMS charging method

/**
 *  Make transaction via SMS. Show default sms form of SDK
 *
 *  @param amount     Available amount value. (required)
 *                    This param in NS_OPTIONS type, so you can add multi values and separate them with charactor '|'.
 *                    Eg: MOGSMSAmount500 | MOGSMSAmount4000
 *  @param delegate   Delegate for sms form
 *  @param datasource Datasource for sms form
 *  @param payload    Custom payload string
 */
+ (void)makeSMSTransactionWithDelegate:(id<MOGSMSChargingDelegate>)delegate
                            datasource:(id<MOGSMSChargingDataSource>)datasource
                               payload:(NSString *)payload;

/**
 *  Get SMS syntax with given amount. Use this method if you wanna build your custom payment form, instead of default form of SDK
 *
 *  @param amount                Available amount value. (required)
 *                               This param in NS_OPTIONS type, so you can add multi values and separate them with charactor '|'.
 *                               Eg: MOGSMSAmount500 | MOGSMSAmount4000
 *  @param payload               Custom payload string generate by applecation, wanna sent with transaction (optional)
 *  @param block                 The block to execute
 *  It should have the following argument signature: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)getSMSSyntaxWithSMSAmount:(MOGSMSAmount)amount
                          payload:(NSString *)payload
                            block:(MOGSMSResponseBlock)block;

#pragma mark - Phone card charging method

/**
 *  Make transaction via phone card. Show default card charging form of SDK
 *
 *  @param delegate    Delegate for phone card charging form (optional)
 *  @param datasource  Datasource for exchange description
 *  @param payload     Custom payload string (opetional)
 */
+ (void)makePhoneCardTransactionWithDelegate:(id<MOGCardChargingDelegate>)delegate
                                  datasource:(id<MOGCardChargingDataSource>)datasource
                                     payload:(NSString *)payload;

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
 *  Make transaction via e-banking, using default e-banking charging form of SDK
 *
 *  @param delegate   Delegate of e-banking charging form
 *  @param datasource Datasource for e-banking charging form
 *  @param payload    Custom payload string
 */
+ (void)makeBankingTransactionWithDelegate:(id<MOGBankingChargingDelegate>)delegate
                                datasource:(id<MOGBankingChargingDataSource>)datasource
                                   payload:(NSString *)payload;

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
