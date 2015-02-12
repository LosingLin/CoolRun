//
//  ActionHelp.h
//  CoolRun
//
//  Created by ManYou on 14-9-13.
//
//

#ifndef __CoolRun__ActionHelp__
#define __CoolRun__ActionHelp__

#include "cocos2d.h"

using namespace std;
USING_NS_CC;

namespace ActionHelp {
  
    ActionInterval* createFrameAction(const string& format, int from, int to, float delay, bool isRepeat = true);
};

#endif /* defined(__CoolRun__ActionHelp__) */
