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

## 6. Bắt đầu code

### 6.1. Khởi tạo SDK

SDK được khởi tạo thông qua class App360SDK.

Mở class AppDelegate và import App360SDK như sau:

```Objective-C
#import <App360SDK/App360SDK.h>
```

Trong phương thức `application:didFinishLaunchingWithOptions`, gọi hàm khởi tạo của App360SDK

```Objective-C
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  
  [App360SDK initializeWithApplicationId:@"your-app-id"
                               clientKey:@"your-app-secret"];
  
  //Your code
}
```

Bạn có thể lấy `appID` và `appSecret` trong code mẫu bên trên từ App360 dashboard. Đăng nhập vào tài khoản của bạn, chọn ứng dụng mà bạn đang tích hợp, bạn sẽ thấy key bạn cần trong tab `Information`

![App credential](http://i.imgur.com/Bp1ymT0.jpg)

### 6.2. Khởi tạo session

Sau khi khởi tạo SDK, bạn cần phải tạo appscoped session. Tất cả các API của App360SDK đều cần chạy trên một session nào đó.

Để tạo một session, gọi `openActiveSessionWithScopeId:userInfo:block:` trong `MOGSessionManager` class

```Objective-C
[MOGSessionManager openActiveSessionWithScopeId:@"scoped-id" userInfo:nil block:^(MOGSession *session, NSError *error) {
            if (session) {
                //Create appscoped-id session successfully!
                //After session create, you can access info of current user via:
                
                MOGScopedUser *currentUser = [MOGScopedUser getCurrentUser];
                NSLog(@"Scoped-id of current user: %@, come from channel: %@, subChannel: %@", currentUser.scopedId, currentUser.channel, currentUser.subChannel);
            } else {
                
                //Something went wrong! Check error object for more information
                NSLog(@"Create session failed. Error: %@", error.description);
            }
        }];
```

Giá trị `scoped-id` nên đặt là gì?

- Nếu game/app của bạn có user, `scoped-id` nên được đặt với giá trị bằng với user id trong hệ thống của bạn và nên được gọi ngay sau khi xác thực xong user.
- Nếu game/app của bạn không có user, `scoped-id` nên được đặt theo device id và bạn có thể gọi hàm này sớm nhất có thể. Chúng tôi gợi ý bạn có thể gọi ngay sau khi gọi hàm khởi tạo SDK.

Xin chúc mừng. Bạn đã tích hợp xong cơ bản App360SDK

# Làm gì tiếp theo?

- Xem thêm [tài liệu của chúng tôi](http://docs.app360.vn/) để biết thêm những thông tin chi tiết về các hàm của App360SDK.
- Tích hợp với [Payment API](http://docs.app360.vn/?page_id=271)
- Nếu gặp bất kì vấn đề gì, vui lòng xem qua [trang FAG](http://docs.app360.vn/?page_id=228) hoặc gửi yêu cầu hỗ trợ cho chúng tôi

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