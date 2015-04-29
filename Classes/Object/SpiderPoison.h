//
//  SpiderPoison.h
//  CoolRun
//
//  Created by ManYou on 14/11/26.
//
//

#ifndef __CoolRun__SpiderPoison__
#define __CoolRun__SpiderPoison__

#include "Spider.h"

class SpiderPoison : public Spider
{
public:
    SpiderPoison();
    ~SpiderPoison();
    virtual bool init();
    CREATE_FUNC(SpiderPoison);
    
    virtual void loadJson(rapidjson::Value& value) override;
    virtual void saveData(string* buffer) override;
    
    virtual void setState(SpiderState state) override;
    virtual void dead() override;
    
    virtual void movementEvent(Armature *armature, MovementEventType movementType, const std::string& movementID) override;
    virtual void frameEvent(Bone *bone, const std::string& frameEventName, int originFrameIndex, int currentFrameIndex) override;
    
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
    
    void attack();
    void attackDone();
    
    void setAtkDirection(CRDirection direction);
    CRDirection getAtkDirection() { return m_atkDirection; }
private:
    bool b_isAtking;
    CRDirection m_atkDirection;
    Sprite* m_atkAlert;
};

#endif /* defined(__CoolRun__SpiderPoison__) */
