//
//  MYButton.h
//  CoolRun
//
//  Created by ManYou on 14-8-25.
//
//

#ifndef __CoolRun__MYButton__
#define __CoolRun__MYButton__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

class MYButton : public Node
{
public:
    enum class TouchEventType
    {
        BEGAN,
        MOVED,
        ENDED,
        CANCELED
    };
    
    enum class MYButtonType
    {
        ONEBYONE,
        ALLATONCE
    };
    
    typedef std::function<void(Ref*, MYButton::TouchEventType)> MYButtonCallback;
    
    MYButton();
    ~MYButton();
    CREATE_FUNC(MYButton);
    static MYButton* create(const string& _normal, const string& _highLight = "", const string& _disable = "");
    static MYButton* createWithFrameName(const string& _normal, const string& _highLight = "", const string& _disable = "");
    static MYButton* createWithContentSize(const Size& _size);
    virtual bool init();
    
    void setNormalSprite(Sprite* _sp);
    void setHighLightSprite(Sprite* _sp);
    void setDisableSprite(Sprite* _sp);
    
    virtual void setOpacity(GLubyte opacity) override;
    
    void setTouchEnabled(bool enable, MYButtonType _type = MYButtonType::ONEBYONE);
    
    void addTouchEventListener(MYButtonCallback callback);
    
    virtual bool onTouchBegan(Touch *touch, Event *unusedEvent);
    virtual void onTouchMoved(Touch *touch, Event *unusedEvent);
    virtual void onTouchEnded(Touch *touch, Event *unusedEvent);
    virtual void onTouchCancelled(Touch *touch, Event *unusedEvent);

    virtual void onTouchesBegan(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesMoved(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesEnded(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    virtual void onTouchesCancelled(const std::vector<cocos2d::Touch*>& touches, cocos2d::Event *event);
    
protected:
    void displaySprites();
    bool isTouchInContent(Touch *touch);
private:
    Sprite* m_normalSp;
    Sprite* m_highLightSp;
    Sprite* m_disableSp;
    MYButtonCallback m_callback;
    bool b_isEnable;
    
    MYButtonType m_touchType;
    EventListenerTouchOneByOne* m_touchListener;
    EventListenerTouchAllAtOnce* m_allTouchListener;
};

#endif /* defined(__CoolRun__MYButton__) */
