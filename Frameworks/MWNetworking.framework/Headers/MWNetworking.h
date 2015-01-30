//
//  MWNetworking.h
//  MWNetworking
//
//  Created by Tran Manh Tuan on 12/10/14.
//  Copyright (c) 2014 Mwork. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for MWNetworking.
FOUNDATION_EXPORT double MWNetworkingVersionNumber;

//! Project version string for MWNetworking.
FOUNDATION_EXPORT const unsigned char MWNetworkingVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <MWNetworking/PublicHeader.h>


#import <Foundation/Foundation.h>
#import <Availability.h>

#ifndef _MWNETWORKING_
#define _MWNETWORKING_

#import "MWURLRequestSerialization.h"
#import "MWURLResponseSerialization.h"
#import "MWSecurityPolicy.h"
#import "MWNetworkReachabilityManager.h"

#import "MWURLConnectionOperation.h"
#import "MWHTTPRequestOperation.h"
#import "MWHTTPRequestOperationManager.h"

#if ( ( defined(__MAC_OS_X_VERSION_MAX_ALLOWED) && __MAC_OS_X_VERSION_MAX_ALLOWED >= 1090) || \
( defined(__IPHONE_OS_VERSION_MAX_ALLOWED) && __IPHONE_OS_VERSION_MAX_ALLOWED >= 70000 ) )
#import "MWURLSessionManager.h"
#import "MWHTTPSessionManager.h"
#endif

#endif /* _MWNETWORKING_ */