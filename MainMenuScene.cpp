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

	//background animation
	//https://gamedev.stackexchange.com/questions/82877/playing-a-sprite-sheet-animation-in-cocos2d-x
	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("Sprites/texture.plist");

	Sprite* someSprite = Sprite::createWithSpriteFrameName("frame0000.png");

	// load all the animation frames into an array
	Vector<SpriteFrame*> frames;
	for (int i = 0; i <= 8; i++)
	{
		std::stringstream ss;
		ss << "frame000" << i << ".png";
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		i++;
	}
	for (int i = 10; i <= 30; i++)
	{
		std::stringstream ss;
		ss << "frame00" << i << ".png";
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		i++;
	}

	// play the animation
	Animation* anim = Animation::createWithSpriteFrames(frames, 0.05f);
	someSprite->runAction(CCRepeatForever::create(Animate::create(anim)));
	someSprite->setPosition(visibleSize.width/2, visibleSize.height/2);
	someSprite->setScale(1.05);

	this->addChild(someSprite);

	//background music
	if (CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying() == false)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Sound/02_01.mp3");
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/02_01.mp3", true);
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}

	//preload button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");

	//Menu
	auto menu_item_1 = MenuItemImage::create("menus/MAIN Play Button.png", "menus/MAIN Play Button Pressed.png", CC_CALLBACK_1(MainScene::StartGame, this));
	auto menu_item_2 = MenuItemImage::create("menus/MAIN How Button.png", "menus/MAIN How Button Pressed.png", CC_CALLBACK_1(MainScene::Instructions, this));
	auto menu_item_3 = MenuItemImage::create("menus/MAIN Exit Button.png", "menus/MAIN Exit Button Pressed.png", CC_CALLBACK_1(MainScene::ExitGame, this));

	menu_item_1->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 3));
	menu_item_2->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 2));
	menu_item_3->setPosition(Point((visibleSize.width / 4) * 3, (visibleSize.height / 5) * 1.3));

	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	return true;
}

void MainScene::StartGame(Ref * pSender)
{
	CCLOG("Begin");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");

	//stop music
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	//pauses game but returns in the same game
	auto scene = HelloWorld::createScene();
	Director::getInstance()->pushScene(scene);
}

void MainScene::Instructions(Ref * pSender)
{
	CCLOG("Instructions");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");

	//stop music
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();

	//pauses game but returns in the same game
	auto scene = InstructionScene::createScene();
	Director::getInstance()->pushScene(scene);
}


void MainScene::ExitGame(Ref * pSender)
{
	CCLOG("Exit");
	
	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");
	
	//wait to exit for sound effect
	std::chrono::seconds duration(1);
	std::this_thread::sleep_for(duration);

	//should restart game
	Director::getInstance()->popScene();
}

void MainScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}

