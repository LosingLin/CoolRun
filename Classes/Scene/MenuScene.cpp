//
//  MenuScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-3.
//
//

#include "MenuScene.h"
#include "CoolRunScene.h"
#include "VillageScene.h"
#include "EditorScene.h"
#include "Mission.h"
#include "ActionHelp.h"


//test
#include "editor-support/cocostudio/CocoStudio.h"
#include "Home.h"
using namespace cocostudio;


MenuLayer::MenuLayer()
: Layer()
{
}
MenuLayer::~MenuLayer()
{
}

Scene* MenuLayer::createScene()
{
    auto _scene = Scene::create();
    auto _layer = MenuLayer::create();
    _scene->addChild(_layer);
    return _scene;
}

bool MenuLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tempRes.plist");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("runner.plist");
    //Director::getInstance()->getTextureCache()->addImage("bg001.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //auto _bg = Sprite::create("bg001.png");
    //_bg->setAnchorPoint(Vec2::ZERO);
    //_bg->setPosition(Vec2(origin.x, origin.y));
    //this->addChild(_bg);
    
    auto banner = Sprite::createWithSpriteFrameName("banner_tree.png");
    banner->setAnchorPoint(Vec2(0.5, 0));
    banner->setPosition(Vec2(origin.x + visibleSize.width - 200, origin.y - 200));
    this->addChild(banner, 10);
    
    auto _startBtn = MYButton::createWithFrameName("btn_run.png", "btn_hl_run.png");
    _startBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::startCallback, this));
    _startBtn->setPosition(Vec2(origin.x + visibleSize.width - 260, origin.y + 20));
    this->addChild(_startBtn, 10);
    
    auto _chapterBtn = MYButton::createWithFrameName("btn_editor.png", "btn_hl_editor.png");
    _chapterBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::editorCallback, this));
    _chapterBtn->setPosition(Vec2(origin.x + visibleSize.width - 260, origin.y + 220));
    this->addChild(_chapterBtn, 10);
    
    auto _settingBtn = MYButton::createWithFrameName("btn_setting.png", "btn_hl_setting.png");
    _settingBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::settingCallback, this));
    _settingBtn->setPosition(Vec2(origin.x + visibleSize.width - 260, origin.y + 320));
    this->addChild(_settingBtn, 10);
    
//    auto _sp = Sprite::createWithSpriteFrameName("runner_01.png");
//    _sp->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
//    this->addChild(_sp);
//    
//    _sp->runAction(ActionHelp::createFrameAction("runner_%02d.png", 1, 8, 0.1, true));
    
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Runner0.png", "Runner0.plist", "Runner.ExportJson");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spider_bone.plist");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Spider.ExportJson");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Boss010.plist");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Boss01.ExportJson");
    
    
    
    auto armature = Armature::create("Runner");
    armature->getAnimation()->play("walk", 0, 1);
    //armature->setScale(0.6f);
    Bone* leftSword = armature->getBone("右手");
    //leftSword->addDisplay(_enemy, 2);
//    leftSword->setOpacity(0);
//    leftSword->setScale(2);
    //leftSword->setColor(Color3B::BLACK);
//    leftSword->setVisible(false);
//    leftSword->setOpacityModifyRGB(true);
//    leftSword->setRotation(-90);
    armature->setPosition(Vec2(origin.x + visibleSize.width/2 - 200, origin.y + visibleSize.height/2));
    this->addChild(armature, 20, 111);
    
    
    auto home = Home::create();
    this->addChild(home);
    
    
    return true;
}


#pragma mark - btn callback

void MenuLayer::startCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        auto mission = Mission::create("{\"e\":{\"num\":1}, \"n\":{\"num\":1}, \"h\":{\"num\":1}}");
        mission->setMissionRepeatModel(Mission::MissionRepeatModel::LAST);
        auto _scene = CoolRun::createScene(mission);
        Director::getInstance()->replaceScene(_scene);
    }
    
}
void MenuLayer::editorCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    
//    auto _scene = VillageLayer::createScene();
//    Director::getInstance()->replaceScene(_scene);
    
    if (_type == MYButton::TouchEventType::ENDED)
    {
        auto _scene = EditorScene::createScene();
        Director::getInstance()->replaceScene(_scene);
    }
}
void MenuLayer::settingCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    
//    Size visibleSize = Director::getInstance()->getVisibleSize();
//    Vec2 origin = Director::getInstance()->getVisibleOrigin();
//    
//    Armature* armature = dynamic_cast<Armature*>(this->getChildByTag(111));
//    armature->getAnimation()->play("walk_atk", 0, 0);
//    armature->getAnimation()->setMovementEventCallFunc(CC_CALLBACK_3(MenuLayer::movementEvent, this));
//    
//    armature->getAnimation()->setFrameEventCallFunc(CC_CALLBACK_4(MenuLayer::frameEvent, this));
//    armature->runAction(MoveBy::create(2, Vec2(300, 0)));
    
    
//    auto _sp = Sprite::createWithSpriteFrameName("attack.png");
//    _sp->setPosition(Vec2(origin.x + visibleSize.width/2 - 160, origin.y + visibleSize.height/2 + 40));
//    this->addChild(_sp, 20);
//    
//    _sp->runAction(RotateBy::create(0.2, 30));
    if (_type == MYButton::TouchEventType::ENDED)
    {

    }
}

void MenuLayer::movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID)
{
    if (movementType == MovementEventType::COMPLETE)
    {
        Armature* armature = dynamic_cast<Armature*>(this->getChildByTag(111));
        armature->getAnimation()->play("walk", 0, 1);
    }
    
}
void MenuLayer::frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex)
{
    if("atk_over" == frameEventName)
    {
        Armature* armature = dynamic_cast<Armature*>(this->getChildByTag(111));
        armature->getAnimation()->play("walk", 0, 1);
    }
    log("frameEvent   %d, %d", originFrameIndex, currentFrameIndex);
}
