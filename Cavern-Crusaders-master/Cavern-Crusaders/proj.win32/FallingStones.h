#pragma once

#include <vector>
#include "Primitives.h"

namespace cocos2d
{
	class Vec2;
	class Scene;
}

class FallingStones
{
public:
	FallingStones(const cocos2d::Vec2 &a_StartPosition, const float &a_Radius, const float &a_Angle, const unsigned int &a_Segments, const bool &a_DrawLineToCenter);
	virtual void Update(float dt);
	BathMat::PrimitiveCricle m_Circle;
private:
};

class FallingStonesManager
{
public:
	FallingStonesManager(cocos2d::Scene *scene);
	void operator +=(FallingStones *);
	void operator -=(FallingStones *);
	FallingStones * operator [](unsigned int a_Index);
	void Generate();
	void Update(float dt);

	std::vector<FallingStones *> m_FallingStonesContainer;
private:
	cocos2d::Scene * m_Scene;
};