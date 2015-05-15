//
//  MYMultiLanguageManager.h
//  CoolRun
//
//  Created by ManYou on 15/5/13.
//
//

#ifndef __CoolRun__MYMultiLanguageManager__
#define __CoolRun__MYMultiLanguageManager__

#include "cocos2d.h"
#include "JsonHelp.h"

#define MULTI_LANGUAGE_ENGLISH "EN"
#define MULTI_LANGUAGE_CHINESE "CH"

USING_NS_CC;
using namespace std;

class MYMultiLanguageManager : public Ref
{
public:
    enum class MultiLanguageType
    {
        ENGLISH,
        CHINESE,
    };
    static MYMultiLanguageManager* getInstance();
    static void purgeInstance();
    
    bool init();
    const string getText(const char* key);
private:
    const string getLanguageKey(MultiLanguageType type);
private:
    MYMultiLanguageManager();
    ~MYMultiLanguageManager();
    
    static MYMultiLanguageManager* m_instance;
    static rapidjson::Document* m_doc;
};

#endif /* defined(__CoolRun__MYMultiLanguageManager__) */
