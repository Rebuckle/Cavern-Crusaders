#include "FallingStones.h"
#include "cocos2d.h"
#include "physics\CCPhysicsWorld.h"

FallingStonesManager::FallingStonesManager(cocos2d::Scene * scene)
{
	m_Scene = scene;
}


void FallingStonesManager::operator+=(FallingStones *a_Platform)
{
	for (unsigned int i = 0; i < m_FallingStonesContainer.size(); i++)
	{
		if (m_FallingStonesContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_FallingStonesContainer.push_back(a_Platform);
}

void FallingStonesManager::operator-=(FallingStones *a_Platform)
{
	for (unsigned int i = 0; i < m_FallingStonesContainer.size(); i++)
	{
		if (m_FallingStonesContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_FallingStonesContainer.push_back(a_Platform);
}

FallingStones * FallingStonesManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_FallingStonesContainer.size())
	{
		return m_FallingStonesContainer[a_Index];
	}
	return nullptr;
}

void FallingStonesManager::Generate()
{
	for (unsigned int i = 0; i < 5; i++)
	{
		*(this) += new FallingStones(cocos2d::Vec2(i * 600, 830.0f), 60.0f, 75.0f, 14u, false);
		m_Scene->addChild(m_FallingStonesContainer[m_FallingStonesContainer.size() - 1]->m_Circle.getPrimitive());
	}
}

void FallingStonesManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_FallingStonesContainer.size(); i++)
	{
		m_FallingStonesContainer[i]->Update(dt);
	}
}

FallingStones::FallingStones(const cocos2d::Vec2 & a_StartPosition, const float & a_Radius, const float & a_Angle, const unsigned int & a_Segments, const bool & a_DrawLineToCenter)
	: m_Circle(a_StartPosition, a_Radius, a_Angle, a_Segments, a_DrawLineToCenter)
{
}

void FallingStones::Update(float dt)
{
	//m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY() - 7);

	if (m_Circle.getPrimitive()->getPositionY() > m_Circle.getPrimitive()->boundingBox().size.height - 540)
	{
		m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY() - 7);
	}
	else
	{
		m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY());
	}
}
