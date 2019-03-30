#include "Player.h"

Player * Player::create()
{
	Player * character = new Player();
	
	if (character && character->initWithFile("Sprites/Push Animation/Push01.png"))
	{
		character->autorelease();
		character->initPlayer();
		return character;
	}

	CC_SAFE_DELETE(character);
	return NULL;
}

void Player::update()
{
	if (moving == true)
	{
		if (direction == 0) // check if going left
		{
			this->setScale(5,5); //flip image horizontally
			this->setPosition(this->getPosition() - Vec2(2.5f, 0.0f));
		}
		else //going right
		{
			this->setScale(-5,5); //flip image horizontally
			this->setPosition(this->getPosition() + Vec2(5.0f, 0.0f));
		}
	}
	else
	{
		if (direction == 0) // check if going left
		{
			this->setScale(5, 5); //flip image horizontally
			this->setPosition(this->getPosition() - Vec2(1.5f, 0.0f));
		}
		else //going right
		{
			this->setScale(-5, 5); //flip image horizontally
			this->setPosition(this->getPosition() - Vec2(1.5f, 0.0f));
		}
	}
}

void Player::initPlayer()
{
	moving = false;

	// ---------------- idle animation ---------------- 
	// ------------------------------------------------
	auto cacherIdle = SpriteFrameCache::getInstance();
	cacherIdle->addSpriteFramesWithFile("Sprites/Push Animation/Push.plist");

	Sprite* idleSprite = Sprite::createWithSpriteFrameName("Push01.png");

	// load all the animation frames into an array
	Vector<SpriteFrame*> idleFrames;
	for (int i = 1; i <= 4; i++)
	{
		std::stringstream ss;
		ss << "Push0" << i << ".png";
		idleFrames.pushBack(cacherIdle->getSpriteFrameByName(ss.str()));
		idleFrames.pushBack(cacherIdle->getSpriteFrameByName(ss.str()));
		idleFrames.pushBack(cacherIdle->getSpriteFrameByName(ss.str()));
		//i++;
	}

	// play the animation
	Animation* idleAnimation = Animation::createWithSpriteFrames(idleFrames, 0.05f);
	idleAnimation->setLoops(-1);
	idleAnimate = Animate::create(idleAnimation);
	idleAnimate->retain(); //retain to use it later
	this->runAction(RepeatForever::create(idleAnimate)); //starting animation
	

	// ---------------- run animation ---------------- 
	// -----------------------------------------------
	auto cacherRun = SpriteFrameCache::getInstance();
	cacherRun->addSpriteFramesWithFile("Sprites/Run Animation/Run.plist");

	Sprite* runSprite = Sprite::createWithSpriteFrameName("Run01.png");

	// load all the animation frames into an array
	Vector<SpriteFrame*> runFrames;
	for (int i = 1; i <= 8; i++)
	{
		std::stringstream ss;
		ss << "Run0" << i << ".png";
		runFrames.pushBack(cacherRun->getSpriteFrameByName(ss.str()));
		runFrames.pushBack(cacherRun->getSpriteFrameByName(ss.str()));
		runFrames.pushBack(cacherRun->getSpriteFrameByName(ss.str()));
		//i++;
	}

	// play the animation
	Animation* runAnimation = Animation::createWithSpriteFrames(runFrames, 0.05f);
	runAnimation->setLoops(-1);
	runAnimate = Animate::create(runAnimation);
	runAnimate->retain(); //retain to use it later

}

Player::~Player()
{
	CC_SAFE_RELEASE(idleAnimate);
	CC_SAFE_RELEASE(runAnimate);
}

void Player::move(int directionVal)
{
	direction = directionVal;
	moving = true;

	//this->stopAllActions();
	this->stopAction(idleAnimate);
	this->runAction(RepeatForever::create(runAnimate));
}

void Player::idle()
{
	moving = false;
	//this->stopAllActions();
	this->stopAction(runAnimate);
	this->runAction(RepeatForever::create(idleAnimate));
}
