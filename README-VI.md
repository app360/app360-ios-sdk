

# Giới thiệu

App360SDK cung cấp cách thức đơn giản nhất để quản lý user và tích hợp thanh toán (bao gồm sms, thẻ điện thoại và e-banking) vào ứng dụng của bạn.

App360 iOS SDK hỗ trợ iOS từ 6.0 trở lên

Sơ đồ luồng tích hợp App360 SDK

![App360-sdk integration](http://i.imgur.com/PXdCmb3.png)

# Yêu cầu

## Môi trường phát triển

| App360SDK Version | Minimum iOS Target | 				Notes 			|
|:-----------------:|:------------------:|:----------------------------:|
|1.1.0|6.0|Xcode 6.1 is required. Support armv7, armv7s and arm64 architectures (+ i386 for the simulator)|

### Tương thích

App360 iOS SDK hỗ trợ tất cả iOS từ 6.0 trở lên. Hỗ trợ armv7, armv7s and arm64 architectures (+ i386 cho simulator).

### Xcode

Chúng tôi sử dụng Xcode 6.1.1 để viết project demo và SDK. Bạn có thể gặp một số lỗi nếu mở trên những phiên bản Xcode cũ hơn. Đó là lý do vì sao chúng tôi khuyên bạn sử dụng phiên bản mới nhất (non-beta) khả dụng.

# Bắt đầu với project Demo

Bạn cần clone hoặc download repository này về máy của bạn.

- `git clone https://github.com/app360/app360-ios-sdk.git`
- Hoặc, download tại https://github.com/app360/app360-ios-sdk/releases

Mở file AppDelegate.m trong demo project, tìm dòng `initializeWithApplicationId` và thay thế placeholder bằng cặp application id và secret key tương ứng với ứng dụng của bạn.

Chạy project. Ứng dụng mô tả cho bạn khả năng cũng như cách tích hợp của App360SDK, bao gồm cả app-scoped ID và payment (thanh toán).

# Cấu hình project của bạn

## Application Id & Client key

Để sử dụng bất kì chức năng nào của App360SDK, bạn cần phải có application id và secret key tương ứng. SDK sử dụng cặp key này để xác thực app (game) của bạn với server của SDK. Để lấy application ID và secret key, bạn cần đăng ký ứng dụng (game) của bạn trên https://developers.app360.vn/; application ID và secret key của của ứng dụng sẽ được hiển thị trong trang thông tin chi tiết của ứng dụng, tab `Information`.

![App credentials](http://i.imgur.com/4xZ8fYc.png)

## Channeling

Để hỗ trợ mô hình channeling, trong project cần chứa một file plist với tên `m360.plist`. File này chưa hai key là `channel` and `sub_channel`. `channel` là kênh phân phối, ví dụ như `mwork`, `appota` còn `sub_channel` là một chuỗi bất kì được định nghĩa bới kênh phân phối.

## Import SDK vào project của bạn

Để import SDK vào project của bạn, đơn giản chỉ việc kéo và thả.

Để bắt đầu, hãy kéo và thả `App360SDK.framework` và `MWNetworking.framework` vào mục **Embedded Binaries** :

![Imgur](http://i.imgur.com/y1cY5gD.png)

Sau đó, kéo và thả bundle của SDK (MOGBundle) vào project của bạn trong cửa sổ Project Navigation

![Imgur](http://i.imgur.com/YoSMVNE.png)

Chọn '**Create groups**' và '**Copy items if needed**' để copy SDK vào thư mục project của bạn

![Imgur](http://i.imgur.com/MOTKyPG.png)

Một số chức năng của App360 iOS SDK cần thêm một vào frameworks nhất định. Hãy chắc chắn bạn đã có chúng trong project. Nếu không, rất có thể ứng dụng của bạn không thể biên dịch được và Xcode sẽ thông báo lỗi..

Chọn project, di chuyển đến tab General, kéo xuống mục **Linked Frameworks and Libraries** sau đó ấn vào nút "**+**".

Tìm và thêm framework sau:

- MessageUI


## Thêm linker flag

![Imgur](http://i.imgur.com/K7odm6U.png)

# App-scoped ID

App-scoped ID là dịch vụ dùng để định danh người dùng cuối cho các ứng dụng tích hợp SDK của App360. App-scoped IDs được sinh ra bởi ứng dụng và có giá trị cho ứng dụng đó (hence _app-scoped_). Một ứng dụng không thể truy cập vào dữ liệu và user của ứng dụng khác.

App-scoped ID SDK cung cấp các phương thức sau:
- Đăng ký/Đăng nhập nặc danh (anonymously)
- Đăng ký đăng nhập qua Facebook/Google
- Liên kết app-scoped ID nặc danh với Facebook/Google account

**Note**: tất cả các API của App360 đều yêu cầu phải tồn tại của một app-scoped ID.

# Tích hợp ứng dụng của bạn với App360 SDK

## Khởi tạo SDK

SDK được khởi tạo qua class App360SDK. Và quá trình khởi tạo nên được thực hiện trong AppDelegate.

```objective-c
/*!
 @abstract Khoi tao SDK. Trong qua trinh khoi tao, SDK se tim va mo lai session cu. Neu khong co session nao duoc mo thi ban se phai tu mo session moi bang cac API ma SDK cung cap.
 
 @param applicationId   ID of the app that the token is issued for
 @param clientKey       secret key of the app that the token is issued for
 @param block           The block to execute
 It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
*/
+ (void)initializeWithApplicationId:(NSString *)applicationId
                          clientKey:(NSString *)clientKey
                              block:(MOGSessionResultBlock)block
```

`applicationId` và `clientKey` có thể lấy trên [App360 Developers](https://developers.app360.vn). `block` là một instance của `MOGSessionResultBlock`, được định nghĩa là `^(MOGSession *session, NSError *error)`

Trong suốt quá trình khởi tạo, SDK sẽ tìm kiếm và mở lại session cũ. Nếu không mở được session nào, object session trong block sẽ trả về nil. Khi đó ứng dụng sẽ phải tự mở một session mới..

![Imgur](http://i.imgur.com/PVqZ5bP.png)

```objective-c
[App360SDK initializeWithApplicationId:@"your-application-id"
                             clientKey:@"your-client-key"
                                 block:^(MOGSession *session, NSError *error) {
    
    if (error) {
        //init failed
        NSLog(@"Init SDK and open last session failed with error: %@", error.description);
    } else if (!session) {
        //session nil, means last session info is not exist => you must open session by yourself
        
        //pre-define scope user id (optional, scoped user id will generate randomly if you not set
        //you can use device identifier to be scoped user id
        
        NSString *uuid = [[[UIDevice currentDevice] identifierForVendor] UUIDString];
        [MOGSessionManager openActiveSessionWithScopeId:uuid
                                               userInfo:nil
                                                  block:^(MOGSession *session, NSError *error) {
            
            //After get session, you can retrieve current scoped user
            MOGScopedUser *currentUser = [MOGScopedUser getCurrentUser];
            NSLog(@"Scoped id: %@", currentUser.scopedId); //it should equals to your device uuid
        }];
        
        //Or you can open session with facebook access token. ONLY USE ONE OF TWO METHOD HERE
        
        /*
        
        NSString *facebookToken = @"token-from-facebook";
        [MOGSessionManager openActiveSessionWithService:kMOGServiceNameFacebook
                                                  token:facebookToken
                                                  block:^(MOGSession *session, NSError *error) {
            
        }];
         
         */
        
    } else {
        //Session object not null, means last session info found, sdk opens session automatically and return session object
        
        MOGScopedUser *currentUser = [MOGScopedUser getCurrentUser];
        NSLog(@"Scoped id: %@", currentUser.scopedId); //it should equals to your device uuid
    }
}];
```

## Khởi tạo session

App-scoped ID được đăng nhập thông qua việc tạo một session mới bằng ID đó. Có hai cách để mở một session (cả hai đều được gọi thông qua class  `MOGSessionManager`):

### Nặc danh (Anonymously)
```objective-c
/**
 *  @param scopeId   random UUID with lowercase hexadecimal digits. Optional
 *  @param userInfo  additional key/value defined by application
 *  @param block     The block to execute
 *  It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
+ (void)openActiveSessionWithScopeId:(NSString *)scopeId
                            userInfo:(NSDictionary *)userInfo
                               block:(MOGSessionResultBlock)block;
```

### Sử dụng Facebook/Google access token
```objective-c
/**
 *  @param serviceName  Name of OpenID service like facebook, app360, google
 *  @param token        Access token of service above
 *  @param block        The block to execute
 *  It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
 */
+ (void)openActiveSessionWithService:(NSString *)serviceName
                               token:(NSString *)token
                               block:(MOGSessionResultBlock)block;
```

Khi session được tạo bằng các nặc danh và scopedId đã tồn tại, một session mới sẽ được tạo cho app-scoped ID đó. Nếu scopedId không tồn tại, một app-scoped ID mới trùng với scopedId sẽ được tạo. Nếu scopedId null, nó sẽ được sinh một cách ngẫu nhiên.

Cần chú ý rằng sẽ không có bất kì cơ thế xác thực nào (password, token,...) cho việc đăng nhập nặc danh. Hình thức đăng nhập này nên được sử dụng sau khi ứng dụng đã có sẵn cơ chế xác thực riêng (trong trường hợp này, scopedId có thể được đặt theo username trong ứng dụng); hoặc khi ứng dụng không cần người dùng đăng nhập ngay. Anonymously logged-in user có thể liên kết với tài khoản Facebook và Google sau đó nhằm mục đích bảo mật và linh động (ví dụ như đăng nhập vào cùng 1 app-scoped ID trên những thiết bị khác nhau).

Khi session được tạo qua Facebook/Google access token, SDK sẽ kiểm tra token với server của Facebook/Google sau đó sẽ tìm một app-scoped ID đã tồn tài và đã liên kết với tài khoản mạng xã hội tương ứng. Nếu không có ID nào, thì một ID mới sẽ được sinh ngẫu nhiên và được liên kết với tài khoản mạng xã hội đó, session tương ứng sẽ được trả về. Nếu không, một session mới sẽ được sinh ra cho app-scoped ID tương ứng. Nếu sử dụng cách này thì cơ chế xác thực sẽ sử dụng qua Facebook và Google.

Ứng dụng sẽ nhận được session thông qua `MOGSessionResultBlock` block: `^(MOGSession *session, NSError *error)`

Trong `MOGSessionResultBlock`,  nếu session khác `nil`, nghĩa là session đã được khởi tạo thành công. Nếu `error` khác `nil`, đã có lỗi xảy ra, vui lòng kiểm tra object `error` để biết thêm thông tin về lỗi.

Khi session được khởi tạo thành công, ứng dụng có thể truy xuất session hiện tại qua phương thức `[MOGSessionManager getCurrentSession]` và scopedUser hiện tại qua `[MOGUser getCurrentUser]`

## Liên kết app-scoped ID với Facebook/Google

Để liên kết app-scoped ID hiện tại với Facebook/Google, gọi
```objective-c
- (void)linkWithFacebookToken:(NSString *)facebookToken block:(MOGSessionResultBlock)block;
```
or
```objective-c
- (void)linkWithGoogleToken:(NSString *)googleToken block:(MOGSessionResultBlock)block
```

#Payment

## Payment flow

Để đảm bảo độ tin cậy cho luồng thanh toán, ứng dụng của bạn có thể chọn tích hợp với SDK thông qua cả client-side và server-side, luồng thanh toán được mô tả trong sơ đồ dưới đây:

![Payment flow](http://www.websequencediagrams.com/cgi-bin/cdraw?lz=dGl0bGUgUGF5bWVudCBzZXF1ZW5jZQoKR2FtZS0-U0RLOgAUCXJlcXVlc3QgKDEpClNESy0-R2FtZTogVHJhbnNhY3Rpb24gaWQsIHN0YXR1cywgYW1vdW50ICgyKQBGB0dhbWUgc2VydmVyOiBzZW5kIHQAMAtkYXRhIGZvciBpbnNwZQBJBigzAF8LADIJACoMaWQAYQgsIHVzZXJfaWQgKDQAbAYAZQcAgT8HYWNrIChIVFRQAIEaByAyMDApICg1AB0PAIEYDWNvbmZpcm0gKDYAExMAFAs3KQ&s=rose)

1. Ứng dụng (client-side) gọi API thanh toán từ SDK, tùy chọn có thể gửi kèm payload (mô tả bên dưới).
2. SDK trả về transaction id và thông tin bổ sung (nếu có)
3. Ứng dụng client gửi thông tin về transaction lên server của ứng dụng để đợi xác nhận.
4. SDK server gọi đến server của ứng dụng đã được đăng ký để thông báo về trạng thái của giao dịch khi nó đã hoàn thành.
    - Lưu ý rằng hai bước (3) và (4), thứ tự có thể không giống như sơ đồ. Bước (4) hoàn toàn có thể xảy ra trước bước (3).
5. Server của ứng dụng thông báo đã nhận được kết quả cho SDK server bằng việc trả về HTTP status code 200.
6. Server của ứng dụng duyệt giao dịch dựa vào các thông tin của nó (transaction ID, payload,....)
7. Server của ứng dụng xác nhận/thông báo cho ứng dụng về trạng thái của giao dịch.

**Note**:
- Để đăng kí địa chỉ server nhận callback, truy cập https://developers.app360.vn/; điền _Payment callback endpoint_ trong trang thông tin của ứng dụng, tab _Information_.
- Trước khi sử dụng bất kì phương thức thanh toán náo, ứng dụng phải khởi tạo SDK và khởi tạo session trước. Xem mục [_SDK Initialization_](#khởi-tạo-sdk) trên.

Có hai cách để tích hợp thanh toán của App360SDK vào ứng dụng của bạn:
- Sử dụng UI mặc định mà SDK cung cấp
- Tự xây dựng UI của bạn và sử dụng các API thanh toán mà SDK cung cấp.

## Using payment form UI

Để tiết kiệm thời gian của bạn, chúng tôi cung cấp sẵn các form thanh toán trong SDK, bao gồm sms, thẻ điện thoại và e-banking. Chúng tôi cũng cung cấp sẵn một form hiển thị tất cả các phương thức thanh toán mà SDK hỗ trợ, user có thể chọn phương thức mà họ muốn thể mua vật phẩm hoặc thanh toán dịch vụ.

Để hiện form này, hãy gọi hàm
```objective-c
+ (void)makeTransactionWithPayload:(NSString *)payload;
```
trước đó, bạn cần phải gọi một số hàm để chuẩn bị dữ liệu đầu vào cho form đó. Ví dụ:

```objective-c
//Set delegate & datasource for sms charging
[MOGPaymentSDK setSMSDelegate:self];
[MOGPaymentSDK setSMSDatasource:self];

//Set delegate & datasource for card charging
[MOGPaymentSDK setCardDelegate:self];
[MOGPaymentSDK setCardDatasource:self];

//Set delegate & datasource for e-banking charging
[MOGPaymentSDK setBankingDatasource:self];
[MOGPaymentSDK setBankingDelegate:self];

//Personalize sdk form UI
[MOGPaymentSDK setIcon:[UIImage imageNamed:@"game-icon"]];
[MOGPaymentSDK setDisplayName:@"Swing Copters"];
[MOGPaymentSDK setDescription:@".Gear Studio"];

//Show form
[MOGPaymentSDK makeTransactionWithPayload:@"gamer-id"];
```

Xem SDK demo: http://marvl.in/2b575a

![Choose payment method form](http://i.imgur.com/1BvENrv.jpg)![SMS charging form](http://i.imgur.com/NZLHq6y.jpg)


![Phone card charging form](http://i.imgur.com/960YHbW.jpg)![E-Banking charging form](http://i.imgur.com/5twccza.jpg)

Chú ý rằng các delegate thông báo giao kết thúc chỉ có ý nghĩa là user đã hoàn tất việc gửi yêu cầu thanh toán dưới client (đã gửi SMS, đã nhận request nạp thẻ..), còn bản thân giao dịch có thể chưa thật sử kết thúc. Ví dụ, user có thể đã gửi SMS nhưng backend của chúng tôi chưa nhận được. Để kiểm tra trạng thái của giao dịch, gọi API `checkStatusOfTransaction:block:` (trình bày bên dưới).

##Using request classes

###Card Request

Để thanh toán qua thẻ điện thoại, sử dụng API sau:

```objective-c
[MOGPaymentSDK makePhoneCardTransactionWithVendor:VENDOR
                                         cardCode:CARD_CODE
                                       cardSerial:CARD_SERIAL
                                          payload:SOME_CUSTOM_PAYLOAD
                                            block:^(MOGCardResponseObject *responseObject, NSError *error) {
        if (!error) {
            NSLog(@"make phone card transaction success! Transaction Id is %@", responseObject.transactionId);
        } else {
            NSLog(@"make phone card transaction error: %@", error.description);
        }
    }];
```

Trong đó:

- *VENDOR*: Tên nhà mạng của thẻ điện thoại (vinaphone, mobifone, viettel)
- *CARD_CODE*: Mã thẻ điện thoại
- *CARD_SERIAL*: Số seri của thẻ điện thoại
- *SOME_CUSTOM_PAYLOAD*: Chuỗi bất kì gắn với giao dịch. Chuỗi này sẽ được gửi trả cùng giao dịch về callback URL.

###SMS Request

Để thanh toán bằng SMS, sử dụng API sau:

```objective-c
[MOGPaymentSDK getSMSSyntaxWithAmount:AMOUNT
                              payload:CUSTOM_PAYLOAD
                                block:^(MOGSMSResponseObject *responseObject, NSError *error) {
        if (!error) {
            NSLog(@"get sms syntax success! Transaction Id is %@", responseObject.transactionId);
        } else {
            NSLog(@"get sms syntax error: %@", error.description);
        }
    }];
```

Trong đó:

-  *AMOUNT*: Số tiền muốn thanh toán
-  *CUSTOM_PAYLOAD*: Chuỗi bất kì gắn với giao dịch. Chuỗi này sẽ được gửi trả cùng giao dịch về callback URL.

###E-Banking Request

Để nạp tiền qua e-banking, sử dụng API sau

```objective-c
[MOGPaymentSDK makeBankingTransactionWithAmount:AMOUNT
                                        payload:@""
                                          block:^(MOGBankingResponseObject *responseObject, NSError *error) {
        if (!error) {
            NSLog(@"make banking transaction successfully! Transaction Id is %@", responseObject.transactionId);
        } else {
            NSLog(@"make banking transaction error: %@", error.description);
        }
    }];
```

Mô tả:

- *AMOUNT*: Số tiền muốn thanh toán

### Kiểm tra trạng thái giao dịch

Để kiểm tra trạng thái của giao dịch, sử dụng API sau:

```objective-c
[MOGPaymentSDK checkStatusOfTransaction:@"" block:^(MOGPaymentResponseObject *responseObject, NSError *error) {
        if (!error) {
            MOGTransactionStatus status = responseObject.status;
            MOGTransactionType type = responseObject.type;
            NSString *transactionId = responseObject.transactionId;
        } else {
            NSLog(@"Check transantion status failed: %@", error.description);
        }
    }];
```
Trong đó:

- *TRANSACTION_ID*: ID của giao dịch muốn kiểm tra

#Release Notes

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

#Known Issues

Hiện tại chưa có issues nào

#FAQ

**Application id và client key là gì?**

Đây là cặp key, dùng để xác thực ứng dụng (game) của bạn với SDK server.

**Application id và client key có thể lấy ở đâu?**

1. Truy cập https://developers.app360.vn
2. Đăng nhập nếu bạn đã có tài khoản, nếu chưa hãy đăng ký tài khoản mới
3. Mở ứng dụng của bạn trong App360 dashboard. Nếu chưa có hãy tạo mới. Sau đó, chọn tab Information
4. Trong tab này, copy application key và secret key

**App360 iOS SDK chiếm bao nhiêu dung lượng trong ứng dụng của tôi?**

Phiên bản mới nhất của SDK nặng khoảng hơn 3MB. Nhưng đó không phải dung lượng mà SDK chiếm khi submit lên Apple Store.
Dựa vào rất nhiều lần thử nghiệm, SDK sau khi submit lên Appstore sẽ chiếm khoảng dưới 1MB ứng dụng.
Ứng dụng càng lớn, SDK càng ít ảnh hưởng đến dung lượng cuối cùng của ứng dụng.

# Hỗ trợ
Vui lòng liên hệ với [chúng tôi](mailto:support@app360.vn) về những vấn đề chung.

## Về những vấn đề kỹ thuật
Trong trường hợp bạn có những vấn đề về kỹ thuật, vui lòng liên hệ với [đội kỹ thuật của chúng tôi](mailto:support@app360.vn).
Vui lòng cung cấp những thông tin sau khi liên hệ, chúng sẽ giúp chúng tôi hỗ trợ bạn nhanh hơn rất nhiều.

 - **Phiên bản của SDK** bạn đang sử dụng. Bạn có thể biết được phiên bản của SDK thông qua việc gọi hàm `[App360SDK getSDKVersion];`.
 - **Môi trường** có thể tái hiện lại vấn đề (máy ảo hay thiết bị? thiết bị gì? iOS phiên bản bao nhiêu?)
 - **Các bước** để tái hiện vấn đề.
 - Nếu có thể, bạn hãy cung cấp **một vài đoạn code**, thậm chí cả project nếu có thể.

> Để biết thêm thông tin chi tiết, vui lòng truy cập https://developers.app360.vn.