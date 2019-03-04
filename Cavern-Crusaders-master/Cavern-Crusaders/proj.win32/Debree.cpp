#include "Debree.h"
#include "cocos2d.h"

DebreeManager::DebreeManager(cocos2d::Scene * scene)
{
	m_Scene = scene;
}


void DebreeManager::operator+=(Debree *a_Platform)
{
	for (unsigned int i = 0; i < m_DebreeContainer.size(); i++)
	{
		if (m_DebreeContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_DebreeContainer.push_back(a_Platform);
}

void DebreeManager::operator-=(Debree *a_Platform)
{
	for (unsigned int i = 0; i < m_DebreeContainer.size(); i++)
	{
		if (m_DebreeContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_DebreeContainer.push_back(a_Platform);
}

Debree * DebreeManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_DebreeContainer.size())
	{
		return m_DebreeContainer[a_Index];
	}
	return nullptr;
}

void DebreeManager::Generate()
{
	for (unsigned int i = 0; i < 5; i++)
	{
		*(this) += new Debree(cocos2d::Vec2(i * 650, 730.0f), cocos2d::Vec2(i * 650 + 100, 930.0f));
		m_Scene->addChild(m_DebreeContainer[m_DebreeContainer.size() - 1]->m_Square.getPrimitive());
	}
}

void DebreeManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_DebreeContainer.size(); i++)
	{
		m_DebreeContainer[i]->Update(dt);
	}
}

Debree::Debree(const cocos2d::Vec2 & a_StartPosition, const cocos2d::Vec2 & a_EndPosition) : m_Square(a_StartPosition, a_EndPosition)
{
}

void Debree::Update(float dt)
{
	//cocos2d::Vec2 l_tmp = m_Square.getPrimitive()->getPosition();
	m_Square.getPrimitive()->setPosition(m_Square.getPrimitive()->getPositionX() - 5, m_Square.getPrimitive()->getPositionY());
}
