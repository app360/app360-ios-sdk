//
//  CardChargingDataSource.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 12/26/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MOGCardChargingDataSource <NSObject>

@required

/**
 *  Use to get number of phone card desciption item
 *
 *  @return number of phone card description item
 */
- (NSUInteger)numberOfItemsForCardCharging;

/**
 *  Return amount for item at given index
 *
 *  @param index index of the item
 *
 *  @return Amount for item at given index.
 */
- (NSUInteger)cardChargingAmountForIndex:(NSUInteger)index;

/**
 *  Return exchange description for the item at given index
 *
 *  @param index index of the item
 *
 *  @return exchange description for the item at given index
 */
- (NSString *)cardExchangeDescriptionForIndex:(NSUInteger)index;

@end
