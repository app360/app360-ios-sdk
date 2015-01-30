//
//  PaymentSDK.h
//  AppScopeID
//
//  Created by Tran Manh Tuan on 12/17/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "MOGSMSResponseObject.h"
#import "MOGCardResponseObject.h"
#import "MOGBankingResponseObject.h"

@interface MOGPaymentSDK : NSObject

#pragma mark - SMS charging method

/**
 *  Hàm gọi API lấy cú pháp nạp tiền bằng SMS. Sử dụng hàm này nếu không muốn dùng form tin nhắn mặc định của SDK
 *
 *  @param amount                Mệnh giá muốn hiện trong form thanh toán. (required)
 *                               Tham số này có dạng NS_OPTIONS nên có thể truyền 1 hoặc nhiều cách nhau bởi dấu "|".
 *                               Ví dụ: MOGAmount500 | MOGAmount4000
 *  @param block                 Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)getSMSSyntaxWithAmount:(MOGAmount)amount
                         block:(MOGSMSResponseBlock)block;

/**
 *  Hàm gọi API lấy cú pháp nạp tiền bằng SMS. Sử dụng hàm này nếu không muốn dùng form tin nhắn mặc định của SDK
 *
 *  @param amount                Mệnh giá muốn hiện trong form thanh toán. (required)
 *                               Tham số này có dạng NS_OPTIONS nên có thể truyền 1 hoặc nhiều cách nhau bởi dấu "|".
 *                               Ví dụ: MOGAmount500 | MOGAmount4000
 *  @param payload               Chuỗi bất kì do ứng dụng tự tạo; chuỗi này sẽ được gửi cho app/game server khi thanh toán thành công (optional)
 *  @param block                 Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGSMSResponseObject *responseObject, NSError *error)`.
 */
+ (void)getSMSSyntaxWithAmount:(MOGAmount)amount
                       payload:(NSString *)payload
                         block:(MOGSMSResponseBlock)block;

#pragma mark - Phone card charging method

/**
 *  Hàm gọi API thanh toán trực tiếp qua thẻ điện thoại. Sử dụng khi ứng dụng muốn dùng form thanh toán tự định nghĩa
 *
 *  @param vendor     Tên nhà mạng. Hỗ trợ 3 nhà mạng là vinaphone, mobifone, viettel (required)
 *  @param cardCode   Mã số thẻ điện thoại (required)
 *  @param cardSerial Số seri của thẻ điện thoại (required)
 *  @param block      Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGCardResponseObject *responseObject, NSError *error)`.
 */
+ (void)makePhoneCardTransactionWithVendor:(MOGVendor)vendor
                                  cardCode:(NSString *)cardCode
                                cardSerial:(NSString *)cardSerial
                                     block:(MOGCardResponseBlock)block;

/**
 *  Hàm gọi API thanh toán trực tiếp qua thẻ điện thoại. Sử dụng khi ứng dụng muốn dùng form thanh toán tự định nghĩa
 *
 *  @param vendor     Tên nhà mạng. Hỗ trợ 3 nhà mạng là vinaphone, mobifone, viettel (required)
 *  @param cardCode   Mã số thẻ điện thoại (required)
 *  @param cardSerial Số seri của thẻ điện thoại (required)
 *  @param payload    Chuỗi bất kì do ứng dụng tự tạo; chuỗi này sẽ được gửi cho app/game server khi thanh toán thành công (optional)
 *  @param block      Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGCardResponseObject *responseObject, NSError *error)`.
 */
+ (void)makePhoneCardTransactionWithVendor:(MOGVendor)vendor
                                  cardCode:(NSString *)cardCode
                                cardSerial:(NSString *)cardSerial
                                   payload:(NSString *)payload
                                     block:(MOGCardResponseBlock)block;

#pragma mark - Banking charging method

/**
 *  Hàm gọi API thanh toán qua thẻ ngân hàng, trả về URL của trang thanh toán cho giao dịch đó. 
 *  Sử dụng API này khi ứng dụng không muốn dùng form mặc định của SDK.
 *  Sau khi nhận được URL từ SDK trả về, ứng dụng cần hiện cho user website đó để user thực hiện thanh toán
 *
 *  @param amount      Số tiền muốn nạp > 1000 (required)
 *  @param block       Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGBankingResponseObject *responseObject, NSError *error)`.
 */
+ (void)makeBankingTransactionWithAmount:(NSUInteger)amount
                                   block:(MOGBankingResponseBlock)block;

/**
 *  Hàm gọi API thanh toán qua thẻ ngân hàng, trả về URL của trang thanh toán cho giao dịch đó.
 *  Sử dụng API này khi ứng dụng không muốn dùng form mặc định của SDK.
 *  Sau khi nhận được URL từ SDK trả về, ứng dụng cần hiện cho user website đó để user thực hiện thanh toán
 *
 *  @param amount      Số tiền muốn nạp > 1000 (required)
 *  @param payload     Chuỗi bất kì do ứng dụng tự tạo; chuỗi này sẽ được gửi cho app/game server khi thanh toán thành công (optional)
 *  @param block       Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGBankingResponseObject *responseObject, NSError *error)`.
 */
+ (void)makeBankingTransactionWithAmount:(NSUInteger)amount
                                 payload:(NSString *)payload
                                   block:(MOGBankingResponseBlock)block;

#pragma mark - Check transaction status

/**
 *  API dung de kiem tra trang thai cua giao dich
 *
 *  @param transactionID id cua giao dich muon kiem tra
 *  @param block         Code trong block này sẽ được thực thi khi hàm trả về kết quả
 *  Block này có dạng như sau: `^(MOGPaymentResponseObject *responseObject, NSError *error)`.
 */
+ (void)checkStatusOfTransaction:(NSString *)transactionID
                           block:(MOGPaymentResponseBlock)block;

@end
