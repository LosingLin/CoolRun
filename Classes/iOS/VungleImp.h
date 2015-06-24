//
//  VungleImp.h
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#import <Foundation/Foundation.h>
#import <VungleSDK/VungleSDK.h>

@interface VungleImp : NSObject <VungleSDKDelegate>
{
    VungleSDK* m_vungleSDK;
}
+ (VungleImp*)getInstance;
+ (void)purgeInstance;

- (void)startApp;
- (void)playAd;
- (bool)isCachedAdAvailable;

#pragma mark - VungleSDKDelegate
/**
 * if implemented, this will get called when the SDK is about to show an ad. This point
 * might be a good time to pause your game, and turn off any sound you might be playing.
 */
- (void)vungleSDKwillShowAd;

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
- (void)vungleSDKwillCloseAdWithViewInfo:(NSDictionary*)viewInfo willPresentProductSheet:(BOOL)willPresentProductSheet;

/**
 * if implemented, this will get called when the product sheet is about to be closed.
 */
- (void)vungleSDKwillCloseProductSheet:(id)productSheet;

/**
 * if implemented, this will get called when there is an ad cached and ready to be shown.
 */
- (void)vungleSDKhasCachedAdAvailable;

@end
