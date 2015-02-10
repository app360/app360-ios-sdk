//
//  SMSChargingDataSource.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 12/26/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MOGSMSChargingDataSource <NSObject>

@required

/**
 *  Return available sms amount for SMS charging form
 *
 *  @return MOGSMSAmount value. Return MOGSMSAmountAll to get all supported values
 */
- (MOGSMSAmount)allowedSMSAmount;

/**
 *  Return exchange description for sms item
 *
 *  @param amount current amount value
 *
 *  @return Exchange description for given amount value
 */
- (NSString *)smsExchangeDescriptionForAmount:(MOGSMSAmount)amount;

@end
