#ifndef __SPLASH_SCREEN_H__
#define __SPLASH_SCREEN_H__

#include "cocos2d.h"
#include "Defenitions.h"

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
    void ToMainMenu(Ref *pSender);

    void FinishSplashScreen(float dt);

    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);


private:
    //sprites for cover pages
    cocos2d::Sprite *cover1;
    cocos2d::Sprite *cover2;
    cocos2d::Sprite *cover3;
    //and for splash screen
    cocos2d::Sprite *splashScreen;
    cocos2d::Menu *menu;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    int visibleCover;
};

#endif // __SPLASH_SCREEN_H__
