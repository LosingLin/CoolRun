//
//  MenuScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-3.
//
//

#include "MenuScene.h"
#include "MYScene.h"
#include "CoolRunScene.h"
#include "VillageScene.h"
#include "EditorScene.h"
#include "FreshGuideScene.h"
#include "Mission.h"
#include "ActionHelp.h"
#include "Leaves.h"
#include "SceneHelp.h"
#include "BackgroundAudio.h"
#include "AudioHelp.h"
//test
#include "editor-support/cocostudio/CocoStudio.h"
#include "Home.h"
#include "MYMultiLanguageManager.h"
using namespace cocostudio;


MenuLayer::MenuLayer()
: Layer()
, m_logo(nullptr)
, m_menu(nullptr)
, m_home(nullptr)
{
}
MenuLayer::~MenuLayer()
{
    AudioHelp::unloadMenuEft();
}

Scene* MenuLayer::createScene()
{
    auto _scene = MYScene::create();
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
    
    AudioHelp::preloadMenuEft();
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("tempRes.plist");
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("runner.plist");
    //Director::getInstance()->getTextureCache()->addImage("bg001.png");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //auto _bg = Sprite::create("bg001.png");
    //_bg->setAnchorPoint(Vec2::ZERO);
    //_bg->setPosition(Vec2(origin.x, origin.y));
    //this->addChild(_bg);
    
    m_menu = Node::create();
    m_menu->setPosition(Vec2(origin.x, origin.y - 600));
    this->addChild(m_menu, 100);
    
    auto banner = Sprite::createWithSpriteFrameName("banner_tree.png");
    banner->setAnchorPoint(Vec2(0.5, 0));
    banner->setPosition(Vec2(origin.x + visibleSize.width - 210, origin.y - 200));
    m_menu->addChild(banner, 10);
    
    auto _startBtn = MYButton::createWithFrameName("btn_start.png", "btn_start_hl.png");
    _startBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::startCallback, this));
    _startBtn->setPosition(Vec2(origin.x + visibleSize.width - 260, origin.y + 20));
    m_menu->addChild(_startBtn, 10);
    
    auto _chapterBtn = MYButton::createWithFrameName("btn_editor.png", "btn_editor_hl.png");
    _chapterBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::editorCallback, this));
    _chapterBtn->setPosition(Vec2(origin.x + visibleSize.width - 260, origin.y + 220));
    m_menu->addChild(_chapterBtn, 10);
    
    auto _settingBtn = MYButton::createWithFrameName("btn_setting.png", "btn_setting_hl.png");
    _settingBtn->addTouchEventListener(CC_CALLBACK_2(MenuLayer::settingCallback, this));
    _settingBtn->setPosition(Vec2(origin.x + visibleSize.width - 260, origin.y + 320));
    m_menu->addChild(_settingBtn, 10);
    
//    auto _sp = Sprite::createWithSpriteFrameName("runner_01.png");
//    _sp->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
//    this->addChild(_sp);
//    
//    _sp->runAction(ActionHelp::createFrameAction("runner_%02d.png", 1, 8, 0.1, true));
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("runner_bone.plist");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("Runner.ExportJson");
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("spider_bone.plist");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("SpiderPoison.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("SpiderKind.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("SpiderSpine.ExportJson");
    ArmatureDataManager::getInstance()->addArmatureFileInfo("SpiderFly.ExportJson");
    
    
    
    
//    auto armature = Armature::create("Runner");
//    armature->getAnimation()->play("walk", 0, 1);
    //armature->setScale(0.6f);
//    Bone* leftSword = armature->getBone("右手");
    //leftSword->addDisplay(_enemy, 2);
//    leftSword->setOpacity(0);
//    leftSword->setScale(2);
    //leftSword->setColor(Color3B::BLACK);
//    leftSword->setVisible(false);
//    leftSword->setOpacityModifyRGB(true);
//    leftSword->setRotation(-90);
//    armature->setPosition(Vec2(origin.x + visibleSize.width/2 - 200, origin.y + visibleSize.height/2));
//    this->addChild(armature, 20, 111);
    
    
    m_home = Home::create();
    //home->setPosition(Vec2(origin.x, origin.y-160));
    //home->setScale(0.8f);
    //m_home->setAnchorPoint(Vec2(0.1, 0.1));
    this->addChild(m_home);
    
    m_logo = Sprite::createWithSpriteFrameName("logo.png");
    m_logo->setAnchorPoint(Vec2(0.5, 0));
    m_logo->setPosition(Vec2(origin.x + visibleSize.width/2 - 130, origin.y + visibleSize.height));
    this->addChild(m_logo, 100);
    
    
    auto leaves = Leaves::create();
    this->addChild(leaves, 90);
    
    auto bga = BackgroundAudio::create();
    bga->setBGAType(BackgroundAudio::BGAType::NIGHT);
    this->addChild(bga);
    
    log("test ml key1 = %s", MYMultiLanguageManager::getInstance()->getText("key1").c_str());
    log("test ml key2 = %s", MYMultiLanguageManager::getInstance()->getText("key2").c_str());
    
    return true;
}


void MenuLayer::onEnter()
{
    Layer::onEnter();
    
    auto _scaleTo = ScaleTo::create(0.3, 1.2f);
    m_home->runAction(_scaleTo);
    
    auto _moveBy = MoveBy::create(0.3, Vec2(0, -420));
    m_logo->runAction(_moveBy);
    
    auto _moveBy02 = MoveBy::create(0.3, Vec2(0, 600));
    m_menu->runAction(_moveBy02);
}


void MenuLayer::start()
{
    auto mission = Mission::create("{\"s\":{\"num\":1}, \"e\":{\"num\":0}, \"n\":{\"num\":0}, \"h\":{\"num\":0}}");
    mission->setMissionRepeatModel(Mission::MissionRepeatModel::LAST);
    auto _scene = CoolRun::createScene(mission);
    SceneHelp::replaceScene(_scene);
}

#pragma mark - btn callback

void MenuLayer::startCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    if (_type == MYButton::TouchEventType::ENDED)
    {
        auto _scaleTo = ScaleTo::create(0.3, 1.0f);
        m_home->runAction(_scaleTo);
        auto _moveBy02 = MoveBy::create(0.3, Vec2(0, 420));
        m_logo->runAction(_moveBy02);
        auto _moveBy = MoveBy::create(0.3, Vec2(0, -600));
        auto _call = CallFunc::create(CC_CALLBACK_0(MenuLayer::start, this));
        m_menu->runAction(Sequence::create(_moveBy, _call, NULL));
    }
    
}
void MenuLayer::editorCallback(Ref* _ref, MYButton::TouchEventType _type)
{
    
//    auto _scene = VillageLayer::createScene();
//    Director::getInstance()->replaceScene(_scene);
    
    if (_type == MYButton::TouchEventType::ENDED)
    {
        auto _scene = EditorScene::createScene();
        SceneHelp::replaceScene(_scene);
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
        auto _layer = FreshGuideLayer::create();
        this->addChild(_layer);
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
