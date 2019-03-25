#include "InstructionScene.h"
#include "SimpleAudioEngine.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* InstructionScene::createScene()
{
	auto scene = Scene::create();
	auto layer = InstructionScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char * filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool InstructionScene::init()
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
		CC_CALLBACK_1(InstructionScene::menuCloseCallback, this));

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
	auto menu_item_1 = MenuItemFont::create("Instructions", CC_CALLBACK_1(InstructionScene::Instructions, this));
	auto menu_item_2 = MenuItemFont::create("Return To The Main Menu", CC_CALLBACK_1(InstructionScene::MenuReturn, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));

	auto *menu = Menu::create(menu_item_1, menu_item_2, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}

void InstructionScene::Instructions(Ref * pSender)
{
	CCLOG("Instructions");
}

void InstructionScene::MenuReturn(Ref * pSender)
{
	CCLOG("Return To The Main Menu");
	
	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/02_01.mp3", true);

	Director::getInstance()->popScene();
}

void InstructionScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

