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
 @abstract Đơn vị tiền tệ
 */
@property (nonatomic, strong) NSString *currency;

/*!
 @abstract Cú pháp tin nhắn
 */
@property (nonatomic, strong) NSString *syntax;

/*!
 @abstract Mảng các <MOGSMSItem>
 */
@property (nonatomic, strong) NSArray *services;

@end
