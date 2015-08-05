//
//  ViewController.h
//  App360SDKDemo
//
//  Created by Tran Manh Tuan on 1/29/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface ViewController : UIViewController

@property (weak, nonatomic) IBOutlet UITextField *txtUsername;
@property (weak, nonatomic) IBOutlet UITextField *txtPassword;

- (IBAction)onLoginButtonTapped:(id)sender;
@end

