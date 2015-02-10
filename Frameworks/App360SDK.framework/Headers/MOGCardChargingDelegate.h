//
//  CardChargingDelegate.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 12/19/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MOGCardChargingDelegate <NSObject>

@optional

- (void)cardTransactionFinishWithId:(NSString *)transactionId details:(NSDictionary *)details;

- (void)cardTransactionDidFailedWithError:(NSError *)error;

@end
