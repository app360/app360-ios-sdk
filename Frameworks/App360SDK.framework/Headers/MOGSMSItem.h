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
 @abstract Cú pháp tin nhắn
 */
@property (nonatomic, strong, readonly ) NSString *syntax;

/*!
 @abstract Đơn vị tiền tệ tương ứng với 'amount'
 */
@property (nonatomic, strong, readonly ) NSString *currency;

/*!
 @abstract Đầu số gửi đến
 */
@property (nonatomic, strong, readonly ) NSString *recipient;

/*!
 @abstract Số tiền sẽ nạp / Mệnh giá của tin nhắn
 */
@property (nonatomic, strong, readonly ) NSString *amount;

/*!
 @abstract Giá trị quy đổi (Ví dụ: 20 coin)
 */
@property (nonatomic, strong, readwrite) NSString *exchangeDescription;

@end
