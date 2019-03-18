#include "DeathScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

Scene* DeathScene::createScene()
{
	auto scene = Scene::create();
	auto layer = DeathScene::create();
	scene->addChild(layer);
	return scene;
}

static void problemLoading(const char * filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

bool DeathScene::init()
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
		CC_CALLBACK_1(DeathScene::menuCloseCallback, this));

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
	auto menu_item_1 = MenuItemFont::create("Restart", CC_CALLBACK_1(DeathScene::GameReturn, this));
	auto menu_item_2 = MenuItemFont::create("Main Menu", CC_CALLBACK_1(DeathScene::MenuReturn, this));
	auto menu_item_3 = MenuItemFont::create("Exit", CC_CALLBACK_1(DeathScene::ExitGame, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2));

	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	//display score
	scoreCount = Label::createWithTTF("0", "fonts/8-bit pusab.ttf", 60);
	scoreCount->setColor(Color3B::GRAY);
	scoreCount->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - scoreCount->getContentSize().height - 80.0f));
	this->addChild(scoreCount, 2);

	__String * DisplayScore = __String::createWithFormat("%.0f", p_score);
	scoreCount->setString(DisplayScore->getCString());

	return true;
}

void DeathScene::GameReturn(Ref * pSender)
{
	CCLOG("New Game");

	//pauses game but returns to the same game
	auto scene = HelloWorld::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
}

void DeathScene::MenuReturn(Ref * pSender)
{
	CCLOG("Return");

	//exit game and returns to the main menu
	Director::getInstance()->popScene();
}

void DeathScene::ExitGame(Ref * pSender)
{
	CCLOG("Exit");

	//exit the game and exit the program
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}

void DeathScene::getScore(float score)
{
	p_score = score;
}

void DeathScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}
