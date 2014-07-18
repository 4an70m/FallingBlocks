#ifndef __SPLASH_SCREEN_H__
#define __SPLASH_SCREEN_H__
#define SPLASH_SCREEN_TRANSITION_LENGTH 1.0f
#define SPLASH_SCREEN_APPEAR_TIME 1.0f

#include "cocos2d.h"

class SplashScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SplashScreen);

    // function for replacing splashscreen
    void ToMainMenu(float dt);
};

#endif // __SPLASH_SCREEN_H__
