#pragma once
#pragma once

#include <vector>
#include "Primitives.h"

namespace cocos2d
{
	class Vec2;
	class Scene;
}

class Rocks
{
public:
	Rocks(const cocos2d::Vec2 &a_StartPosition, const float &a_Radius, const float &a_Angle, const unsigned int &a_Segments, const bool &a_DrawLineToCenter);
	virtual void Update(float dt);
	BathMat::PrimitiveCricle m_Circle;
private:
};

class RocksManager
{
public:
	RocksManager(cocos2d::Scene *scene);
	void operator +=(Rocks *);
	void operator -=(Rocks *);
	Rocks * operator [](unsigned int a_Index);
	void Generate();
	void Update(float dt);

	std::vector<Rocks *> m_RocksContainer;
private:
	cocos2d::Scene * m_Scene;
};