/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	//scene
	auto scene = Scene::createWithPhysics();
	//draws physics bodys for debug.
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//layer
	auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	//add layer as child to scene
	scene->addChild(layer);
	//return the scene
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::initWithPhysics() )
    {
        return false;
    }
	//Get Window Size
	size = Director::sharedDirector()->getInstance()->getWinSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    /////////////////////////////

	//Init the event handlers
	initListeners(); 
	initSprites();
	initObstacles();

	//edgenode for edge of screen collisons 
	auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
	auto edgeNode = Node::create();
	edgeNode->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	edgeNode->setPhysicsBody(edgeBody);

	//Add sprites to the scene
	this->addChild(background, -1);
	this->addChild(background2, -1);
	this->addChild(background3, -1);
	this->addChild(Miner,1);
	this->addChild(edgeNode, 2);
	

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();
	
	

   
    return true;
}

void HelloWorld::initListeners()
{
	//Init the keyboard listener
	initKeyboardListener();
}

void HelloWorld::initKeyboardListener()
{
	//Create the keyboard listener
	keyboardListener = EventListenerKeyboard::create();

	//Setting up callbacks
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::keyDownCallback, this);
	keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::keyUpCallback, this);

	//Add the keyboard listener to the dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HelloWorld::keyDownCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	if (keyCode == EventKeyboard::KeyCode::KEY_W)
		key_W = true;

	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		key_S = true;

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		key_A = true;

	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		key_D = true;

	////////////////////////////////////////////////////////////////////////////////////////////////////
}

void HelloWorld::keyUpCallback(EventKeyboard::KeyCode keyCode, Event* event)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////

	if (keyCode == EventKeyboard::KeyCode::KEY_W)
		key_W = false;

	else if (keyCode == EventKeyboard::KeyCode::KEY_S)
		key_S = false;

	else if (keyCode == EventKeyboard::KeyCode::KEY_A)
		key_A = false;

	else if (keyCode == EventKeyboard::KeyCode::KEY_D)
		key_D = false;

	////////////////////////////////////////////////////////////////////////////////////////////////////
}



void HelloWorld::update(float deltaTime)
{
	//update loop for items in the game.
	//Infinite Looping Background
	initBackground();
	
	//Updating the obstacles in the scene
	m_PlatformManager->update(deltaTime);
	m_RocksManager->Update(deltaTime);
	m_DebreeManager->Update(deltaTime);
	m_BatsManager->Update(deltaTime);
	m_FallingStonesManager->Update(deltaTime);
	m_SpikesManager->Update(deltaTime);

	/*MovingBats *myMovingBats = new MovingBats(cocos2d::Vec2(50, 50), 45.0f, 45.0f, 12, false, cocos2d::Vec2(50, 150), cocos2d::Vec2(50, 0), 10.0f);
	myMovingBats->update(deltaTime);*/
	
	
	// update the Miner's velocity
	if (key_W == true)
		MinerPhys->applyForce(Vec2(0, 200));
	if (key_S == true)
		MinerPhys->applyForce(Vec2(0, 0));
	if (key_A == true)
		MinerPhys->applyForce(Vec2(-100, 0));
	if (key_D == true)
		MinerPhys->applyForce(Vec2(100, 0));
		
}


void HelloWorld::initBackground()
{
	background->setPosition(background->getPositionX() - 5, background->getPositionY());
	background2->setPosition(background2->getPositionX() - 5, background2->getPositionY());
	background3->setPosition(background3->getPositionX() - 5, background3->getPositionY());
	if (background->getPositionX() < -background->boundingBox().size.width)
	{
		background->setPosition(background3->getPositionX() + background3->boundingBox().size.width, background->getPositionY());
	}
	if (background2->getPositionX() < -background2->boundingBox().size.width)
	{
		background2->setPosition(background->getPositionX() + background->boundingBox().size.width, background2->getPositionY());
	}
	if (background3->getPositionX() < -background3->boundingBox().size.width)
	{
		background3->setPosition(background2->getPositionX() + background2->boundingBox().size.width, background3->getPositionY());
	}
}

void HelloWorld::initSprites()
{
	MinerPhys = PhysicsBody::createBox(Size(110.0f, 125.0f), PhysicsMaterial(0.0f, 0.0f, 1.0f));
	MinerPhys->setDynamic(true);

	background = Sprite::create("CaveBack_Reference.jpg");
	background->setScale(7.0f);
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setPosition(0, this->boundingBox().getMinY());

	background2 = Sprite::create("CaveBack_Reference.jpg");
	background2->setScale(7.0f);
	background2->setAnchorPoint(Vec2(0.0f, 0.0f));
	background2->setPosition(background->boundingBox().size.width - 1, this->boundingBox().getMinY());

	background3 = Sprite::create("CaveBack_Reference.jpg");
	background3->setScale(7.0f);
	background3->setAnchorPoint(Vec2(0.0f, 0.0f));
	background3->setPosition(background2->boundingBox().size.width - 1, this->boundingBox().getMinY());

	//just a standded in sprite for the character
	Miner = Sprite::create("MineyPortraitHD.png");
	Miner->setPosition(this->boundingBox().getMinX(), this->boundingBox().getMidY());
	//apply physicsBody to the sprite
	Miner->setPhysicsBody(MinerPhys);
}

void HelloWorld::initObstacles()
{
	m_PlatformManager = new PlatformManager(this);
	m_PlatformManager->Generate();

	m_SpikesManager = new SpikesManager(this);
	m_SpikesManager->Generate();


	m_RocksManager = new RocksManager(this);
	m_RocksManager->Generate();

	m_DebreeManager = new DebreeManager(this);
	m_DebreeManager->Generate();

	m_BatsManager = new BatsManager(this);
	m_BatsManager->Generate();

	m_FallingStonesManager = new FallingStonesManager(this);
	m_FallingStonesManager->Generate();
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
