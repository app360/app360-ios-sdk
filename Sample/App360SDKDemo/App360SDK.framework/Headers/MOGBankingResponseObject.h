//
//  MOGBankingResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import <App360SDK/App360SDK.h>

@interface MOGBankingResponseObject : MOGPaymentResponseObject

/*!
 * @abstract Đường dẫn trang thanh toán cho giao dịch hiện tại.
 * User cần thực hiện giao dịch trên trang web với địa chỉ này.
 */
@property (nonatomic, strong) NSURL *payURL;

@end
