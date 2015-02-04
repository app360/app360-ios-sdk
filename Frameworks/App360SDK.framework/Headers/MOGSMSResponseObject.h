//
//  MOGSMSResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "MOGPaymentResponseObject.h"

@class MOGSMSItem;

@interface MOGSMSResponseObject : MOGPaymentResponseObject

/*!
 @abstract Currency of sms amount
 */
@property (nonatomic, strong) NSString *currency;

/*!
 @abstract Syntax of sms
 */
@property (nonatomic, strong) NSString *syntax;

/*!
 @abstract Array of <MOGSMSItem>
 
 @see MOGSMSItem
 */
@property (nonatomic, strong) NSArray *services;

@end
