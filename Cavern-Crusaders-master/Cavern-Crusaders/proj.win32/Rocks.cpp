#include "Rocks.h"
#include "cocos2d.h"

RocksManager::RocksManager(cocos2d::Scene * scene)
{
	m_Scene = scene;
}


void RocksManager::operator+=(Rocks *a_Platform)
{
	for (unsigned int i = 0; i < m_RocksContainer.size(); i++)
	{
		if (m_RocksContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_RocksContainer.push_back(a_Platform);
}

void RocksManager::operator-=(Rocks *a_Platform)
{
	for (unsigned int i = 0; i < m_RocksContainer.size(); i++)
	{
		if (m_RocksContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_RocksContainer.push_back(a_Platform);
}

Rocks * RocksManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_RocksContainer.size())
	{
		return m_RocksContainer[a_Index];
	}
	return nullptr;
}

void RocksManager::Generate()
{
	for (unsigned int i = 0; i < 5; i++)
	{
		*(this) += new Rocks(cocos2d::Vec2(i * 200, 290.0f), 60.0f, 75.0f, 14u, false);
		m_Scene->addChild(m_RocksContainer[m_RocksContainer.size() - 1]->m_Circle.getPrimitive());
	}
}

void RocksManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_RocksContainer.size(); i++)
	{
		m_RocksContainer[i]->Update(dt);
	}
}

Rocks::Rocks(const cocos2d::Vec2 & a_StartPosition, const float & a_Radius, const float & a_Angle, const unsigned int & a_Segments, const bool & a_DrawLineToCenter) 
	: m_Circle(a_StartPosition, a_Radius, a_Angle, a_Segments, a_DrawLineToCenter)
{
}

void Rocks::Update(float dt)
{
	//cocos2d::Vec2 l_tmp = m_Circle.getPrimitive()->getPosition();
	m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY());
}
