//
//  MYKeyBoardLayer.h
//  CoolRun
//
//  Created by ManYou on 15/6/13.
//
//

#ifndef __CoolRun__MYKeyBoardLayer__
#define __CoolRun__MYKeyBoardLayer__

#include "MYLayer.h"

class MYKeyBoardLayer : public MYLayer
{
public:
    MYKeyBoardLayer();
    ~MYKeyBoardLayer();
    
    virtual bool init() override;
    CREATE_FUNC(MYKeyBoardLayer);
    
    void keyBoardCallback(EventKeyboard::KeyCode keyCode, Event* event);
    void showExitGameFrame();
};

#endif /* defined(__CoolRun__MYKeyBoardLayer__) */
