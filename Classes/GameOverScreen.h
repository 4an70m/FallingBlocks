#ifndef __GAME_OVER_SCREEN_H__
#define __GAME_OVER_SCREEN_H__
#define TRANSITION_TIME 1.0f

#include "cocos2d.h"

class GameOverScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScreen);

    void returnToMainMenu(float dt);
};

#endif // __GAME_OVER_SCREEN_H__
