//
//  SMSItem.h
//  MworkPaymentSDK
//
//  Created by Tran Manh Tuan on 11/25/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MOGSMSItem : NSObject

/*!
 @abstract Syntax of sms
 */
@property (nonatomic, strong) NSString *syntax;

/*!
 @abstract Currency for sms amount
 */
@property (nonatomic, strong) NSString *currency;

/*!
 @abstract Phone number that sms will send to (eg: 8038, 8738...)
 */
@property (nonatomic, strong) NSString *recipient;

/*!
 @abstract Number of cash that user will be charged for this sms
 */
@property (nonatomic, assign) NSUInteger amount;

@end
