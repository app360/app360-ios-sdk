//
//  MOGPaymentResponseObject.h
//  App360SDK
//
//  Created by Tran Manh Tuan on 1/27/15.
//  Copyright (c) 2015 Mwork. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MOGPaymentResponseObject : NSObject

/*!
 @abstract Response code (Success or failure)
 */
@property (nonatomic, assign) MOGAPICode code;

/*!
 @abstract Details infomation for each request
 */
@property (nonatomic, strong) id details;

/*!
 @abstract Id of the transaction
 */
@property (nonatomic, strong) NSString *transactionId;

/*!
 @abstract Payload string that send with charging request
 */
@property (nonatomic, strong) NSString *payload;

/*!
 @abstract Status of transaction
 
 @see MOGTransactionStatus
 */
@property (nonatomic, assign) MOGTransactionStatus status;

/*!
 @abstract Transaction type (SMS/Phone card/E-banking)
 
 @see MOGTransactionType
 */
@property (nonatomic, assign) MOGTransactionType type;

/*!
 @abstract Description for error code
 */
@property (nonatomic, strong) NSString *message;

/**
 *  Initiallize method
 *
 *  @param JSON json string from response
 *
 */
- (instancetype)initWithJSON:(id)JSON;

@end
