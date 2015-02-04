//
//  MOGCardResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import "MOGPaymentResponseObject.h"

@interface MOGCardResponseObject : MOGPaymentResponseObject

/*!
 @abstract Service provider for this transaction
 */
@property (nonatomic, assign) MOGVendor vendor;

/*!
 @abstract PIN number of phone card use for this transaction
 */
@property (nonatomic, strong) NSString *cardCode;

/*!
 @abstract Serial number of phone card use for this transaction
 */
@property (nonatomic, strong) NSString *cardSerial;

@end
