#pragma once

#include <vector>
#include "Primitives.h"

using namespace cocos2d;

namespace cocos2d
{
	class Vec2;
	class Scene;
}

class Bats
{
public:
	Bats(const cocos2d::Vec2 &a_StartPosition, const float &a_Radius, const float &a_Angle, const unsigned int &a_Segments, const bool &a_DrawLineToCenter);
	virtual void Update(float dt);
	/*Vec2 m_Direction;
	float m_Speed = 10.0f;*/
	BathMat::PrimitiveCricle m_Circle;
private:
};

class BatsManager
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