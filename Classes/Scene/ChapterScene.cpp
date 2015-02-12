//
//  ChapterScene.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-4.
//
//

#include "ChapterScene.h"


ChapterLayer::ChapterLayer()
: Layer()
{
}
ChapterLayer::~ChapterLayer()
{
}

bool ChapterLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }
    
    return true;
}

Scene* ChapterLayer::createScene()
{
    auto _scene = Scene::create();
    auto _layer = ChapterLayer::create();
    _scene->addChild(_layer);
    return _scene;
}