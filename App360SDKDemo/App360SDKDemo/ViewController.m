//
//  ViewController.m
//  App360SDKDemo
//
//  Created by Tran Manh Tuan on 1/29/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "ViewController.h"

#import <App360SDK/App360SDK.h>

#pragma mark - User object

@interface User : NSObject

@property (nonatomic, strong) NSString *userId;

@end

@implementation User


@end

//=============================================

#pragma mark - View Controller

@interface ViewController ()

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)loginWithUserName:(NSString *)username password:(NSString *)password complettion:(void (^)(User *user))completion {
    //your code to authorize user here...
    
    //Just for example, i will sleep 2 seconds and return user with user id equals with username
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        sleep(2);
        
        User *user = [[User alloc] init];
        user.userId = username;
        
        dispatch_async(dispatch_get_main_queue(), ^{
            if (completion) {
                completion(user);
            }
        });
    });
}

- (IBAction)onLoginButtonTapped:(id)sender {
    
    //call your login method here
    [self loginWithUserName:self.txtUsername.text password:self.txtPassword.text complettion:^(User *user) {
        
        //After login and received user id, call create appscoped-id session
        [MOGSessionManager openActiveSessionWithScopeId:user.userId userInfo:nil block:^(MOGSession *session, NSError *error) {
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
    }];
}
@end
