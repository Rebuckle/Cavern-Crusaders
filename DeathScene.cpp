#include "DeathScene.h"
#include "SimpleAudioEngine.h"
#include "HelloWorldScene.h"
#include "MainMenuScene.h"

USING_NS_CC;

unsigned int score;


Scene* DeathScene::createScene(unsigned int tempScore)
{
	score = tempScore;
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
	cocos2d::Sprite* background;
	background = Sprite::create("menus/Death Screen No Buttons.png");
	background->setScale(1.05f);
	background->setPosition(Point(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(background, -1);

	auto menu_item_1 = MenuItemImage::create("menus/DEATH Play Again Button.png", "menus/DEATH Play Again Button Pressed.png", CC_CALLBACK_1(DeathScene::GameReturn, this));
	auto menu_item_2 = MenuItemImage::create("menus/DEATH Main Menu Button.png", "menus/DEATH Main Menu Button Pressed.png", CC_CALLBACK_1(DeathScene::MenuReturn, this));
	auto menu_item_3 = MenuItemImage::create("menus/DEATH Exit Game Button.png", "menus/DEATH Exit Game Button Pressed.png", CC_CALLBACK_1(DeathScene::ExitGame, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 10) * 6 + 50.0f));
	//menu_item_1->setScale(1.4f);
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 10) * 3.5));
	//menu_item_2->setScale(0.8f);
	menu_item_3->setPosition(Point((visibleSize.width / 2) + 6.0f, (visibleSize.height / 10) * 2.0 + 3.0f));
	//menu_item_3->setScale(0.8f);

	auto *menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, nullptr);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);

	//highscores
	UserDefault *def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey("HIGHSCORE", 0);

	if (score > highScore)
	{
		highScore = score;
		def->setIntegerForKey("HIGHSCORE", highScore);
	}

	def->flush();

	//score display
	__String *tempScore = __String::createWithFormat("%i", score);
	auto currentScore = LabelTTF::create( tempScore->getCString(), "fonts/8-bit pusab.ttf", 60);
	currentScore->setPosition(395.0f, 240.0f);
	currentScore->setScale(1.0f, 1.5f);
	currentScore->setColor(Color3B::BLACK);
	this->addChild(currentScore);

	__String *tempHighScore = __String::createWithFormat("%i", highScore);
	auto highScoreLabel = LabelTTF::create(tempHighScore->getCString(), "fonts/8-bit pusab.ttf", 60);
	highScoreLabel->setPosition(1525.0f, 240.0f);
	highScoreLabel->setScale(1.0f, 1.5f);
	highScoreLabel->setColor(Color3B::BLACK);
	this->addChild(highScoreLabel);

	//Losing sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/Game_Over_Theme.mp3");

	return true;
}

void DeathScene::GameReturn(Ref * pSender)
{
	CCLOG("New Game");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");

	//pauses game but returns to the same game
	auto scene = HelloWorld::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
	Director::getInstance()->pushScene(scene);
}

void DeathScene::MenuReturn(Ref * pSender)
{
	CCLOG("Return");

	//button sound
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sound/sound_ex_machina_Buttons+-+Stone+Button.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("Sound/02_01.mp3", true);

	//exit game and returns to the main menu
	Director::getInstance()->popScene();
	Director::getInstance()->popScene();
}

void DeathScene::ExitGame(Ref * pSender)
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

void DeathScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();
}
