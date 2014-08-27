#include "PauseOverlay.h"
#include "MainMenuScreen.h"

USING_NS_CC;

Scene* PauseOverlay::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseOverlay::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseOverlay::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "SplashScreen" splash screen"
    auto sprite = Sprite::create(GAME_SCENE_BACKGROUND);

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    auto label = Label::createWithBMFont("fonts/west_england-64.fnt", "Pause",TextHAlignment::LEFT, visibleSize.width/ 5);
    label->setHeight(visibleSize.height/10);
    label->setPosition(Point((visibleSize.width / 2) , (visibleSize.height / 4 * 3)));
	this->addChild(label, BUTTONS_ZORDER);

    // add the sprite as a child to this layer
    this->addChild(sprite, BACKGROUND_ZORDER);

    return true;
}

void PauseOverlay::ToMainMenu(float dt)
{
	auto sceneMainMenu = MainMenuScreen::createScene();

	//transition to main menu
	Director::getInstance()->replaceScene(TransitionFade::create(SPLASH_SCREEN_TRANSITION_LENGTH, sceneMainMenu));
}

void PauseOverlay::menuCloseCallback(Ref* pSender)
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
