#pragma once

#include <vector>
#include "Primitives.h"

namespace cocos2d
{
	class Vec2;
	class Scene;
}

class Spikes
{
public:
	Spikes(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_MidPosition, const cocos2d::Vec2 &a_EndPosition);
	virtual void Update(float dt);
	BathMat::PrimitiveTriangle m_Triangle;
private:
};

class SpikesManager
{
public:
	SpikesManager(cocos2d::Scene *scene);
	void operator +=(Spikes *);
	void operator -=(Spikes *);
	Spikes * operator [](unsigned int a_Index);
	void Generate();
	void Update(float dt);

	std::vector<Spikes *> m_SpikesContainer;
private:
	cocos2d::Scene * m_Scene;
};