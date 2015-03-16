**Other language**: [Vietnamese](https://github.com/app360/app360-ios-sdk/blob/master/README-VI.md)

<!-- START doctoc generated TOC please keep comment here to allow auto update -->
<!-- DON'T EDIT THIS SECTION, INSTEAD RE-RUN doctoc TO UPDATE -->

- [Introduction](#introduction)
- [Requirements](#requirements)
  - [Development Environment](#development-environment)
    - [Library compatibility](#library-compatibility)
    - [Xcode](#xcode)
- [Getting started with Demo project](#getting-started-with-demo-project)
- [Setup your project](#setup-your-project)
  - [Application Id & Client key](#application-id-&-client-key)
  - [Channeling](#channeling)
  - [Import the library into your project](#import-the-library-into-your-project)
  - [Add linker flag](#add-linker-flag)
- [App-scoped ID](#app-scoped-id)
- [Integrate your application with App360 SDK](#integrate-your-application-with-app360-sdk)
  - [SDK Initialization](#sdk-initialization)
  - [Session initialization](#session-initialization)
    - [Anonymously](#anonymously)
    - [With Facebook/Google access token](#with-facebookgoogle-access-token)
  - [Linking app-scoped ID with Facebook/Google](#linking-app-scoped-id-with-facebookgoogle)
- [Payment](#payment)
  - [Payment flow](#payment-flow)
  - [Using payment form UI](#using-payment-form-ui)
  - [Using request classes](#using-request-classes)
    - [Card Request](#card-request)
    - [SMS Request](#sms-request)
    - [E-Banking Request](#e-banking-request)
    - [Checking transaction status](#checking-transaction-status)
- [Release Notes](#release-notes)
  - [Version 1.1.0](#version-110)
  - [Version 1.0.0](#version-100)
- [Known Issues](#known-issues)
- [FAQ](#faq)
- [Support](#support)
  - [For a technical issue](#for-a-technical-issue)

<!-- END doctoc generated TOC please keep comment here to allow auto update -->



#Introduction

App360SDK provides easiest way to integrate user management and payment methods (including sms, phone card and e-banking) into your application.

The App360 iOS SDK supports iOS version 6.0 and above.

App360 SDK 's Integration Flow

![App360-sdk integration](http://i.imgur.com/PXdCmb3.png)

#Requirements

##Development Environment

| App360SDK Version | Minimum iOS Target | 				Notes 			|
|:-----------------:|:------------------:|:----------------------------:|
|1.1.0|6.0|Xcode 6.1 is required. Support armv7, armv7s and arm64 architectures (+ i386 for the simulator)|

###Library compatibility

The App360 iOS SDK supports all iOS 6.0 and above versions. It compiles against the armv7, armv7s and arm64 architectures (+ i386 for the simulator).

###Xcode

We are using Xcode 6.1.1 to create our demo projects. You may encounter some errors if you are using a lower version of Xcode. That's why we recommend you work on the latest (non-beta) available version.

#Getting started with Demo project

Firstly, clone or download this repository to your machine.

- `git clone https://github.com/app360/app360-ios-sdk.git`
- Or, download from https://github.com/app360/app360-ios-sdk/releases

Open AppDelegate.m inside demo project, find `initializeWithApplicationId` line and replace the placeholders with your application credentials.

Run the project. The app demonstrates capability of App360 SDK, including app-scoped ID and payment.

#Setup your project

##Application Id & Client key

To using any function of App360SDK, you need to configure application id and secret. SDK uses this pair of key to authorize your app (game) with SDK's server. To retrieve application ID and client secret, register your application on https://developers.app360.vn/; your application ID and secret is available in application details page, Information tab.

![App credentials](http://i.imgur.com/4xZ8fYc.png)

##Channeling

In order to support channeling, the project's directory should contain a properties file named `m360.plist`. The file should contain two keys `channel` and `sub_channel`. `channel` is distribution channel such as `mwork`, `appota` while `sub_channel` is arbitrary string defined by the distribution channel itself.

##Import the library into your project

The sample project displays the simplest way to install the SDK inside your app: Dragging & dropping the SDK into your own project.

To get started, drag `App360SDK.framework` and `MWNetworking.framework` onto **Embedded Binaries** section :

![Imgur](http://i.imgur.com/y1cY5gD.png)

Then, drag and drop SDK's bundle into your project

![Imgur](http://i.imgur.com/YoSMVNE.png)

Choose '**Create groups**' and select '**Copy items if needed**' to copy sdk to your project folder

![Imgur](http://i.imgur.com/MOTKyPG.png)

The App360 iOS SDK requires additional frameworks to operate. Make sure to have them in your project. If you fail to do so, your project will not compile and XCode will produce errors.

Navigate to the General tab, scroll down to **Linked Frameworks and Libraries** and then hit the "**+**" button.

Search for and add the following frameworks:

- MessageUI


##Add linker flag

![Imgur](http://i.imgur.com/K7odm6U.png)

# App-scoped ID

App-scoped ID is App360's identification service for end-user of applications that integrate with our SDK. App-scoped IDs generated by an app is only valid for that app (hence _app-scoped_). Different applications cannot access each other's user and data.

App-scoped ID SDK provides the following functions:
- Sign-up/Login anonymously
- Sign-up/Login via Facebook/Google
- Link anonymous app-scoped ID with Facebook/Google account

**Note**: almost all App360 APIs require the existence of an app-scoped ID.

# Integrate your application with App360 SDK

## SDK Initialization

The SDK could be initialized via App360SDK class. Initialization should be done on AppDelegate.

```objective-c
/*!
 @abstract Initialize SDK. This method will open last active session (if exist). If not, you must open session by yourself
 
 @param applicationId   ID of the app that the token is issued for
 @param clientKey       secret key of the app that the token is issued for
 @param block           The block to execute
 It should have the following argument signature: `^(MOGSession *session, NSError *error)`.
*/
+ (void)initializeWithApplicationId:(NSString *)applicationId
                          clientKey:(NSString *)clientKey
                              block:(MOGSessionResultBlock)block
```

`applicationId` và `clientKey` could be acquired from [App360 Developers](https://developers.app360.vn). `block` is an instance of `MOGSessionResultBlock`, defined as `^(MOGSession *session, NSError *error)`

During initialization, the SDK will try to find and re-opened any cached app-scoped ID session. If the application hasn't opened any session, session in block will return nil and the application should open a new session.

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

## Session initialization

App-scoped ID is logged in via creating a new session for such ID. There are two ways to open a session (both via `MOGSessionManager` class):

###Anonymously
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

###With Facebook/Google access token
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

When session is created anonymously and scopedId exists, a new session will be created for that app-scoped ID. If scopedId doesn't exist, a new app-scoped ID with the same scopedId will be created first. If scopedId is null, it will be generated randomly.

Note that there's no authentication mechanism (password, token, etc) for anonymous login. This login type should be used when the application has already implemented its own authentication mechanism (in this case, scopedId should be set to app's username, for example); or when the application doesn't require the user to login immediately. Anonymously logged-in user could later be linked with Facebook/Google account for better security and portability (e.g. login the same app-scoped ID on different devices).

When session is created via Facebook/Google access token, the SDK will verify the token with Facebook/Google servers then try to find an existing app-scoped ID that is already linked with the corresponding social account. If there's no such ID, a new one will be generated randomly then link with the account and its session is returned. Otherwise, a new session is generated for the existing app-scoped ID. In this way, the authentication mechanism is provided by Facebook/Google.

The application receives initialized session via `MOGSessionResultBlock` block: `^(MOGSession *session, NSError *error)`

In `MOGSessionResultBlock`,  if session is not `nil`, it means session initialize successfully. And if error is not `nil`, its means something wrong happened, please check error object for more information.

In case session initialize successfully, the application could access current session via `[MOGSessionManager getCurrentSession]` and current scoped ID via `[MOGUser getCurrentUser]`

##Linking app-scoped ID with Facebook/Google

To link current app-scoped ID with Facebook/Google, call
```objective-c
- (void)linkWithFacebookToken:(NSString *)facebookToken block:(MOGSessionResultBlock)block;
```
or
```objective-c
- (void)linkWithGoogleToken:(NSString *)googleToken block:(MOGSessionResultBlock)block
```

#Payment

## Payment flow

In order to secure payment flow, your application might choose to integrate with our SDK on both client-side and server-side, in which case the payment flow is depict in the following diagram:

![Payment flow](http://www.websequencediagrams.com/cgi-bin/cdraw?lz=dGl0bGUgUGF5bWVudCBzZXF1ZW5jZQoKR2FtZS0-U0RLOgAUCXJlcXVlc3QgKDEpClNESy0-R2FtZTogVHJhbnNhY3Rpb24gaWQsIHN0YXR1cywgYW1vdW50ICgyKQBGB0dhbWUgc2VydmVyOiBzZW5kIHQAMAtkYXRhIGZvciBpbnNwZQBJBigzAF8LADIJACoMaWQAYQgsIHVzZXJfaWQgKDQAbAYAZQcAgT8HYWNrIChIVFRQAIEaByAyMDApICg1AB0PAIEYDWNvbmZpcm0gKDYAExMAFAs3KQ&s=rose)

1. The application (client-side) calls payment API from the SDK, optionally with a custom payload (documented below).
2. The SDK returns transaction id and other details (if available)
3. The application client sends transaction data to its server awaiting confirmation
4. SDK server calls a pre-registered endpoint of the application server to notify about transaction status when it completes
    - Note that there is no guarantee about the order of (3) and (4) (i.e. (4) may happen before (3))
5. Application server acknowledges SDK server's call by responding with HTTP status code 200.
6. Application server validates the transaction based on the information it has (transaction ID, payload, etc.)
7. Application server confirms/notifies game client about the status of the transaction

**Note**:
- To register your application's server endpoint, go to https://developers.app360.vn/; set _Payment callback endpoint_ in application details page, _Information_ tab.
- Before using any payment methods, the application must first initialize the SDK. See section _SDK Initialization_ above.

There are two methods to integrate payment functionality of App360 SDK into your application:
- Using the SDK's existing UI
- Implement your own UI and using the SDK's basic payment request classes.

## Using payment form UI

To save your time, we provide pre-build payment form, include sms, phone card and e-banking charging form. We also provide a form to show all supported payment method, user can choose which method that they want to use to purchase item.

To display the payment UI, call
```objective-c
+ (void)makeTransactionWithPayload:(NSString *)payload;
```
after set required parameter. For example:

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

See App360SDK in action: http://marvl.in/2b575a

![Choose payment method form](http://i.imgur.com/1BvENrv.jpg)![SMS charging form](http://i.imgur.com/NZLHq6y.jpg)


![Phone card charging form](http://i.imgur.com/960YHbW.jpg)![E-Banking charging form](http://i.imgur.com/5twccza.jpg)

Note that transaction finished in delegate only means that the user has finished placing a payment request, but the transaction itself might not be finished yet. For example, the user might has sent an SMS but our backend has not received it yet. In order to inquire the status of the transaction, use `checkStatusOfTransaction:block:` (documented later).

##Using request classes

###Card Request

To charge via phone card, please use the API below

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

Description:

- *VENDOR*: Name of mobile network operator that provide the phone card you use to charge
- *CARD_CODE*: The code of the phone card
- *CARD_SERIAL*: The serial of the phone card
- *SOME_CUSTOM_PAYLOAD*: Some custom string you want to send to your server when transaction finished.

###SMS Request

To charge via SMS, please use the APIs below:

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

Description:

-  *AMOUNT*: The number of money you want to charge
-  *CUSTOM_PAYLOAD*: Some custom string you want to send to your server when transaction finished

###E-Banking Request

To charge via E-Banking, please use the APIs

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

Description:

- *AMOUNT*: Amount want to charge (int)

###Checking transaction status

To check status of a transaction, please use checking transaction status API

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
Description:

- *TRANSACTION_ID*: ID of transaction you want to check

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

There's no known issues for now

#FAQ

**What is a application id and client key?**

They are a pair of key, used to authorize your app (game) with SDK's server.

**How can i get my application id and client key?**

1. Goto https://developers.app360.vn
2. Login if you already have an account or register a new one
3. Open your application in App360 dashboard, select Information tab
4. All key you need will be there

**How much does the App360 iOS SDK add to my application size?**

The latest version of the SDK weighs less than 2MB. But this isn't the size which will be added to your archive when submitted to iTunes.
Based on several tests, it should adds below 1MB depending of the size of your application.
The bigger your app is, the less the App360 iOS SDK will have an impact on the final size.

#Support
Please contact [us](mailto:support@app360.vn) for general inquiries.

##For a technical issue
In case you have a technical issue, you can reach [our technical support team](mailto:support@app360.vn).
Please provide the following information when you reach out, it'll allow us to help you much more quickly.

 - **The library version** you're using. You can get the precise number by
   printing the result of the `[App360SDK getSDKVersion];` method.
 - **The platform** used to produce the problem (device model or simulator),
   and the iOS version.
 - **The steps** to reproduce the problem.
 - If possible, **some pieces of code**, or even a project.

> For more information, please go to https://developers.app360.vn.