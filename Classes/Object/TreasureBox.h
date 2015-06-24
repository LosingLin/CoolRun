//
//  TreasureBox.h
//  CoolRun
//
//  Created by ManYou on 15/6/23.
//
//

#ifndef __CoolRun__TreasureBox__
#define __CoolRun__TreasureBox__

#include "Animal.h"

class TreasureBox : public Animal
{
public:
    TreasureBox();
    ~TreasureBox();
    
    virtual bool init() override;
    CREATE_FUNC(TreasureBox);
    
    virtual void trackCollideWithRunner(Runner* _runner) override;
    virtual void trackCollideWithBullet(Bullet* bullet) override;
};

#endif /* defined(__CoolRun__TreasureBox__) */
