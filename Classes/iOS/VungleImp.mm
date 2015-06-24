//
//  VungleImp.m
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#import "VungleImp.h"
#import "Vungle.h"

@implementation VungleImp

static VungleImp* m_vungleImpInstance = nil;

+ (VungleImp*)getInstance
{
    if (!m_vungleImpInstance)
    {
        m_vungleImpInstance = [[VungleImp alloc] init];
    }
    
    return m_vungleImpInstance;
}
+ (void)purgeInstance
{
    if (m_vungleImpInstance)
    {
        [m_vungleImpInstance release];
    }
}

- (void)startApp
{
    NSString* appID = @"557c1892b2addf5a5a000077";
    m_vungleSDK = [VungleSDK sharedSDK];
    [m_vungleSDK startWithAppId:appID];
    [m_vungleSDK setDelegate:self];
    //[m_vungleSDK clearCache];
}
- (void)playAd
{
    UIViewController* uiviewctrl = [[[UIApplication sharedApplication] keyWindow] rootViewController];
    NSError* err = [[NSError alloc] init];
    BOOL isSuccess = [m_vungleSDK playAd:uiviewctrl error:&err];
    NSLog(@"isSuccess %d, %@", isSuccess, err);
}
- (bool)isCachedAdAvailable
{
    return [m_vungleSDK isCachedAdAvailable];
}

#pragma mark - VungleSDKDelegate
/**
 * if implemented, this will get called when the SDK is about to show an ad. This point
 * might be a good time to pause your game, and turn off any sound you might be playing.
 */
- (void)vungleSDKwillShowAd
{
    NSLog(@"=============>vungleSDKwillShowAd");
    
    VungleCallback_willShowAd();
}

/**
 * if implemented, this will get called when the SDK closes the ad view, but there might be
 * a product sheet that will be presented. This point might be a good place to resume your game
 * if there's no product sheet being presented. The viewInfo dictionary will contain the
 * following keys:
 * - "completedView": NSNumber representing a BOOL whether or not the video can be considered a
 *               full view.
 * - "playTime": NSNumber representing the time in seconds that the user watched the video.
 * - "didDownlaod": NSNumber representing a BOOL whether or not the user clicked the download
 *                  button.
 */
- (void)vungleSDKwillCloseAdWithViewInfo:(NSDictionary*)viewInfo willPresentProductSheet:(BOOL)willPresentProductSheet
{
    NSLog(@"=============>vungleSDKwillCloseAdWithViewInfo %d", willPresentProductSheet);
    
    if (!willPresentProductSheet)
    {
        VungleCallback_willCloseAd();
    }
    
}

/**
 * if implemented, this will get called when the product sheet is about to be closed.
 */
- (void)vungleSDKwillCloseProductSheet:(id)productSheet
{
    NSLog(@"=============>vungleSDKwillCloseProductSheet");
    
    VungleCallback_willCloseAd();
}

/**
 * if implemented, this will get called when there is an ad cached and ready to be shown.
 */
- (void)vungleSDKhasCachedAdAvailable
{
    NSLog(@"=============>vungleSDKhasCachedAdAvailable");
}

@end
