//
//  SceneHelp.cpp
//  CoolRun
//
//  Created by ManYou on 15/5/5.
//
//

#include "SceneHelp.h"
#include "AudioHelp.h"

void SceneHelp::replaceScene(Scene* _sc)
{
    AudioHelp::stopAllEft();
    //AudioHelp::endAudio();
    Director::getInstance()->replaceScene(_sc);
}