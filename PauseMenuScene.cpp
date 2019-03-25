#include "PauseMenuScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* PauseScene::createScene()
{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char * filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool PauseScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(PauseScene::menuCloseCallback, this));

	if (closeItem == nullptr ||
		closeItem->getContentSize().width <= 0 ||
		closeItem->getContentSize().height <= 0)
	{
		problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
	}
	else
	{
		float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	//Menu
	cocos2d::Sprite* background;
	background = Sprite::create("menus/Pause Screen No Buttons.png");
	background->setScale(1.05f);
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, -1);

	auto menu_item_1 = MenuItemImage::create("menus/PAUSE Continue Button.png", "menus/PAUSE Continue Button Pressed.png", CC_CALLBACK_1(PauseScene::GameReturn, this));
	auto menu_item_2 = MenuItemImage::create("menus/PAUSE Main Menu Button.png", "menus/PAUSE Main Menu Button Pressed.png", CC_CALLBACK_1(PauseScene::MenuReturn, this));
	auto menu_item_3 = MenuItemImage::create("menus/PAUSE Exit Game Button.png", "menus/PAUSE Exit Game Button Pressed.png", CC_CALLBACK_1(PauseScene::ExitGame, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 10) * 6));
	menu_item_1->setScale(1.4f);
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 10) * 3.5));
	menu_item_2->setScale(0.8f);
	menu_item_3->setPosition(Point((visibleSize.width / 2)+6.0f, (visibleSize.height / 10) * 2.0));
	menu_item_3->setScale(0.8f);

	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}

void PauseScene::GameReturn(Ref * pSender)
{
	CCLOG("Return");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/final_rush_music.mp3", true);

	//pauses game but returns to the same game
	Director::getInstance()->popScene();
}

void PauseScene::MenuReturn(Ref * pSender)
{
	CCLOG("Return");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/02_01.mp3", true);

	//exit game and returns to the main menu
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}

void PauseScene::ExitGame(Ref * pSender)
{
	CCLOG("Exit");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");

	//wait to exit for sound effect
	std::chrono::seconds duration(1);
	std::this_thread::sleep_for(duration);
	
	//exit the game and exit the program
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}

void PauseScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

