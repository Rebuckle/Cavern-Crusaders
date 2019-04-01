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

	
	//--- Tiled Map ---//
	//_tileMap = new CCTMXTiledMap();
	//_tileMap->initWithTMXFile("Cavern.tmx");
	//_background = _tileMap->layerNamed("Background");
	//_tileMap->setPosition(Vec2(0, 0));
	////_tileMap->setScale(10);

	//---TILE MAP LVL 1---//
	_tileMap = TMXTiledMap::create("Cavern.tmx");
	addChild(_tileMap, 0, 99);


	CCTMXObjectGroup *objectGroup = _tileMap->objectGroupNamed("Objects");

	/*if (objectGroup == NULL) {
		CCLog("tile map has no objects object layer");
		return false;
	}*/

	ValueMap spawnPoint = objectGroup->objectNamed("SpawnPoint");

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();

	_player = new CCSprite();
	_player->initWithFile("Player.png");
	_player->setPosition(ccp(x, y));

	this->addChild(_player);
	//this->setViewPointCenter(_player->getPosition());

	//---Collisions---//
	_meta = _tileMap->layerNamed("Meta");
	_meta->setVisible(true);

	//this->addChild(_tileMap);

	

	/*auto map = TMXTiledMap::create("TileMap.tmx");
	map->setScale(10);
	this->addChild(map, 10);*/

	//this->addChild(_background);

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
	this->addChild(backgroundFront, -1);
	this->addChild(backgroundFront2, -1);
	this->addChild(backgroundFront3, -1);
	this->addChild(Miner,1);
	this->addChild(edgeNode, 2);

	//Allow for the update() function to be called by cocos
	this->scheduleUpdate();

	// ------------- Timer Score ------------- 
	// ---------------------------------------

	//Add the score count to the screen
	scoreCount = Label::createWithTTF("0", "fonts/8-bit pusab.ttf", 60);
	if (scoreCount == nullptr)
	{
		problemLoading("'fonts/8-bit pusab.ttf'");
	}
	else
	{
		// colour and position the text on the center top of the screen
		scoreCount->setColor(Color3B::GRAY);
		scoreCount->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height - scoreCount->getContentSize().height - 80.0f));

		// add the scoreCount text as a child to this layer
		this->addChild(scoreCount, 1);
	}

	//set beginning time to 0
	time = 0;

	//call the TimerMethod to count up by 1s increments
	this->schedule(schedule_selector(HelloWorld::TimerMethod), 1.0f);



    return true;
}

//---Collisions---//
//CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
//{
//	int x = position.x / _tileMap->getTileSize().width;
//	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
//	return ccp(x, y);
//}

//---Spawning Player---//
//void HelloWorld::setViewPointCenter(CCPoint position) {
//
//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//
//	int x = MAX(position.x, winSize.width / 2);
//	int y = MAX(position.y, winSize.height / 2);
//	x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
//	y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height / 2);
//	CCPoint actualPosition = ccp(x, y);
//
//	CCPoint centerOfView = ccp(winSize.width / 2, winSize.height / 2);
//	CCPoint viewPoint = ccpSub(centerOfView, actualPosition);
//	this->setPosition(viewPoint);
//}

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
	
	/*MovingBats *myMovingBats = new MovingBats(cocos2d::Vec2(50, 50), 45.0f, 45.0f, 12, false, cocos2d::Vec2(50, 150), cocos2d::Vec2(50, 0), 10.0f);
	myMovingBats->update(deltaTime);*/
	
	
	// update the Miner's velocity
	if (key_W == true)
		setPlayerPosition(Vec2(Miner->getPositionX(), Miner->getPositionY() + 10));
		//MinerPhys->applyForce(Vec2(0, 200));
	if (key_S == true)
		setPlayerPosition(Vec2(Miner->getPositionX(), Miner->getPositionY() - 10));
	//MinerPhys->applyForce(Vec2(0, 0));
	if (key_A == true)
		setPlayerPosition(Vec2(Miner->getPositionX()-10, Miner->getPositionY()));
	//MinerPhys->applyForce(Vec2(-100, 0));
	if (key_D == true)
		setPlayerPosition(Vec2(Miner->getPositionX()+10, Miner->getPositionY()));
	/*MinerPhys->applyForce(Vec2(100, 0));*/

	
	
}


void HelloWorld::initBackground()
{
	// ------------------- Background Back ------------------- 
	// -------------------------------------------------------
	background->setPosition(background->getPositionX() - 2, background->getPositionY());
	background2->setPosition(background2->getPositionX() - 2, background2->getPositionY());
	background3->setPosition(background3->getPositionX() - 2, background3->getPositionY());
	_tileMap->setPosition(_tileMap->getPositionX() - 4, _tileMap->getPositionY());



	//tileCoordForPosition(_tileMap->getPosition())

	//Miner->setPosition(_tileMap->getPositionX() - 4, _tileMap->getPositionY());
	//setPlayerPosition(Vec2(_tileMap->getPositionX(), _tileMap->getPositionY()));
	if (time >= 52) {
		_tileMapLvl2->setPosition(_tileMapLvl2->getPositionX() - 4, _tileMapLvl2->getPositionY());
	}
	
	if (time >= 100)
	{
		_tileMapLvl3->setPosition(_tileMapLvl3->getPositionX() - 4, _tileMapLvl3->getPositionY());
	}
	if (time >= 150)
	{
		_tileMapLvl4->setPosition(_tileMapLvl4->getPositionX() - 4, _tileMapLvl4->getPositionY());
	}
	if (time >= 200)
	{
		_tileMapLvl5->setPosition(_tileMapLvl5->getPositionX() - 4, _tileMapLvl5->getPositionY());
	}
	if (time >= 250)
	{
		_tileMapLvl6->setPosition(_tileMapLvl6->getPositionX() - 4, _tileMapLvl6->getPositionY());
	}
	if (time >= 300)
	{
		_tileMapLvl7->setPosition(_tileMapLvl7->getPositionX() - 4, _tileMapLvl7->getPositionY());
	}
	if (time >= 350)
	{
		_tileMapLvl8->setPosition(_tileMapLvl8->getPositionX() - 4, _tileMapLvl8->getPositionY());
	}


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

	// ------------------- Background Front ------------------- 
	// --------------------------------------------------------
	backgroundFront->setPosition(backgroundFront->getPositionX() - 3, backgroundFront->getPositionY());
	backgroundFront2->setPosition(backgroundFront2->getPositionX() - 3, backgroundFront2->getPositionY());
	backgroundFront3->setPosition(backgroundFront3->getPositionX() - 3, backgroundFront3->getPositionY());
	if (backgroundFront->getPositionX() < -backgroundFront->boundingBox().size.width)
	{
		backgroundFront->setPosition(backgroundFront3->getPositionX() + backgroundFront3->boundingBox().size.width, backgroundFront->getPositionY());
	}
	if (backgroundFront2->getPositionX() < -backgroundFront2->boundingBox().size.width)
	{
		backgroundFront2->setPosition(backgroundFront->getPositionX() + backgroundFront->boundingBox().size.width, backgroundFront2->getPositionY());
	}
	if (backgroundFront3->getPositionX() < -backgroundFront3->boundingBox().size.width)
	{
		backgroundFront3->setPosition(backgroundFront2->getPositionX() + backgroundFront2->boundingBox().size.width, backgroundFront3->getPositionY());
	}


}
void HelloWorld::initSprites()
{
	MinerPhys = PhysicsBody::createBox(Size(110.0f, 125.0f), PhysicsMaterial(0.0f, 0.0f, 1.0f));
	MinerPhys->setDynamic(true);
	MinerPhys->setCollisionBitmask(2);
	MinerPhys->setContactTestBitmask(true);

	

	// ------------------- Background Back ------------------- 
	// -------------------------------------------------------
	background = Sprite::create("Background Back.png");
	background->setScale(1.07f);
	background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setPosition(0, this->boundingBox().getMinY());

	background2 = Sprite::create("Background Back.png");
	background2->setScale(1.07f);
	background2->setAnchorPoint(Vec2(0.0f, 0.0f));
	background2->setPosition(background->boundingBox().size.width - 1, this->boundingBox().getMinY());

	background3 = Sprite::create("Background Back.png");
	background3->setScale(1.07f);
	background3->setAnchorPoint(Vec2(0.0f, 0.0f));
	background3->setPosition(background2->boundingBox().size.width - 1, this->boundingBox().getMinY());

	// ------------------- Background Front ------------------- 
	// --------------------------------------------------------
	backgroundFront = Sprite::create("Background front.png");
	backgroundFront->setScale(1.07f);
	backgroundFront->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundFront->setPosition(0, this->boundingBox().getMinY());

	backgroundFront2 = Sprite::create("Background front.png");
	backgroundFront2->setScale(1.07f);
	backgroundFront2->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundFront2->setPosition(backgroundFront->boundingBox().size.width - 1, this->boundingBox().getMinY());

	backgroundFront3 = Sprite::create("Background front.png");
	backgroundFront3->setScale(1.07f);
	backgroundFront3->setAnchorPoint(Vec2(0.0f, 0.0f));
	backgroundFront3->setPosition(backgroundFront2->boundingBox().size.width - 1, this->boundingBox().getMinY());

	//just a standded in sprite for the character
	Miner = Sprite::create("Character Rough Right.png");
	Miner->setScale(0.3f);
	Miner->setPosition(this->boundingBox().getMinX(), this->boundingBox().getMidY());
	//apply physicsBody to the sprite
	//Miner->setPhysicsBody(MinerPhys);
	
	


	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}


void HelloWorld::initObstacles()
{
	
	
	/*m_PlatformManager = new PlatformManager(this);
	m_SpikesManager = new SpikesManager(this);
	m_RocksManager = new RocksManager(this);
	m_DebreeManager = new DebreeManager(this);
	m_FallingStonesManager = new FallingStonesManager(this);*/
	
	//Easy 1 

	//m_PlatformManager->GenerateEasy();
	//m_SpikesManager->GenerateEasy();
	//m_RocksManager->GenerateEasy();
	//m_DebreeManager->GenerateEasy();

	/*m_PlatformManager->GenerateEasy3();
	m_DebreeManager->GenerateEasy3();*/
	//Easy 2

	/*if (background2->getPositionX() > -background2->boundingBox().size.width - 1000)
	{
		m_PlatformManager->GenerateEasy2();
		m_SpikesManager->GenerateEasy2();
		m_FallingStonesManager->GenerateEasy();
	}*/

	/*
	m_BatsManager = new BatsManager(this);
	m_BatsManager->Generate();
	*/


	
}

// ------------- Timer Function ------------- 
// ------------------------------------------ 
void HelloWorld::TimerMethod(float dt)
{
	time += dt;
	__String * timeToDisplay = __String::createWithFormat("%.0f", time);
	scoreCount->setString(timeToDisplay->getCString());

	//Insert different difficulty setting here
	//if (time == ? ) -> Level 1, 2, 3, 4, so on...

	/*if (time == 1)
	{
		m_PlatformManager->GenerateEasy();
		m_SpikesManager->GenerateEasy();
		m_RocksManager->GenerateEasy();
		m_DebreeManager->GenerateEasy();
	}
	*/
	
	if(time == 52)
	{
		//---TILE MAP LVL 2---//
		_tileMapLvl2 = TMXTiledMap::create("Cavern2.tmx");
		//_tileMapLvl2->setPosition(Vec2(_tileMap->getBoundingBox().size.width -1, this->boundingBox().getMidY()));
		_tileMapLvl2->setPositionX(1920);
		addChild(_tileMapLvl2, 0, 100);
	}
	if (time == 100)
	{
		_tileMapLvl3 = TMXTiledMap::create("Cavern3.tmx");
		_tileMapLvl3->setPositionX(1920);
		addChild(_tileMapLvl3, 0, 101);
	}

	if (time == 150)
	{
		_tileMapLvl4 = TMXTiledMap::create("Cavern4.tmx");
		_tileMapLvl4->setPositionX(1920);
		addChild(_tileMapLvl4, 0, 102);
	}
	if (time == 200)
	{
		_tileMapLvl5 = TMXTiledMap::create("Cavern5.tmx");
		_tileMapLvl5->setPositionX(1920);
		addChild(_tileMapLvl5, 0, 103);
	}
	if (time == 250)
	{
		_tileMapLvl6 = TMXTiledMap::create("Cavern6.tmx");
		_tileMapLvl6->setPositionX(1920);
		addChild(_tileMapLvl6, 0, 104);
	}
	if (time == 300)
	{
		_tileMapLvl7 = TMXTiledMap::create("Cavern7.tmx");
		_tileMapLvl7->setPositionX(1920);
		addChild(_tileMapLvl7, 0, 105);
	}
	if (time == 350)
	{
		_tileMapLvl8 = TMXTiledMap::create("Cavern8.tmx");
		_tileMapLvl8->setPositionX(1920);
		addChild(_tileMapLvl8, 0, 106);
	}

}

CCPoint HelloWorld::tileCoordForPosition(CCPoint position)
{
	int x = position.x / _tileMap->getTileSize().width;
	int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
	return ccp(x, y);
}

//---Collisions With Tile Map---//
void HelloWorld::setPlayerPosition(CCPoint position)
{
	CCPoint tileCoord = this->tileCoordForPosition(position);
	int tileGid = _meta->tileGIDAt(tileCoord);
	if (tileGid) {
		ValueMap properties = (_tileMap->propertiesForGID(tileGid)).asValueMap();
		if (!properties.empty()) {
			CCString *collision;
			collision = new CCString(properties["Collidable"].asString());
			if (collision && (collision->compare("true") == 0)) {
				return;
			}
		}
	}
	Miner->setPosition(position);
}


bool HelloWorld::onContactBegin(cocos2d::PhysicsContact & contact)
{
	
	return true;
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
