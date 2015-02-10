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

@interface ViewController ()<
UITableViewDataSource, UITableViewDelegate,
MOGSMSChargingDataSource, MOGSMSChargingDelegate,
MOGCardChargingDataSource, MOGCardChargingDelegate,
MOGBankingChargingDataSource, MOGBankingChargingDelegate
>

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

- (void)showPaymentForm {
    [MOGPaymentSDK setSMSDelegate:self];
    [MOGPaymentSDK setSMSDatasource:self];
    
    [MOGPaymentSDK setCardDelegate:self];
    [MOGPaymentSDK setCardDatasource:self];
    
    [MOGPaymentSDK setBankingDatasource:self];
    [MOGPaymentSDK setBankingDelegate:self];
    
    [MOGPaymentSDK setIcon:[UIImage imageNamed:@"game-icon"]];
    [MOGPaymentSDK setDisplayName:@"Swing Copters"];
    [MOGPaymentSDK setDescription:@".Gear Studio"];
    
    [MOGPaymentSDK makeTransactionWithPayload:nil];
}

- (void)makeSMSTransaction {
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK makeSMSTransactionWithDelegate:self
                                       datasource:self
                                          payload:payload];
}

- (void)makePhoneCardTransaction {
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK makePhoneCardTransactionWithDelegate:self
                                             datasource:self
                                                payload:payload];
    
}

- (void)makeBankingTransaction {
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK makeBankingTransactionWithDelegate:self
                                           datasource:self
                                              payload:payload];
}

#pragma mark - Payment API
- (void)requestForSMS {
    //Set payload string. The addition infomation you want to send with transaction. such as id of user make this transaction
    //This payload string will send to callback URL (that configured on dashboard) when transaction finish successfully
    NSString *payload = @"gamer-id";
    
    [MOGPaymentSDK getSMSSyntaxWithSMSAmount:MOGSMSAmountAll
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

- (void)requestForPhoneCard {
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

//--------------------------------------------------------

#pragma mark - SMS Datasource

- (MOGSMSAmount)allowedSMSAmount {
    return MOGSMSAmountAll;
}

- (NSString *)smsExchangeDescriptionForAmount:(MOGSMSAmount)amount {
    switch (amount) {
        case MOGSMSAmount500:
            return @"50 coin";
        case MOGSMSAmount1000:
            return @"100 coin";
        case MOGSMSAmount2000:
            return @"200 coin";
        case MOGSMSAmount3000:
            return @"300 coin";
        case MOGSMSAmount4000:
            return @"400 coin";
        case MOGSMSAmount5000:
            return @"500 coin";
        case MOGSMSAmount10000:
            return @"1000 coin";
        case MOGSMSAmount15000:
            return @"1500 coin";
        default:
            break;
    }
    return nil;
}

#pragma mark - SMS Delegate
- (void)SMSTransactionDidFinishWithId:(NSString *)transactionId
                               syntax:(NSString *)syntax
                            recipient:(NSArray *)recipient
{
    
}

- (void)SMSTransactionDidFailedWithError:(NSError *)error
{
    
}

//--------------------------------------------------------

#pragma mark - Phone card charging datasource
- (NSUInteger)numberOfItemsForCardCharging {
    return 3;
}

- (NSUInteger)cardChargingAmountForIndex:(NSUInteger)index {
    switch (index) {
        case 0:
            return 10000;
        case 1:
            return 20000;
        case 2:
        default:
            return 50000;
    }
}

- (NSString *)cardExchangeDescriptionForIndex:(NSUInteger)index {
    switch (index) {
        case 0:
            return @"10 Coins";
        case 1:
            return @"20 Coins";
        case 2:
        default:
            return @"50 Coins";
    }
}

#pragma mark - Phone card charging delegate
- (void)cardTransactionFinishWithId:(NSString *)transactionId details:(NSDictionary *)details {
    
}

- (void)cardTransactionDidFailedWithError:(NSError *)error {
    
}

//--------------------------------------------------------

#pragma mark - Banking charging datasource
- (NSUInteger)numberOfItemsForBankingCharging
{
    return 5;
}

- (NSUInteger)bankingChargingAmountForIndex:(NSUInteger)index {
    switch (index) {
        case 0:
            return 50000;
        case 1:
            return 100000;
        case 2:
            return 200000;
        case 3:
            return 300000;
        case 4:
            return 500000;
    }
    return 0;
}

- (NSString *)bankingExchangeDescriptionForIndex:(NSUInteger)index
{
    switch (index) {
        case 0:
            return @"500 coin";
        case 1:
            return @"1000 coin";
        case 2:
            return @"2000 coin";
        case 3:
            return @"3000 coin";
        case 4:
            return @"5000 coin";
    }
    return nil;
}

#pragma mark - Banking charging delegate
- (void)bankingTransactionDidReceiveUrl:(NSURL *)url transactionId:(NSString *)transactionId {
    
}

- (void)bankingTransactionDidFailWithError:(NSError *)error {
    
}

//--------------------------------------------------------

#pragma mark - Handle UITableViewCell did selected
- (void)processQuickPaymentForm {
    [self showPaymentForm];
}

- (void)processPrebuildFormRequestForIndex:(NSInteger)index {
    switch (index) {
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
            break;
    }
}

#pragma mark - UITableView datasource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    if (section == 0) {
        return 1;
    } else {
        return 3;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell;
    static NSString *cellIdentifier = @"Cell";
    cell = [tableView dequeueReusableCellWithIdentifier:cellIdentifier];
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:cellIdentifier];
    }
    
    if (indexPath.section != 0) {
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
                break;
        }
    } else {
        cell.textLabel.text = @"Charging form";
    }
    
    return cell;
}

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 3;
}

#pragma mark - UITableView delegate
- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath
{
    return 44;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    switch (indexPath.section) {
        case 0:
            //Quick start
            [self processQuickPaymentForm];
            break;
        case 1:
            //Pre-build form
            [self processPrebuildFormRequestForIndex:indexPath.row];
            break;
        case 2:
        default:
            //API
            [self processAPIRequestForIndex:indexPath.row];
            break;
    }
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
    switch (section) {
        case 0:
            return @"Quickstart";
        case 1:
            return @"Pre-build form";
        case 2:
        default:
            return @"API";
    }
}

@end
