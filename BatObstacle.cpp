#include "BatObstacle.h"

BatObstacle * BatObstacle::create()
{
	BatObstacle * batObs = new BatObstacle();

	if (batObs && batObs->initWithFile("Sprites/Bats/Bat01.png"))
	{
		batObs->autorelease();
		batObs->initBat(batObs);
		return batObs;
	}

	CC_SAFE_DELETE(batObs);
	return NULL;
}

BatObstacle::~BatObstacle()
{
	CC_SAFE_RELEASE(batAnimate);
}

double BatObstacle::calcX(int init_Velocity, double angle)
{
	xPosition = (((init_Velocity)*(init_Velocity))*sin(2 * angle)); //projectile movement
	xPosition = xPosition * 5; // since a bat flies, they will not be affected as gravity as much and therefore can move longer distances
	xPosition = xPosition + 1000; //center the bat's dive to the center of the screen
	return xPosition;
}

double BatObstacle::calcY(int init_Velocity, double angle)
{
	yPosition = (init_Velocity)*(init_Velocity)*((sin(angle))*(sin(angle))) / 2 * gravity; //m=projectile movement
	yPosition = yPosition + 2500; //move the bat up higher so that it will be on the upper portion of the screen
	return yPosition;
}

void BatObstacle::initBat(BatObstacle * batOb)
{
	batExist = false;

	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("Sprites/Bats/bats.plist");

	// load all the animation frames into an array
	Vector<SpriteFrame*> batFrames;
	for (int i = 1; i <= 8; i++)
	{
		std::stringstream ss;
		ss << "Bat0" << i << ".png";
		batFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		batFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		batFrames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		//i++;
	}

	// play the animation
	auto batAnimation = Animation::createWithSpriteFrames(batFrames, 0.05f);
	batAnimate = Animate::create(batAnimation);
	batAnimate->retain(); //retain to use it later
	this->runAction(RepeatForever::create(batAnimate));
}

void BatObstacle::Update(float dt)
{
	if (batExist == true)
	{
		this->setPosition(calcX(init_Velocity, angle), calcY(init_Velocity, angle));
		this->setScale(2.0f);
		angle = angle + (3.14 / 800);
	}
	else
	{
		this->setPosition(0, 0);
		angle = 0.05;
	}
	
}

void BatObstacle::spawnBat()
{
	batExist = true;
}

void BatObstacle::delBat()
{
	batExist = false;
}
