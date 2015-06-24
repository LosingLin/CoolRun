//
//  Vungle_Android.cpp
//  CoolRun
//
//  Created by ManYou on 15/6/14.
//
//

#include "Vungle.h"
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#include "cocos2d.h"
#include "AudioHelp.h"
#include "ThirdPartyManager.h"
#include "ReviveMenu.h"
#include "ResourceManager.h"


USING_NS_CC;

#define kInPineForestPackageName "org/cocos2dx/cpp/AppActivity"

extern "C" {
    JNIEXPORT void JNICALL
    Java_org_cocos2dx_cpp_AppActivity_VungleAndroidCallbackWillShowAd
    (JNIEnv * env, jobject obj)
    {
        //Log.e("MANYOU==", "Java_org_cocos2dx_cpp_AppActivity_VungleAndroidCallback_willShowAd");

    	ResourceManager::getInstance()->removeBigSource();

        Director::getInstance()->pause();
        AudioHelp::pauseAllEft();
        AudioHelp::pauseBgA();
        
        auto menu = ThirdPartyManager::getInstance()->getReviveMenu();
        if (menu)
        {
            menu->AdLoadingDone(false);
        }
    };
    
    JNIEXPORT void JNICALL
    Java_org_cocos2dx_cpp_AppActivity_VungleAndroidCallbackWillCloseAd
    (JNIEnv * env, jobject obj)
    {
        //Log.e("MANYOU==", "Java_org_cocos2dx_cpp_AppActivity_VungleAndroidCallback_willCloseAd");

    	ResourceManager::getInstance()->addBigSource();

        Director::getInstance()->resume();
        AudioHelp::resumeAllEft();
        AudioHelp::resumeBgA();
        auto menu = ThirdPartyManager::getInstance()->getReviveMenu();
        if (menu)
        {
            menu->revive();
        }
    };
    JNIEXPORT void JNICALL
    Java_org_cocos2dx_cpp_AppActivity_VungleAndroidCallbackCancelShowAd
    (JNIEnv * env, jobject obj)
    {
//        auto menu = ThirdPartyManager::getInstance()->getReviveMenu();
//        if (menu)
//        {
//            menu->AdLoadingDone(true);
//        }
    };
};

#pragma mark -

jobject AppActivity(JniMethodInfo& minfo)
{
    bool isHave = JniHelper::getStaticMethodInfo(minfo,
                                                 kInPineForestPackageName,
                                                 "getJavaActivity",
                                                 "()Ljava/lang/Object;");
    jobject activityObj;
    if (isHave)
    {
        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
    }
    else
    {
        log("JNI::getJavaActivity is not exist!");
    }
    return activityObj;
}

void VungleStart()
{
    //Done in AppActivity onCreate();
}
void VunglePlayAd()
{
    JniMethodInfo minfo;
    jobject activityObj = AppActivity(minfo);
    
    bool isHave = JniHelper::getMethodInfo(minfo,
                                      kInPineForestPackageName,
                                      "playVungleAd",
                                      "()V");
    if (isHave)
    {
        minfo.env->CallVoidMethod(activityObj, minfo.methodID);
    }
    else
    {
        log("JNI::playVungleAd is not exist!");
    }
}
bool VungleIsCachedAdAvailable()
{
    JniMethodInfo minfo;
    jobject activityObj = AppActivity(minfo);
    
    bool isHave = JniHelper::getMethodInfo(minfo,
                                           kInPineForestPackageName,
                                           "isVungleAdPlayable",
                                           "()Z");
    bool isAvailable = false;
    if (isHave)
    {
         jboolean result = minfo.env->CallBooleanMethod(activityObj, minfo.methodID);
         isAvailable = result;
    }
    else
    {
        log("JNI::playVungleAd is not exist!");
    }
    return isAvailable;
}

void VungleCallback_willShowAd()
{
    
}
void VungleCallback_willCloseAd()
{
    
}



