//
//  Mission.h
//  CoolRun
//
//  Created by ManYou on 14-8-20.
//
//

#ifndef __CoolRun__Mission__
#define __CoolRun__Mission__

#include "cocos2d.h"
#include "MissionPage.h"
#include "JsonHelp.h"

using namespace std;
USING_NS_CC;
class Mission : public Ref
{
public:
    enum class MissionRepeatModel
    {
        LAST,
        ALL,
    };
    
    Mission();
    ~Mission();
    virtual bool init();
    CREATE_FUNC(Mission);
    
    static Mission* create(const std::string& filename, MissionRepeatModel model);
    static Mission* create(const std::string& jsonStr);
    static Mission* createWithDataStr(const std::string& data);
    
    int getMissionPageCount();
    MissionPage* getMissionPage(int _index);
    MissionPage* getNextMissionPage();
    
    void setPageIndex(int _index) { m_pageIndex = _index; }
    int getPageIndex() { return m_pageIndex; }
    
    const string* getDataStr() { return m_jsonStr; }
    
    void setMissionRepeatModel(MissionRepeatModel model) { m_repeatModel = model; }
    
    string getRandomMissionData(const string& path, const string& format, int num);
private:
    void setJsonStr(const string& str);
private:
    MissionRepeatModel m_repeatModel;
    string* m_jsonStr;
    int m_pageIndex;
};

#endif /* defined(__CoolRun__Mission__) */
