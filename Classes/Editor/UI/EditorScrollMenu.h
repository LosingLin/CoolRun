//
//  EditorScrollMenu.h
//  CoolRun
//
//  Created by ManYou on 15/1/28.
//
//

#ifndef __CoolRun__EditorScrollMenu__
#define __CoolRun__EditorScrollMenu__

#include "cocos2d.h"
#include "EditorNode.h"

class EditorMenu;
class EditorScrollMenu : public EditorNode
{
public:
    EditorScrollMenu();
    ~EditorScrollMenu();
    
    virtual bool init() override;
    CREATE_FUNC(EditorScrollMenu);
    
    void setMenu(EditorMenu* menu);
    EditorMenu* getMenu();
private:
    ScrollView* m_scrollView;
};

#endif /* defined(__CoolRun__EditorScrollMenu__) */
