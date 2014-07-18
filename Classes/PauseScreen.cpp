#include "PauseScreen.h"
#include "MainMenuScreen.h"

USING_NS_CC;

Scene* PauseScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = PauseScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool PauseScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "PauseScreen" splash screen"
    auto sprite = Sprite::create("Backgrounds/pause_screen_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

	auto menu_item_1 = MenuItemFont::create("Back", CC_CALLBACK_1(PauseScreen::Back, this));
	auto menu_item_2 = MenuItemFont::create("Main Menu", CC_CALLBACK_1(PauseScreen::toMainMenu, this));

	menu_item_1->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 4) * 2));
	menu_item_2->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 4) * 3));

	auto *menu = Menu::create(menu_item_1, menu_item_2, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);


    return true;
}

void PauseScreen::Back(Ref *pSender)
{
	Director::getInstance()->popScene();
}

void PauseScreen::toMainMenu(Ref *pSender)
{
	auto sceneMainMenu = MainMenuScreen::createScene();

	Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME,sceneMainMenu));
}

void PauseScreen::menuCloseCallback(Ref* pSender)
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
