//
//  BankingChargingDelegate.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 12/19/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol MOGBankingChargingDelegate <NSObject>

- (void)bankingTransactionDidReceiveUrl:(NSURL *)url transactionId:(NSString *)transactionId;

- (void)bankingTransactionDidFailWithError:(NSError *)error;

@end
