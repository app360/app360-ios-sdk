//
//  MOGBankingResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "MOGPaymentResponseObject.h"

@interface MOGBankingResponseObject : MOGPaymentResponseObject

/*!
 * @abstract URL of charging web page for this transaction
 * User must pay via this web page to finish this transaction
 */
@property (nonatomic, strong) NSURL *payURL;

@end
