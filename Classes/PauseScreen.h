#ifndef __PAUSE_SCREEN_H__
#define __PAUSE_SCREEN_H__
#define TRANSITION_TIME 1.0f

#include "cocos2d.h"

class PauseScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(PauseScreen);

    void Back(cocos2d::Ref *pSender);
    void toMainMenu(cocos2d::Ref *pScene);
};

#endif // __PAUSE_SCREEN_H__
