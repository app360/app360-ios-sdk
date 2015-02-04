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
        case MOGTransactionStatusProcessing:
            return @"processing";
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
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)makeSMSTransaction {
    
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK getSMSSyntaxWithAmount:MOGAmountAll
                                  payload:payload
                                    block:^(MOGSMSResponseObject *responseObject, NSError *error) {
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

- (void)makePhoneCardTransaction {
    
    MOGVendor vendor = MOGVendorViettel;
    NSString *cardCode = @"enter-pin-number-of-phone-card";
    NSString *cardSerial = @"enter-serial-number-of-phone-card";
    
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK makePhoneCardTransactionWithVendor:vendor
                                             cardCode:cardCode
                                           cardSerial:cardSerial
                                              payload:payload
                                                block:^(MOGCardResponseObject *responseObject, NSError *error) {
        
        if (error) {
            //API request failed
            
        } else if (responseObject.code == MOGAPICodeError){
            //API response 200 OK but something wrong
            
        } else {
            //success
            NSString *transactionId  = responseObject.transactionId;
            MOGTransactionType type = responseObject.type; //It should be MOGTransactionTypeSMS
            MOGTransactionStatus status = responseObject.status; //It should be MOGTransactionStatusBegin, means server just create transaction but not receive sms
            
            NSLog(@"Card transaction: %@, type: %@, status: %@", transactionId, NSStringFromType(type), NSStringFromStatus(status));
        }
    }];
}

- (void)makeBankingTransaction {
    
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

#pragma mark - UITableView datasource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 3; //3 payment method
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
            cell.textLabel.text = @"Charge via SMS";
            break;
        case PaymentMethodPhoneCard:
            cell.textLabel.text = @"Charge via phone card";
            break;
        case PaymentMethodBanking:
            cell.textLabel.text = @"Charge via E-Banking";
            break;
        default:
            break;
    }
    
    return cell;
}

#pragma mark - UITableView delegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.row) {
        case PaymentMethodSMS:
        {
            [self makeSMSTransaction];
            break;
        }
        case PaymentMethodPhoneCard:
        {
            [self makePhoneCardTransaction];
            break;
        }
        case PaymentMethodBanking:
        {
            [self makeBankingTransaction];
            break;
        }
        default:
            break;
    }
}

@end
