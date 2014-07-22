#include "MainMenuScreen.h"
#include "GameScreen.h"
#include "HighscoresScreen.h"

USING_NS_CC;

Scene* MainMenuScreen::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScreen::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScreen::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add "MainMenuScreen" splash screen"
    auto sprite = Sprite::create("Backgrounds/main_menu_background.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);

    //main menu items
    auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(MainMenuScreen::Play, this));
    auto menu_item_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(MainMenuScreen::Highscores, this));
    auto menu_item_3 = MenuItemFont::create("Mute", CC_CALLBACK_1(MainMenuScreen::Mute, this));
    auto menu_item_4 = MenuItemFont::create("Exit", CC_CALLBACK_1(MainMenuScreen::Exit, this));

    // simple main menu
    menu_item_1->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 4));
    menu_item_2->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 3));
    menu_item_3->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 2));
    menu_item_4->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 1));



    auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, NULL);
    menu->setPosition(Point(0, 0));
    this->addChild(menu);

    return true;
}

//implementation of menu functions

void MainMenuScreen::Play(Ref *pSender)
{
	auto scenePlay = GameScreen::createScene();

	//transition to play scene
	Director::getInstance()->replaceScene(TransitionFade::create(TO_PLAY_SCENE_TRANSITION_TIME, scenePlay));
}

void MainMenuScreen::Highscores(Ref *pSender)
{
	auto scenePlay = HighscoresScreen::createScene();

	//transition to highscores scene
	Director::getInstance()->pushScene(TransitionFade::create(TO_PLAY_SCENE_TRANSITION_TIME, scenePlay));
}

void MainMenuScreen::Mute(Ref *pSender)
{
	//no sound implementatin
}

void MainMenuScreen::Exit(Ref *pSender)
{
	Director::getInstance()->end();
	exit(0);
}

void MainMenuScreen::menuCloseCallback(Ref* pSender)
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
