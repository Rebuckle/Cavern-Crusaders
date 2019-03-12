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
#include "Primitives.h"
#include "PlatformManager.h"
#include "Spikes.h"
#include "Rocks.h"
#include "Debree.h"
#include "Bats.h"
#include "FallingStones.h"
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
	//sprite physicis body
	cocos2d::PhysicsBody *MinerPhys;
	//keyboard listiner
	void initListeners();
	void initKeyboardListener();
	//callback
	void keyDownCallback(EventKeyboard::KeyCode keycode, Event* event);
	void keyUpCallback(EventKeyboard::KeyCode keycode, Event* event);

	//Obstacles
	PlatformManager *m_PlatformManager;
	SpikesManager *m_SpikesManager;
	RocksManager *m_RocksManager;
	DebreeManager *m_DebreeManager;
	BatsManager *m_BatsManager;
	FallingStonesManager *m_FallingStonesManager;

	//Init Functions
	void initBackground();
	void initSprites();
	void initObstacles();

private:
	//primitive Square
	//BathMat::PrimitiveSquare m_MySquare{ cocos2d::Vec2(550.0f,150.0f),cocos2d::Vec2(700.0f,250.0f) };

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
};

#endif // __HELLOWORLD_SCENE_H__
