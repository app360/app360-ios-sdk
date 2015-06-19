//
//  ViewController.m
//  App360SDKDemo
//
//  Created by Tran Manh Tuan on 1/29/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "ViewController.h"

#import <App360SDK/App360SDK.h>

typedef NS_ENUM(u_int8_t, PaymentMethod) {
    PaymentMethodSMS = 0,
    PaymentMethodPhoneCard,
    PaymentMethodBanking
};

static inline NSString * NSStringFromType(MOGTransactionType type) {
    switch (type) {
        case MOGTransactionTypeSMS:
            return @"sms";
        case MOGTransactionTypeCard:
            return @"phone card";
        case MOGTransactionTypeBank:
            return @"bank";
        default:
            return nil;
    }
}

static inline NSString * NSStringFromStatus(MOGTransactionStatus status) {
    switch (status) {
        case MOGTransactionStatusBegin:
            return @"begin";
        case MOGTransactionStatusPending:
            return @"pending";
        case MOGTransactionStatusCompleted:
            return @"completed";
        case MOGTransactionStatusFailed:
            return @"failed";
        case MOGTransactionStatusUndefine:
        default:
            return @"undefine";
            break;
    }
}

@interface ViewController ()<UITableViewDataSource, UITableViewDelegate>

@property (weak, nonatomic) IBOutlet UITableView *tableView;

@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    self.tableView.tableFooterView = [UIView new];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

#pragma mark - Payment API
- (void)requestForSMS {
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK requestSMSSyntaxWithAmount:@"500, 10000, 15000, 50000" vendor:kMOGVendorVinaphone payload:payload block:^(MOGSMSResponseObject *responseObject, NSError *error)
    {
        if (error) {
            //API request failed
            
        } else if (responseObject.code == MOGAPICodeError){
            //API response 200 OK but something wrong
            
        } else {
            //success
            NSString *transactionId  = responseObject.transactionId;
            MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
            MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
            
            NSLog(@"SMS transaction: %@, type: %@, status: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status));
            
            NSArray *services = responseObject.services;
            for (MOGSMSItem *item in services) {
                NSString *syntax = item.syntax;
                NSString *sendTo = item.recipient;
                //Syntax charging
                NSLog(@"Send %@ to %@ to make transaction", syntax, sendTo);
            }
        }
    }];
}

- (void)requestForPhoneCard {
    NSString *cardCode = @"card-code";
    NSString *cardSerial = @"card-serial";
    
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK makeCardTransactionWithVendor:kMOGVendorGate cardCode:cardCode cardSerial:cardSerial payload:payload block:^(MOGCardResponseObject *responseObject, NSError *error)
    {
        if (error) {
            //API request failed
            NSLog(@"Error: %@", error.localizedDescription);
            
        } else if (responseObject.code == MOGAPICodeError){
            //API response 200 OK but something wrong
            NSLog(@"");
        } else {
            //success
            NSString *transactionId  = responseObject.transactionId;
            MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
            MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
            
            NSLog(@"Card transaction: %@, type: %@, status: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status));
        }
    }];
}

- (void)requestForEbanking {
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK makeBankingTransactionWithAmount:50000
                                            payload:payload
                                              block:^(MOGBankingResponseObject *responseObject, NSError *error) {
                                                  
                                                  if (error) {
                                                      //API request failed
                                                      
                                                  } else if (responseObject.code == MOGAPICodeError){
                                                      //API response 200 OK but something wrong
                                                      NSLog(@"e-banking charging error: %@", responseObject.message);
                                                  } else {
                                                      //success
                                                      NSString *transactionId  = responseObject.transactionId;
                                                      MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
                                                      MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
                                                      
                                                      //The URL of webpage use to charge this transaction.After receive this URL, you can guild user to pay via that webpage
                                                      NSURL *chargingURL = responseObject.payURL;
                                                      
                                                      NSLog(@"E-banking transaction: %@, type: %@, status: %@, URL: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status), chargingURL.absoluteString);
                                                  }
                                              }];
}

- (void)checkTransactionStatus {
    
    NSString *transactionId = @"transaction-id";
    
    [MOGPaymentSDK checkStatusOfTransaction:transactionId block:^(MOGPaymentResponseObject *responseObject, NSError *error) {
        if (!error) {
            NSLog(@"");
        } else {
            //Error
            NSLog(@"Check transaction error: %@", error);
        }
    }];
}

#pragma mark - Handle UITableViewCell did selected

- (void)processAPIRequestForIndex:(NSInteger)index {
    switch (index) {
        case PaymentMethodSMS:
        {
            [self requestForSMS];
            break;
        }
        case PaymentMethodPhoneCard:
        {
            [self requestForPhoneCard];
            break;
        }
        case PaymentMethodBanking:
        {
            [self requestForEbanking];
            break;
        }
        default:
        {
            [self checkTransactionStatus];
        }
            break;
    }
}

#pragma mark - UITableView datasource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 4;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell;
    static NSString *cellIdentifier = @"Cell";
    cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    switch (indexPath.row) {
        case PaymentMethodSMS:
            cell.textLabel.text = @"SMS charging";
            break;
        case PaymentMethodPhoneCard:
            cell.textLabel.text = @"Card charging";
            break;
        case PaymentMethodBanking:
            cell.textLabel.text = @"E-Banking charging";
            break;
        default:
            cell.textLabel.text = @"Check transaction status";
            break;
    }
    
    return cell;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

#pragma mark - UITableView delegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [self processAPIRequestForIndex:indexPath.row];
}

@end
