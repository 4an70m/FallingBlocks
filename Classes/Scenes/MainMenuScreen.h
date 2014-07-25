#ifndef __MAIN_MENU_SCREEN_H__
#define __MAIN_MENU_SCREEN_H__
#define TO_PLAY_SCENE_TRANSITION_TIME 1.0f

#include "cocos2d.h"
#include "Defenitions.h"
#include "Blocks.h"

class MainMenuScreen : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenuScreen);

    //functions of the main menu
    void Play(cocos2d::Ref *pSender);

    void generateBox(float dt);
private:
    cocos2d::Size visibleSize;
};

#endif // __MAIN_MENU_SCREEN_H__
