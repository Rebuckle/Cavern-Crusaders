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

#include "CC_Gameplay.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* CavernCrusaders::createScene()
{
    return CavernCrusaders::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool CavernCrusaders::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

	////////////////////////////
	///////////////////////////
	//////////////////////////

	//Get Window Size
	size = Director::sharedDirector()->getInstance()->getWinSize();

	//Init Sprites
	//Background Sprite
	background = Sprite::create("CaveBack_Reference.jpg");
	background->setScale(5.0f);
	//background->setAnchorPoint(Vec2(0.0f, 0.0f));
	background->setPosition(0, this->boundingBox().getMidY());

	background2 = Sprite::create("CaveBack_Reference.jpg");
	background2->setScale(5.0f);
	//background2->setAnchorPoint(Vec2(0.0f, 0.0f));
	background2->setPosition(background->boundingBox().size.width-1, this->boundingBox().getMidY());

	//Character Sprite (Larry Lance)
	Larry = Sprite::create("EnemyShip.png");
	Larry->setScale(0.5f);
	Larry->setPosition(this->boundingBox().getMinX(), this->boundingBox().getMidY());
	

	//auto moveTo = MoveTo::create(10, Vec2(5000, this->boundingBox().getMidY()));
	//Larry->runAction(moveTo);


	//Add sprites to the scene
	this->addChild(background, -1);
	this->addChild(background2, -1);
	this->addChild(Larry, 1);

	//Add obstacles to the scene
	addChild(m_MySquare.getDrawNode(), 5);

	this->scheduleUpdate();

	////////////////////////////
	///////////////////////////
	//////////////////////////

    return true;
}

void CavernCrusaders::update(float delta)
{
	//Camera that follows Larry
	this->getDefaultCamera()->setPosition(Larry->getPosition());

	//Infinite Looping Background
	//////////////////////////////
	/////////////////////////////
	////////////////////////////
	background->setPosition(background->getPositionX() - 12, background->getPositionY());
	background2->setPosition(background2->getPositionX() - 12, background2->getPositionY());
	if (background->getPositionX() < -background->boundingBox().size.width)
	{
		background->setPosition(background2->getPositionX() + background2->boundingBox().size.width, background->getPositionY());
	}
	if (background2->getPositionX() < -background2->boundingBox().size.width)
	{
		background2->setPosition(background->getPositionX() + background->boundingBox().size.width, background2->getPositionY());
	}
	m_MySquare.getDrawNode()->setPosition(m_MySquare.getDrawNode()->getPositionX() - 12, m_MySquare.getDrawNode()->getPositionY());
	//////////////////////////////
	/////////////////////////////
	////////////////////////////

}


void CavernCrusaders::menuCloseCallback(Ref* pSender)
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
