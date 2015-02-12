//
//  EditorItemMenu.h
//  CoolRun
//
//  Created by ManYou on 15/1/29.
//
//

#ifndef __CoolRun__EditorItemMenu__
#define __CoolRun__EditorItemMenu__

#include "EditorMenu.h"

class EditorItemMenu : public EditorMenu
{
public:
    EditorItemMenu();
    ~EditorItemMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorItemMenu);
    
    void menuCallback(int index);
    
    virtual void spaceCallback() override;
private:
    
};

#endif /* defined(__CoolRun__EditorItemMenu__) */
