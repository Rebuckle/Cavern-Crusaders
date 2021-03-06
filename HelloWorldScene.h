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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Player.h"
using namespace cocos2d;

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	//Main Update Loop
	void update(float deltaTime);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	//sprite
	cocos2d::Sprite *Miner;
	cocos2d::Sprite* background;
	cocos2d::Sprite* background2;
	cocos2d::Sprite* background3;

	cocos2d::Sprite* backgroundFront;
	cocos2d::Sprite* backgroundFront2;
	cocos2d::Sprite* backgroundFront3;


	cocos2d::Sprite *Platforms;
	//sprite physicis body
	cocos2d::PhysicsBody *MinerPhys;
	cocos2d::PhysicsBody *PlatformPhys;
	//keyboard listiner
	void initListeners();
	void initKeyboardListener();
	//callback
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);

	//Obstacles

	//Init Functions
	void initBackground();
	void initSprites();
	void initObstacles();


	//Timer Score Functions and Data
	void TimerMethod(float dt);
	cocos2d::Label *scoreCount;
	float time;
	
	

	TMXTiledMap *_map;

	//---Collision Layer---//
	CCTMXLayer *_meta;
	CCPoint tileCoordForPosition(CCPoint position);

	//---Spawning Player---//
	CCSprite *_player;
	void setPlayerPosition(CCPoint position);
	void setViewPointCenter(CCPoint position);


	void Collisions();

	TMXTiledMap *_tileMap;
	TMXLayer *_background;
	

	TMXTiledMap *_tileMapLvl2;
	TMXTiledMap *_tileMapLvl3;
	TMXTiledMap *_tileMapLvl4;
	TMXTiledMap *_tileMapLvl5;
	TMXTiledMap *_tileMapLvl6;
	TMXTiledMap *_tileMapLvl7;
	TMXTiledMap *_tileMapLvl8;


	//player movement
	Player * character;
	cocos2d::PhysicsBody * CharacterPhys;
	void PlayerAnimation(int move);
	int move = 0;
	// 0 = Not moving, 1 = Move right, 2 = Move left, 3 = Jump,
	// 4 = Slide, 5 = Push Back
	int direction = 0;
	Sprite* someSprite;
	// 0 = No Direction, 1 = Right movement, 2 = Left Movement

private:
	//primitive Square
	//BathMat::PrimitiveSquare m_MySquare{ cocos2d::Vec2(550.0f,150.0f),cocos2d::Vec2(700.0f,250.0f) };

	//---Tiled Map---//
	


	//---Larry---//
	Sprite *_Larry;

	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { sceneWorld = world; };
	cocos2d::PhysicsWorld *sceneWorld;
	//Event Listener
	EventListenerKeyboard* keyboardListener;
	//input keys
	bool key_W = false;
	bool key_S = false;
	bool key_A = false;
	bool key_D = false;
	//Size of window
	cocos2d::Size size;

	bool onContactBegin(cocos2d::PhysicsContact &contact);


	


};

#endif // __HELLOWORLD_SCENE_H__
