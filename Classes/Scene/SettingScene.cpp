//
//  SettingScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#include "SettingScene.h"


SettingLayer::SettingLayer()
: Layer()
{
}
SettingLayer::~SettingLayer()
{
}

bool SettingLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}

Scene* SettingLayer::createScene()
{
    auto _scene = Scene::create();
    auto _layer = SettingLayer::create();
    _scene->addChild(_layer);
    return _scene;
}