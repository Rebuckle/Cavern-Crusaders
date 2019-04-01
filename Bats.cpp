#include "Bats.h"
#include "cocos2d.h"
#include "physics\CCPhysicsWorld.h"

BatsManager::BatsManager(cocos2d::Scene * scene)
{
	m_Scene = scene;
}


void BatsManager::operator+=(Bats *a_Platform)
{
	for (unsigned int i = 0; i < m_BatsContainer.size(); i++)
	{
		if (m_BatsContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_BatsContainer.push_back(a_Platform);
}

void BatsManager::operator-=(Bats *a_Platform)
{
	for (unsigned int i = 0; i < m_BatsContainer.size(); i++)
	{
		if (m_BatsContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_BatsContainer.push_back(a_Platform);
}

Bats * BatsManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_BatsContainer.size())
	{
		return m_BatsContainer[a_Index];
	}
	return nullptr;
}

void BatsManager::Generate()
{
	for (unsigned int i = 0; i < 1; i++)
	{
		*(this) += new Bats(cocos2d::Vec2(i * 600, 830.0f), 30.0f, 75.0f, 14u, false);
		m_Scene->addChild(m_BatsContainer[m_BatsContainer.size() - 1]->m_Circle.getPrimitive());
	}
}

void BatsManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_BatsContainer.size(); i++)
	{
		m_BatsContainer[i]->Update(dt);
	}

}

Bats::Bats(const cocos2d::Vec2 & a_StartPosition, const float & a_Radius, const float & a_Angle, const unsigned int & a_Segments, const bool & a_DrawLineToCenter)
	: m_Circle(a_StartPosition, a_Radius, a_Angle, a_Segments, a_DrawLineToCenter)
{
	initialize();
}

void Bats::Update(float dt)
{
	//m_Circle.getPrimitive()->setPosition(calcX(init_Velocity, angle), calcY(init_Velocity, angle));
	//angle = angle + (3.14 / 800); //800 slows down the movement
	
	this->setPosition(calcX(init_Velocity, angle), calcY(init_Velocity, angle));
	angle = angle + (3.14 / 800);

	//m_Bat = a_HelloWorld;//allows use of addChild

	/*m_Bat->addChild(someSprite);*/
}

void Bats::initialize()
{
	//bat animation
	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("Sprites/Bats/bats.plist");

	//someSprite = Sprite::createWithSpriteFrameName("Bat01.png");

	// load all the animation frames into an array
	Vector<SpriteFrame*> frames;
	for (int i = 1; i <= 8; i++)
	{
		std::stringstream ss;
		ss << "Bat" << i << ".png";
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
		frames.pushBack(cacher->getSpriteFrameByName(ss.str()));
	}

	// play the animation
	Animation* anim = Animation::createWithSpriteFrames(frames, 0.05f);
	anim->setLoops(-1);
	someSprite = Animate::create(anim);
	someSprite->retain();

	this->runAction(RepeatForever::create(someSprite));
}

double Bats::calcX(int init_Velocity, double angle)
{
	xPosition = (((init_Velocity)*(init_Velocity))*sin(2 * angle)); //projectile movement
	xPosition = xPosition * 5; // since a bat flies, they will not be affected as gravity as much and therefore can move longer distances
	xPosition = xPosition + 1000; //center the bat's dive to the center of the screen
	return xPosition;
}

double Bats::calcY(int init_Velocity, double angle)
{
	yPosition = (init_Velocity)*(init_Velocity)*((sin(angle))*(sin(angle))) / 2 * gravity; //m=projectile movement
	yPosition = yPosition + 1800; //move the bat up higher so that it will be on the upper portion of the screen
	return yPosition;
}

