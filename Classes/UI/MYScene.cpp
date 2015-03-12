//
//  MYScene.cpp
//  CoolRun
//
//  Created by ManYou on 15/3/10.
//
//

#include "MYScene.h"

MYScene::MYScene()
: Scene()
, scenePause(nullptr)
, sceneResume(nullptr)
{
    
}
MYScene::~MYScene()
{
    
}

void MYScene::pause()
{
    if (scenePause)
    {
        scenePause();
    }
}
void MYScene::resume()
{
    if (sceneResume)
    {
        sceneResume();
    }
}