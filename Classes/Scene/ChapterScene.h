//
//  ChapterScene.h
//  CoolRun
//
//  Created by ManYou on 14-9-4.
//
//

#ifndef __CoolRun__ChapterScene__
#define __CoolRun__ChapterScene__

#include "cocos2d.h"

USING_NS_CC;

class ChapterLayer : public Layer
{
public:
    ChapterLayer();
    ~ChapterLayer();
    
    virtual bool init();
    CREATE_FUNC(ChapterLayer);
    
    static Scene* createScene();
    
};

#endif /* defined(__CoolRun__ChapterScene__) */
