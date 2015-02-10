//
//  SMSChargingDelegate.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 12/19/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MOGSMSChargingDelegate <NSObject>

@optional

- (void)SMSTransactionDidFinishWithId:(NSString *)transactionId syntax:(NSString *)syntax recipient:(NSArray *)recipient;

- (void)SMSTransactionDidFailedWithError:(NSError *)error;

@end
