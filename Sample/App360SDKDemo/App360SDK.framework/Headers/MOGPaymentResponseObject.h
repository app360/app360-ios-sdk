//
//  MOGPaymentResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MOGPaymentResponseObject : NSObject

/*!
 @abstract Kết quả của request (Thành công / Thất bại)
 */
@property (nonatomic, assign) MOGAPICode code;

/*!
 @abstract Thông tin chi tiết tương ứng với từng request
 */
@property (nonatomic, strong) id details;

/*!
 @abstract Mã định danh cho giao dịch. Dùng cho việc đối soát hoặc kiểm tra trạng thái giao dịch
 */
@property (nonatomic, strong) NSString *transactionId;

/*!
 @abstract Thông tin payload gửi cùng request
 */
@property (nonatomic, strong) NSString *payload;

/*!
 @abstract Trạng thái của giao dịch
 */
@property (nonatomic, assign) MOGTransactionStatus status;

/*!
 @abstract Loại giao dịch (SMS/Phone card/E-banking)
 */
@property (nonatomic, assign) MOGTransactionType type;

/*!
 @abstract Thông báo kèm theo trong trường hợp API trả về lỗi
 */
@property (nonatomic, strong) NSString *message;

/**
 *  Hàm khởi tạo với đầu vào dạng JSON
 *
 *  @param JSON dữ liệu đầu vào dạng JSON
 *
 */
- (instancetype)initWithJSON:(id)JSON;

@end
