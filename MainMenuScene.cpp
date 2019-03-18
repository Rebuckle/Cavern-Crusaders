#include "MainMenuScene.h"
#include "InstructionScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MainScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char * filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool MainScene::init()
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
		CC_CALLBACK_1(MainScene::menuCloseCallback, this));

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
	auto menu_item_1 = MenuItemFont::create("Start", CC_CALLBACK_1(MainScene::StartGame, this));
	auto menu_item_2 = MenuItemFont::create("Instructions", CC_CALLBACK_1(MainScene::Instructions, this));
	auto menu_item_3 = MenuItemFont::create("Exit", CC_CALLBACK_1(MainScene::ExitGame, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2));

	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}

void MainScene::StartGame(Ref * pSender)
{
	CCLOG("Begin");

	//pauses game but returns in the same game
	auto scene = HelloWorld::createScene();
	Director::getInstance()->pushScene(scene);
}

void MainScene::Instructions(Ref * pSender)
{
	CCLOG("Instructions");

	//pauses game but returns in the same game
	auto scene = InstructionScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void MainScene::ExitGame(Ref * pSender)
{
	CCLOG("Exit");

	//should restart game
	Director::getInstance()->popScene();
}

void MainScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

