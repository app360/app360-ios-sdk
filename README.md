**Other language**: [Tiếng Việt](https://github.com/app360/app360-ios-sdk/blob/master/README-VI.md)

#Introduction

App360SDK provides easiest way to integrate user management and payment methods (including sms, phone card and e-banking) into your application.

The App360 iOS SDK supports iOS version 6.0 and above.

#Requirements

##Development Environment

| App360SDK Version | Minimum iOS Target | 				Notes 			|
|:-----------------:|:------------------:|:----------------------------:|
|1.5.0|6.0|Xcode 6.1 is required. Support armv7, armv7s and arm64 architectures (+ i386 for the simulator)|

###Library compatibility

The App360 iOS SDK supports all iOS 6.0 and above versions. It compiles against the armv7, armv7s and arm64 architectures (+ i386 for the simulator).

###Xcode

We are using Xcode 6.4 to create our demo projects. You may encounter some errors if you are using a lower version of Xcode. That's why we recommend you work on the latest (non-beta) available version.

#Getting started with Demo project

Firstly, clone or download this repository to your machine.

- `git clone https://github.com/app360/app360-ios-sdk.git`
- Or, download from https://github.com/app360/app360-ios-sdk/releases

Open AppDelegate.m inside demo project, find `initializeWithApplicationId` line and replace the placeholders with your application credentials.

Run the project. The app demonstrates capability of App360 SDK, including app-scoped ID and payment.

# 6 Step to integrate with App360SDK

## 1. Create an account

The first thing you need to do to get started with App360 is [sign up for a free account](https://developers.app360.vn/). After create account, you can access App360 dashboard to create or manage your apps.

## 2. Create your app

To integrate with App360SDK you need to create new application. Each application has a pair of key (application id and application secret key) that will be used to authorize with SDK's server.

## 3. Download SDK

There are multiple ways to include the App360 SDK into an Xcode project. We can use CocoaPods, manually include the framework and its dependencies

> ### Cocoapod (Coming soon)
> CocoaPods is the fastest way to get up and running with App360 in your iOS app. Just add the following to your Podfile, pod install, and skip to Getting started in Xcode
> ```
pod 'App360SDK', '>= 1.4.0'
```
> ### Download App360SDK
> Download the iOS SDK from the this repo, unzip the App360 SDK file, drag the .framework folder to your XCode project under Frameworks

## 4. Installing SDK

### Frameworks & Dependencies

The App360 framework depends on these other frameworks. Add them to your project:

| Framework |
|-----------|
|SystemConfiguration.framework|
|CoreMobileServices.framework|
|CoreTelephony.framework|

### Classes & Categories

The App360 framework makes use of Objective-C classes and categories, so we'll need to add this under "Other Linker Flags" in Build Settings:

```
-ObjC
```

### Can't find the "Other Linker Flags" option?

If the "Other Linker Flags" option isn't showing, make sure the tabs in the top left of the Build Settings section are set to "All" and "Combined" rather than "Basic" and "Levels". "Other Linker Flags" is available in the "Linking" subsection.

## 5. Add App360 config file

In order to support channeling, the application's assets directory should contain a properties file named `app360.plist`. The file should contain two keys `channel` and `sub_channel`. `channel` is distribution channel such as mwork, appota while `sub_channel` is arbitrary string defined by the distribution channel itself.
You can get this file from demo project or download it [here](#)

## 6. Start coding

### 6.1. Initialize SDK

The SDK could be initialized via App360SDK class. Initialization should be done on AppDelegate.

Open your AppDelegate class and import App360SDK like this:

```Objective-C
#import <App360SDK/App360SDK.h>
```

In `application:didFinishLaunchingWithOptions` method, call initialize method of App360SDK

```Objective-C
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  
  [App360SDK initializeWithApplicationId:@"your-app-id"
                               clientKey:@"your-app-secret"];
  
  //Your code
}
```

You can get `appID` and `appSecret` in the code example above from App360 dashboard. Login your account, choose the app you are working on and you will see the keys you need in `Information` tab

![App credential](http://i.imgur.com/Bp1ymT0.jpg)

### 6.2. Initialize session

After initialize SDK, you MUST create an appscoped session. All API of App360SDK require to run on a session.

To create session, call `openActiveSessionWithScopeId:userInfo:block:` in `MOGSessionManager` class

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

So, what should `scoped-id` value be?

- If your game/app has user, `scoped-id` should be your user id and should call right after authorize user.
- If your game/app does not have user, `scoped-id` should be device id and you can call as soon as posible. We suggest you call it right after call initialize SDK method.

And done!

# What's next?

- Checkout [our document](http://docs.app360.vn/) for more infomation of App360SDK
- Integrate with [Payment API](http://docs.app360.vn/?page_id=271)
- If you got any trouble, checkout the [FAG page](http://docs.app360.vn/?page_id=228) or send a support request

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