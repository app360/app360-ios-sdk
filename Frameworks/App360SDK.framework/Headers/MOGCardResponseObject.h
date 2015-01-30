//
//  MOGCardResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "MOGPaymentResponseObject.h"

@interface MOGCardResponseObject : MOGPaymentResponseObject

/*!
 @abstract Nhà mạng tương ứng với thẻ được giao dịch
 */
@property (nonatomic, assign) MOGVendor vendor;

/*!
 @abstract Mã thẻ dùng cho giao dịch
 */
@property (nonatomic, strong) NSString *cardCode;

/*!
 @abstract Số se-ri của thẻ dùng cho giao dịch
 */
@property (nonatomic, strong) NSString *cardSerial;

@end
