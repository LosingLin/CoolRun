//
//  Villager.h
//  CoolRun
//
//  Created by ManYou on 14-9-5.
//
//

#ifndef __CoolRun__Villager__
#define __CoolRun__Villager__

#include "cocos2d.h"
#include "MYButton.h"

using namespace std;
USING_NS_CC;

class Dialog;
class Villager : public Node
{
public:
    Villager();
    ~Villager();
    virtual bool init();
    CREATE_FUNC(Villager);
    void init(const string& _frameName, const string& _words);
    static Villager* createWithFrameName(const string& _frameName, const string& _words);
    
    void addTouchCallback(MYButton::MYButtonCallback _callback);
    
    void talk();
protected:
    void talkOver(Dialog* _dlg);
private:
    MYButton* m_touchBtn;
    Sprite* m_villagerSp;
    string* m_words;
};

#endif /* defined(__CoolRun__Villager__) */
