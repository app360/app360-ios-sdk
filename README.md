

#Introduction

Payment SDK is a part of App360SDK, provides easiest way to pay any item via sms, phone card and e-banking

#Requirements

##Application Id & Client key

To using any function of App360SDK, you need to configure application id and client key. SDK uses this pair of key to authorize your app (game) with SDK's server.

##Development Environment

###Library compatibility

The App360 iOS SDK supports all iOS 6.0 and above versions. It compiles against the armv7, armv7s and arm64 architectures (+ i386 for the simulator).

###Xcode

We are using Xcode 6.1.1 to create our demo projects. You may encounter some errors if you are using a lower version of Xcode. That's why we recommend you work on the latest (non-beta) available version.

###Sample projects

We provide sample projects to help you implement our SDK. These sample projects can be downloaded from Github

###Download the Payment iOS SDK

The SDK can be downloaded from the dashboard or from Github

#Setup your project

##Import the library into your project

The sample project displays the simplest way to install the SDK inside your app: Dragging & dropping the SDK into your own project.

To get started, drag the SDK onto Linked Frameworks and Libraries section :

![Imgur](http://i.imgur.com/y1cY5gD.png)

Choose '**Create groups**' and select '**Copy items if needed**' to copy sdk to your project folder

![Imgur](http://i.imgur.com/MOTKyPG.png)

The App360 iOS SDK requires additional frameworks to operate. Make sure to have them in your project. If you fail to do so, your project will not compile and XCode will produce errors.

Navigate to the General tab, scroll down to **Linked Frameworks and Libraries** and then hit the "+" button.

Search for and add the following frameworks:

- Security
- MessageUI


##Add linker flag

![Imgur](http://i.imgur.com/K7odm6U.png)

##Initialize the library

![Imgur](http://i.imgur.com/PVqZ5bP.png)

Call this function before using any API of Payment SDK

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
            [MOGSession openActiveSessionWithScopeId:uuid
                                            userInfo:nil
                                               block:^(MOGSession *session, NSError *error) {
                
                //After get session, you can retrieve current scoped user
                MOGUser *currentUser = [MOGUser currentUser];
                NSLog(@"Scoped id: %@", currentUser.scopedId); //it should equals to your device uuid
            }];
            
            //Or you can open session with facebook access token. ONLY USE ONE OF TWO METHOD HERE
            
            /*
            
            NSString *facebookToken = @"token-from-facebook";
            [MOGSession openActiveSessionWithService:kMOGServiceNameFacebook 
                                               token:facebookToken 
                                               block:^(MOGSession *session, NSError *error) {
                
            }];
             
             */
            
        } else {
            //Session object not null, means last session info found, sdk opens session automatically and return session object
            
            MOGUser *currentUser = [MOGUser currentUser];
            NSLog(@"Scoped id: %@", currentUser.scopedId); //it should equals to your device uuid
        }
    }];
```

Description:

- *APPLICATION_ID*: the access key of your app (game), which provided by us 
- *CLIENT_KEY*: the secret key, pair with the access key, which provided by us
- *DEFAULT_SCOPED_USER_ID*: Scoped user id that using to login by default

#Card Charging

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

Or without payload:

```objective-c
[MOGPaymentSDK makePhoneCardTransactionWithVendor:VENDOR
                                         cardCode:CARD_CODE
                                       cardSerial:CARD_SERIAL
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

#SMS Charging

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

Or without payload

```objective-c
[MOGPaymentSDK getSMSSyntaxWithAmount:AMOUNT
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

#E-Banking Charging

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

or without payload

```objective-c
[MOGPaymentSDK makeBankingTransactionWithAmount:AMOUNT
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

#Checking transaction status

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

##Version 1.0.0

**Release date**: 10 Nov 2014

 - Initialization version support charging via card and SMS. 
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

**How much does the Appsfire iOS SDK add to my application size?**
The latest version of the SDK weighs less than 2MB. But this isn't the size which will be added to your archive when submitted to iTunes.
Based on several tests, it should adds below 1MB depending of the size of your application.
The bigger your app is, the less the Appsfire iOS SDK will have an impact on the final size.

#Support
Please contact [us](mailto:tuantm@toivui.com) for general inquiries.

##For a technical issue
In case you have a technical issue, you can reach [our technical support team](mailto:tuantm@toivui.com).
Please provide the following information when you reach out, it'll allow us to help you much more quickly.

 - **The library version** you're using. You can get the precise number by
   printing the result of the [AppsfireSDK versionDescription]; method.
 - **The platform** used to produce the problem (device model or simulator),
   and the iOS version.
 - **The steps** to reproduce the problem.
 - If possible, **some pieces of code**, or even a project.

> For more information, please go to https://developers.app360.vn.