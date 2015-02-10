//
//  BankingChargingDataSource.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 12/26/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MOGBankingChargingDataSource <NSObject>

@required

/**
 *  Use to get number of e-banking item
 *
 *  @return number of e-banking item
 */
- (NSUInteger)numberOfItemsForBankingCharging;

/**
 *  Return amount for item at given index
 *
 *  @param index index of the item
 *
 *  @return Amount for item at given index. Must >1000
 */
- (NSUInteger)bankingChargingAmountForIndex:(NSUInteger)index;

/**
 *  Return exchange description for the item at given index
 *
 *  @param index index of the item
 *
 *  @return exchange description for the item at given index
 */
- (NSString *)bankingExchangeDescriptionForIndex:(NSUInteger)index;

@end
