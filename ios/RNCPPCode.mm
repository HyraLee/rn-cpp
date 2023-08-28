/**
 * Copyright (c) Facebook, Inc. and its affiliates.
 *
 * This source code is licensed under the MIT license found in the
 * LICENSE file in the root directory of this source tree.
 */

#import "RNCPPCode.h"

#pragma mark - RNCPPCode

@implementation RNCPPCode


RCT_EXPORT_MODULE();

+ (BOOL)requiresMainQueueSetup
{
  return NO;
}

RCT_EXPORT_METHOD(multiply:(nonnull NSNumber*)a withB:(nonnull NSNumber*)b resolver:(RCTPromiseResolveBlock)resolve
withReject:(RCTPromiseRejectBlock)reject)
{
    long result = v99core::multiply([a longValue], [b longValue]);

    resolve(@{
              @"result": @(result)
    });
}

RCT_EXPORT_METHOD(httpGet:(NSString *)url
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    @try {
        std::string urlStr = [url UTF8String]; // Convert NSString to std::string
        // const std::string caFilePath = [[[NSBundle mainBundle] pathForResource:@"cacert" ofType:@"pem"] UTF8String];
        std::string result = v99core::httpGet(urlStr);
        NSString *resultStr = [NSString stringWithUTF8String:result.c_str()]; // Convert std::string to NSString
        resolve(resultStr);
    } @catch (NSException *exception) {
        NSError *error = [[NSError alloc] initWithDomain:@"HTTP_GET_ERROR_DOMAIN" code:0 userInfo:@{NSLocalizedDescriptionKey: @"An error occurred during HTTP GET request"}];
        reject(@"HTTP_GET_ERROR", @"An error occurred during HTTP GET request", error);
    }
}

RCT_EXPORT_METHOD(httpPost:(NSString *)url
                  params:(NSString *)params
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    @try {
        std::string urlStr = [url UTF8String]; // Convert NSString to std::string
        std::string paramsStr = [params UTF8String]; // Convert NSString params to std::string
        // const std::string caFilePath = [[[NSBundle mainBundle] pathForResource:@"cacert" ofType:@"pem"] UTF8String];
        std::string result = v99core::httpPost(urlStr, paramsStr);
        NSString *resultStr = [NSString stringWithUTF8String:result.c_str()]; // Convert std::string to NSString
        resolve(resultStr);
    } @catch (NSException *exception) {
        NSError *error = [[NSError alloc] initWithDomain:@"HTTP_GET_ERROR_DOMAIN" code:0 userInfo:@{NSLocalizedDescriptionKey: @"An error occurred during HTTP GET request"}];
        reject(@"HTTP_GET_ERROR", @"An error occurred during HTTP GET request", error);
    }
}

RCT_EXPORT_METHOD(httpDelete:(NSString *)url
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    @try {
        std::string urlStr = [url UTF8String]; // Convert NSString to std::string
        // const std::string caFilePath = [[[NSBundle mainBundle] pathForResource:@"cacert" ofType:@"pem"] UTF8String];
        std::string result = v99core::httpDelete(urlStr);
        NSString *resultStr = [NSString stringWithUTF8String:result.c_str()]; // Convert std::string to NSString
        resolve(resultStr);
    } @catch (NSException *exception) {
        NSError *error = [[NSError alloc] initWithDomain:@"HTTP_GET_ERROR_DOMAIN" code:0 userInfo:@{NSLocalizedDescriptionKey: @"An error occurred during HTTP GET request"}];
        reject(@"HTTP_GET_ERROR", @"An error occurred during HTTP GET request", error);
    }
}

////////////////////////////////////////////////////
////////////     V99 CORE APP           ////////////
////////////////////////////////////////////////////

RCT_EXPORT_METHOD(getPlatform:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    @try {
        std::string urlStr = [url UTF8String]; // Convert NSString to std::string
        // const std::string caFilePath = [[[NSBundle mainBundle] pathForResource:@"cacert" ofType:@"pem"] UTF8String];
        std::string result = v99core::getPlatform();
        NSString *resultStr = [NSString stringWithUTF8String:result.c_str()]; // Convert std::string to NSString
        resolve(resultStr);
    } @catch (NSException *exception) {
        NSError *error = [[NSError alloc] initWithDomain:@"HTTP_GET_ERROR_DOMAIN" code:0 userInfo:@{NSLocalizedDescriptionKey: @"An error occurred during HTTP GET request"}];
        reject(@"HTTP_GET_ERROR", @"An error occurred during HTTP GET request", error);
    }
}

@end
