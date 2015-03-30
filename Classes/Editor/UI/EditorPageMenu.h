//
//  EditorPageMenu.h
//  CoolRun
//
//  Created by ManYou on 15/3/27.
//
//

#ifndef __CoolRun__EditorPageMenu__
#define __CoolRun__EditorPageMenu__

#include "EditorMenu.h"

class EditorPageMenu: public EditorMenu
{
public:
    EditorPageMenu();
    ~EditorPageMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorPageMenu);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    void menuCallback(int index);
    void deleteCallback(int index);
    
    virtual void spaceCallback() override;
    
    void updatePage();
private:
    bool b_isEditing;
};

#endif /* defined(__CoolRun__EditorPageMenu__) */
