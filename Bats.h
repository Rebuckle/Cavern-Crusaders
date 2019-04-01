#pragma once

#include <vector>
#include "Primitives.h"
#include "HelloWorldScene.h"

USING_NS_CC;

using namespace cocos2d;

namespace cocos2d
{
	class Vec2;
	class Scene;
}

//class HelloWorld;

class Bats : public Node
{
public:
	Bats(const cocos2d::Vec2 &a_StartPosition, const float &a_Radius, const float &a_Angle, const unsigned int &a_Segments, const bool &a_DrawLineToCenter);
	virtual void Update(float dt);
	void initialize();
	double calcX(int init_Velocity, double angle);
	double calcY(int init_Velocity, double angle);
	/*Vec2 m_Direction;
	float m_Speed = 10.0f;*/
	BathMat::PrimitiveCricle m_Circle;
	Animate* someSprite;
private:
	int init_Velocity = 20;
	double angle = 0.05;
	const double gravity = -9.801, PI = 3.141592654;
	double xPosition = 0, yPosition = 0;
	int distanceInterval = 0;
	//HelloWorld *m_Bat;
};

class BatsManager : public Node
{
public:
	BatsManager(cocos2d::Scene *scene);
	void operator +=(Bats *);
	void operator -=(Bats *);
	Bats * operator [](unsigned int a_Index);
	void Generate();
	void Update(float dt);

	std::vector<Bats *> m_BatsContainer;
private:
	cocos2d::Scene * m_Scene;
};

//class MovingBats : public Bats
//{
//public:
//	MovingBats(const cocos2d::Vec2 &a_StartPosition, const float &a_Radius, const float &a_Angle, const unsigned int &a_Segments, const bool &a_DrawLineToCenter, 
//		const cocos2d::Vec2 &a_TravStartPoint, const cocos2d::Vec2 &a_TravEndPoint, const float a_Speed);
//	void update(float a_DeltaTime);
//	Vec2 m_TravStartPoint;
//	Vec2 m_TravEndPoint;
//	float m_Speed = 10.0f;
//	float m_Magnitude;
//	Vec2 m_Direction;
//	bool m_Reverse = false;
//};