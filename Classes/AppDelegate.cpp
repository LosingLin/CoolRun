#include "AppDelegate.h"
#include "MenuScene.h"
#include "MYScene.h"
#include "CoolRunScene.h"
#include "AudioHelp.h"
#include "LogoScene.h"
#include "MobClickCpp.h"
#include "Vungle.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
    umeng::MobClickCpp::end();
    AudioHelp::endAudio();
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        //glview = GLViewImpl::create("My Game");
        glview = GLView::create("松树林");
        director->setOpenGLView(glview);
    }
    
    
    auto frameSize = glview->getFrameSize();
    
    auto designSize = Size(1136, 960);
    //auto designSize = Size(1636, 960);
    
    auto scaleX = (float)designSize.width / frameSize.width;
    auto scaleY = (float)designSize.height / frameSize.height;
    
    
    auto scale = 1.0f;
    if (scaleX > scaleY)
    {
        scale = scaleY;
    }
    else
    {
        scale = scaleX;
    }
    
    log("frameSize(%f, %f)", frameSize.width, frameSize.height);
    log("DesignResolutionSize(%f, %f)", frameSize.width * scale, frameSize.height * scale);
    
    director->getOpenGLView()->setDesignResolutionSize(frameSize.width * scale, frameSize.height * scale,
                                                       ResolutionPolicy::NO_BORDER);
    

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    
    FileUtils::getInstance()->addSearchPath("Image");
    FileUtils::getInstance()->addSearchPath("Json");
    FileUtils::getInstance()->addSearchPath("CocosStudio");
    FileUtils::getInstance()->addSearchPath("Particle");
    FileUtils::getInstance()->addSearchPath("fonts");
    FileUtils::getInstance()->addSearchPath("Music");
    //FileUtils::getInstance()->addSearchPath("./D_Editor");
    
    std::vector<std::string> paths =  FileUtils::getInstance()->getSearchPaths();
//    for (const auto &_path : paths) {
//        log("path : %s\n", _path.c_str());
//    }
    
    MOBCLICKCPP_START_WITH_APPKEY("557a957c67e58e419c0038e1");
    VungleStart();
    
    AudioHelp::preloadAppEft();

    // create a scene. it's an autorelease object
    //auto scene = CoolRun::createScene();
    Scene* scene = nullptr;
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    scene = MenuLayer::createScene();
#else
    scene = LogoLayer::createScene();
#endif
    
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    //Director::getInstance()->stopAnimation();
    
    umeng::MobClickCpp::applicationDidEnterBackground();
    
    if (!Director::getInstance()->isPaused())
    {
        auto coolRun = dynamic_cast<MYScene*>(Director::getInstance()->getRunningScene());
        if (coolRun)
        {
            coolRun->pause();
        }
    }
    
    //AudioHelp::pauseAllEft();
    AudioHelp::pauseBgA();
    
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    //Director::getInstance()->startAnimation();
    
    umeng::MobClickCpp::applicationWillEnterForeground();
    
//    auto coolRun = dynamic_cast<MYScene*>(Director::getInstance()->getRunningScene());
//    if (coolRun)
//    {
//        coolRun->pause();
//    }
    
    //AudioHelp::resumeAllEft();
    AudioHelp::resumeBgA();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
