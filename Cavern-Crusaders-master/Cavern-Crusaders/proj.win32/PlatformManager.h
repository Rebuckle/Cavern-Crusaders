#pragma once
#include <vector>
#include "Primitives.h"

namespace cocos2d
{
	class Vec2;
	class Scene;
}

class Platform
{
public:
	Platform(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition);
	virtual void Update(float a_deltaTime);
	BathMat::PrimitiveSquare m_Square;
private:

};

class PlatformManager
{
public:
	PlatformManager(cocos2d::Scene *);
	void operator +=(Platform *);
	void operator -=(Platform *);
	Platform * operator [](unsigned int a_Index);
	void update(float a_deltaTime);
	void Generate();

private:
	std::vector<Platform *> m_PlatformContainer;
	cocos2d::Scene * m_Scene;
};
