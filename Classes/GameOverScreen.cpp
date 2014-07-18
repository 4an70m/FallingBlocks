#include "GameOverScreen.h"
#include "MainMenuScreen.h"

USING_NS_CC;

Scene* GameOverScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "GameOver" splash screen"
    auto sprite = Sprite::create("Backgrounds/game_over_screen_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    //returns to the main menu in 3 seconds
    this->schedule(schedule_selector(GameOverScreen::returnToMainMenu), 3.0f);

    return true;
}

void GameOverScreen::returnToMainMenu(float dt)
{
	//test implementation of tap on the game over menu
	//to return to the main menu
	auto sceneMainMenu = MainMenuScreen::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,sceneMainMenu));
}

void GameOverScreen::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
