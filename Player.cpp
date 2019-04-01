#include "Player.h"

Player * Player::create()
{
	Player * character = new Player();
	
	if (character && character->initWithFile("Sprites/Push Animation/Push01.png"))
	{
		character->autorelease();
		character->initPlayer(character);
		return character;
	}

	CC_SAFE_DELETE(character);
	return NULL;
}

void Player::update()
{
	if (moving == true && jumping == false)
	{
		if (direction == 0) // check if going left
		{
			this->setScale(5, 5); //flip image horizontally
			this->setPosition(this->getPosition() - Vec2(3.0f, 0.0f));
		}
		if (direction == 1)  //going right
		{
			this->setScale(-5, 5); //flip image horizontally
			this->setPosition(this->getPosition() + Vec2(5.0f, 0.0f));
		}
	}
	else if (jumping == true && moving == false)
	{
		if (direction == 0) // check if going left
		{
			this->setScale(5, 5); //flip image horizontally
			this->setPosition(this->getPosition() + Vec2(0.0f, 100.0f));
			jumping = false;
		}
		if (direction == 1)  //going right
		{
			this->setScale(-5, 5); //flip image horizontally
			this->setPosition(this->getPosition() + Vec2(0.0f, 100.0f));
			jumping = false;
		}
	}
	else if (moving == false && jumping == false)
	{
		if (direction == 0) // check if going left
		{
			this->setScale(5, 5); //flip image horizontally
			this->setPosition(this->getPosition() - Vec2(2.0f, 0.0f));
		}
		if (direction == 1)  //going right
		{
			this->setScale(-5, 5); //flip image horizontally
			this->setPosition(this->getPosition() - Vec2(2.0f, 0.0f));
		}
	}
}

void Player::initPlayer(Player * character)
{
	moving = false;
	jumping = false;

	playerPhys = PhysicsBody::createBox(Size(30.0f, 40.0f), PhysicsMaterial(0.0f, 0.0f, 1.0f));
	playerPhys->setDynamic(true);

	character->setPhysicsBody(playerPhys);
	playerPhys->setAngularVelocityLimit(0);
	//seting collision bitmask
	playerPhys->setCollisionBitmask(2);
	playerPhys->setContactTestBitmask(true);

	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("Sprites/Animation/playerMovement.plist");

	// ---------------- idle animation ---------------- 
	// ------------------------------------------------
	// load all the animation frames into an array
	Vector<SpriteFrame*> idleFrames;
	for (int i = 1; i <= 4; i++)
	{
		std::stringstream ss;
		ss << "Push0" << i << ".png";
		idleFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		idleFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		idleFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		//i++;
	}

	// play the animation
	auto idleAnimation = Animation::createWithSpriteFrames(idleFrames, 0.05f);
	//idleAnimation->setLoops(-1);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //retain to use it later
	//this->runAction(RepeatForever::create(idleAnimate)); //starting animation
	

	// ---------------- run animation ---------------- 
	// -----------------------------------------------
	// load all the animation frames into an array
	Vector<SpriteFrame*> runFrames;
	for (int i = 1; i <= 8; i++)
	{
		std::stringstream ss;
		ss << "Run0" << i << ".png";
		runFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		runFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		runFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		//i++;
	}

	// play the animation
	auto runAnimation = Animation::createWithSpriteFrames(runFrames, 0.05f);
	//runAnimation->setLoops(-1);
	runAnimate = Animate::create(runAnimation);
	runAnimate->retain(); //retain to use it later


	// ---------------- jump animation ---------------- 
	// ------------------------------------------------
	// load all the animation frames into an array
	Vector<SpriteFrame*> jumpFrames;
	for (int i = 1; i <= 6; i++)
	{
		std::stringstream ss;
		ss << "Jump Animatons" << i << ".png";
		jumpFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		jumpFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		jumpFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		//i++;
	}

	// play the animation
	auto jumpAnimation = Animation::createWithSpriteFrames(jumpFrames, 0.05f);
	//jumpAnimation->setLoops(-1);
	jumpAnimate = Animate::create(jumpAnimation);
	jumpAnimate->retain(); //retain to use it later

}

Player::~Player()
{
	CC_SAFE_RELEASE(idleAnimate);
	CC_SAFE_RELEASE(runAnimate);
	CC_SAFE_RELEASE(jumpAnimate);
}

void Player::move(int directionVal)
{
	direction = directionVal;
	moving = true;
	jumping = false;

	stopAction(idleAnimate);
	stopAction(jumpAnimate);
	stopAction(runAnimate);
	runAction(RepeatForever::create(runAnimate));
}

void Player::idle()
{
	moving = false;
	jumping = false;

	stopAction(runAnimate);
	stopAction(jumpAnimate);
	stopAction(idleAnimate);
	runAction(RepeatForever::create(idleAnimate));
}

void Player::jump()
{
	jumping = true;
	moving = false;

	stopAction(idleAnimate);
	stopAction(runAnimate);
	stopAction(jumpAnimate);
	runAction(RepeatForever::create(jumpAnimate));

}
