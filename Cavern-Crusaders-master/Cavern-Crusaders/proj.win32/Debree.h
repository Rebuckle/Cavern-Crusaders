#pragma once
#pragma once
#pragma once

#include <vector>
#include "Primitives.h"

namespace cocos2d
{
	class Vec2;
	class Scene;
}

class Debree
{
public:
	Debree(const cocos2d::Vec2 &a_StartPosition, const cocos2d::Vec2 &a_EndPosition);
	virtual void Update(float dt);
	BathMat::PrimitiveSquare m_Square;
private:
};

class DebreeManager
{
public:
	DebreeManager(cocos2d::Scene *scene);
	void operator +=(Debree *);
	void operator -=(Debree *);
	Debree * operator [](unsigned int a_Index);
	void Generate();
	void Update(float dt);

	std::vector<Debree *> m_DebreeContainer;
private:
	cocos2d::Scene * m_Scene;
};