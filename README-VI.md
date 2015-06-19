**Other language**: [English](https://github.com/app360/app360-ios-sdk/blob/master/README.md)

# Giới thiệu

App360SDK cung cấp cách thức đơn giản nhất để quản lý user và tích hợp thanh toán (bao gồm sms, thẻ điện thoại và e-banking) vào ứng dụng của bạn.

App360 iOS SDK hỗ trợ iOS từ 6.0 trở lên

# Yêu cầu

##Môi trường phát triển

| App360SDK Version | Minimum iOS Target | 				Notes 			|
|:-----------------:|:------------------:|:----------------------------:|
|1.4.0|6.0|Xcode 6.1 is required. Support armv7, armv7s and arm64 architectures (+ i386 for the simulator)|

### Tương thích

App360 iOS SDK hỗ trợ tất cả iOS từ 6.0 trở lên. Hỗ trợ armv7, armv7s and arm64 architectures (+ i386 cho simulator).

### Xcode

Chúng tôi sử dụng Xcode 6.3.2 để viết project demo và SDK. Bạn có thể gặp một số lỗi nếu mở trên những phiên bản Xcode cũ hơn. Đó là lý do vì sao chúng tôi khuyên bạn sử dụng phiên bản mới nhất (non-beta) khả dụng.

# Bắt đầu với project Demo

Bạn cần clone hoặc download repository này về máy của bạn.

- `git clone https://github.com/app360/app360-ios-sdk.git`
- Or, download from https://github.com/app360/app360-ios-sdk/releases

Mở file AppDelegate.m trong demo project, tìm dòng initializeWithApplicationId và thay thế placeholder bằng cặp application id và secret key tương ứng với ứng dụng của bạn.

Chạy project. Ứng dụng mô tả cho bạn khả năng cũng như cách tích hợp của App360SDK, bao gồm cả app-scoped ID và payment (thanh toán).

# 6 bước để tích hợp với App360SDK

## 1. Tạo tài khoản

Việc đầu tiên bạn cần làm là [đăng ký một tài khoản miễn phí](https://developers.app360.vn/) trên App360. Sau khi có tài khoản, bạn có thể truy cập vào App360 dashboard để tạo và quản lý các ứng dụng của bạn.

## 2. Tạo ứng dụng

Để tích hợp với App360SDK, bạn cần phải tạo một ứng dụng trên trang developer của App360. Mỗi ứng dụng sẽ có một cặp key (app id và app secret). Cặp key này sẽ được dùng để xác thực với server của SDK

## 3. Tải SDK

Có rất nhiều các để tải App360SDK vào project Xcode. Bạn có thể dùng CocoaPods hoặc tự tay tải và thêm framework cùng các thư viện liên quan vào project

> ### Cocoapod (Coming soon)
> CocoaPods là cách nhanh nhất để tải và chạy App360SDK trên ứng dụng iOS. Chỉ cần thêm dòng dưới đây vào Podfile và gọi lệnh `pod install`
> ```
pod 'App360SDK', '>= 1.4.0'
```
> ### Tải App360SDK
> Bạn có thể tải iOS SDK ngay từ repo này. Giải nén App360SDK, kéo App360SDK và các framework kèm theo vào project của bạn

## 4. Tích hợp SDK

### Frameworks & Dependencies

App360 SDK phụ thuộc vào một số framework khác. Bạn cần thêm chúng vào project của mình. Cụ thể thêm những framework sau:

| Framework |
|-----------|
|SystemConfiguration.framework|
|CoreMobileServices.framework|
|CoreTelephony.framework|

### Classes & Categories

App360 framework sử dụng class và categories Objective-C nên bạn cần phải thêm cờ sau vào mục "Other Linker Flags" trong Build Settings:

```
-ObjC
```

### Không tìm thấy lựa chọn "Other Linker Flags"?

Nếu bạn không tìm thấy mục "Other Linker Flags", bạn cần chắc chắn tab được chọn ở góc trên bên trái của Build Settings là "All" và "Combined" chứ không phải "Basic" và Levels". "Other Linker Flags" được đặt trong chuyên mục con "Linking"

## 5. Thêm file config của App360

Để hỗ trợ mô hình channeling, trong project cần chứa một file plist với tên `app360.plist`. File này chứa hai key là `channel` and `sub_channel`. `channel` là kênh phân phối, ví dụ như mwork, appota còn `sub_channel` là một chuỗi bất kì được định nghĩa bới kênh phân phối.

Bạn có thể lấy file này từ project demo hoặc download [tại đây](#)

## 6. Tích hợp code

SDK cần được khởi tạo qua class `App360SDK`. Hàm khởi tạo nên gọi sau khi game/app đã lấy được user id

```Objective-C
[App360SDK initializeWithApplicationId:@"your-application-id"
                             clientKey:@"your-client-key"
                                 block:^(MOGSession *session, NSError *error) {
 
    if (error) {
        //init failed
        NSLog(@"Init SDK and open last session failed with error: %@", error.description);
    } else if (!session) {
        //session nil, means last session info is not exist => you must open session by yourself
 
        NSString *scopedId = @"your-user-id";
        [MOGSessionManager openActiveSessionWithScopeId:scopedId
                                               userInfo:nil
                                                  block:^(MOGSession *session, NSError *error) {
 
            //After get session, you can retrieve current scoped user
            MOGScopedUser *currentUser = [MOGScopedUser getCurrentUser];
            NSLog(@"Scoped id: %@", currentUser.scopedId); //it should equals to your user id which you set above
        }];
    } else {
        //Session object not null, means last session info found, sdk opens session automatically and return session object
 
        MOGScopedUser *currentUser = [MOGScopedUser getCurrentUser];
        NSLog(@"Scoped id: %@", currentUser.scopedId); //it should equals to your device uuid
    }
}];
```

Bạn có thể lấy `appID` và `appSecret` trong code mẫu bên trên từ App360 dashboard. Đăng nhập vào tài khoản của bạn, chọn ứng dụng mà bạn đang tích hợp, bạn sẽ thấy key bạn cần trong tab `Information`

![App credential](http://i.imgur.com/Bp1ymT0.jpg)

Xin chúc mừng. Bạn đã tích hợp xong cơ bản App360SDK

# Làm gì tiếp theo?

- Xem thêm [tài liệu của chúng tôi](http://docs.app360.vn/) để biết thêm những thông tin chi tiết về các hàm của App360SDK.
- Tích hợp với [Payment API](http://docs.app360.vn/?page_id=271)
- Nếu gặp bất kì vấn đề gì, vui lòng xem qua [trang FAG](http://docs.app360.vn/?page_id=228) hoặc gửi yêu cầu hỗ trợ cho chúng tôi

#Release Notes

##Version 1.4.0

**Release date**: 18 Jun 2015
 - **[CHANGED]** Separate Payment UI and Payment Request API
 - **[DEPRECATE]** Deprecated `getSMSSyntaxWithSMSAmount` in `MOGPaymentSDK`
 - **[ADDED]** Add `requestSMSSyntaxWithAmount` in `MOGPaymentSDK`
 - **[DEPRECATE]** Deprecated `makePhoneCardTransactionWithVendor` in `MOGPaymentSDK`
 - **[ADDED]** Add `makeCardTransactionWithVendor` in `MOGPaymentSDK`

##Version 1.2.0

**Release date**: 31 Mar 2015

 - **[CHANGED]** Rename `m360.plist` to `app360.plist`

##Version 1.1.0

**Release date**: 10 Feb 2015

 - **[DELETE]** `MOGAmount` enum
 - **[DELETE]** `+getSMSSyntaxWithAmount:block:`
 - **[DELETE]** `+getSMSSyntaxWithAmount:payload:block:`
 - **[DELETE]** `+makePhoneCardTransactionWithVendor:cardCode:cardSerial:block:`
 - **[DELETE]** `+makeBankingTransactionWithAmount:block:`
 - **[ADD]** `MOGSMSAmount` enum
 - **[ADD]** `+getSMSSyntaxWithSMSAmount:payload:block:`
 - **[ADD]** `+makeSMSTransactionWithDelegate:datasource:payload:`
 - **[ADD]** `+makePhoneCardTransactionWithDelegate:datasource:payload:`
 - **[ADD]** `+makeBankingTransactionWithDelegate:datasource:payload:`
 - **[ADD]** `+makeTransactionWithPayload:`

##Version 1.0.0

**Release date**: 29 Jan 2015

 - Initialization version support charging via phone card, SMS and e-banking
 - Support checking transaction status

# Hỗ trợ
Vui lòng liên hệ với [chúng tôi](mailto:support@app360.vn) về những vấn đề chung.

## Về những vấn đề kỹ thuật
Trong trường hợp bạn có những vấn đề về kỹ thuật, vui lòng liên hệ với [đội kỹ thuật của chúng tôi](mailto:support@app360.vn).
Vui lòng cung cấp những thông tin sau khi liên hệ, chúng sẽ giúp chúng tôi hỗ trợ bạn nhanh hơn rất nhiều.

 - **Phiên bản của SDK** bạn đang sử dụng. Bạn có thể biết được phiên bản của SDK thông qua việc gọi hàm `[App360SDK getSDKVersion];`.
 - **Môi trường** có thể tái hiện lại vấn đề (máy ảo hay thiết bị? thiết bị gì? iOS phiên bản bao nhiêu?)
 - **Các bước** để tái hiện vấn đề.
 - Nếu có thể, bạn hãy cung cấp **một vài đoạn code**, thậm chí cả project nếu có thể.

> Để biết thêm thông tin chi tiết, vui lòng truy cập https://docs.app360.vn.