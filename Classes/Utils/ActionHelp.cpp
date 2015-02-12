//
//  ActionHelp.cpp
//  CoolRun
//
//  Created by ManYou on 14-9-13.
//
//

#include "ActionHelp.h"


ActionInterval* ActionHelp::createFrameAction(const string& format, int from, int to, float delay, bool isRepeat)
{
    
    char name[80];
    auto tempArray = Vector<SpriteFrame*>();
    for (int i = from; ; ) {
        sprintf(name, format.c_str(), i);
        auto frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(name);
        tempArray.pushBack(frame);
        if (to >= from)
        {
            ++ i;
            if (i > to)
            {
                break;
            }
        }
        else
        {
            -- i;
            if (i < to)
            {
                break;
            }
        }
    }
    auto _animation = Animation::createWithSpriteFrames(tempArray, delay);
    if (isRepeat)
    {
        auto _action = RepeatForever::create(Animate::create(_animation));
        return _action;
    }
    else
    {
        return Animate::create(_animation);
    }
    
}