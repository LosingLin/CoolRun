//
//  EditorManager.h
//  CoolRun
//
//  Created by ManYou on 15/5/14.
//
//

#ifndef __CoolRun__EditorManager__
#define __CoolRun__EditorManager__

#include "cocos2d.h"

USING_NS_CC;

class EditorManager : public Ref
{
public:
    
    static EditorManager* getInstance();
    static void purgeInstance();
private:
    EditorManager();
    ~EditorManager();
    
    static EditorManager* m_instance;
};

#endif /* defined(__CoolRun__EditorManager__) */
