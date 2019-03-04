#include "Spikes.h"
#include "cocos2d.h"

SpikesManager::SpikesManager(cocos2d::Scene * scene)
{
	m_Scene = scene;
}


void SpikesManager::operator+=(Spikes *a_Platform)
{
	for (unsigned int i = 0; i < m_SpikesContainer.size(); i++)
	{
		if (m_SpikesContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_SpikesContainer.push_back(a_Platform);
}

void SpikesManager::operator-=(Spikes *a_Platform)
{
	for (unsigned int i = 0; i < m_SpikesContainer.size(); i++)
	{
		if (m_SpikesContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_SpikesContainer.push_back(a_Platform);
}

Spikes * SpikesManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_SpikesContainer.size())
	{
		return m_SpikesContainer[a_Index];
	}
	return nullptr;
}

void SpikesManager::Generate()
{
	for (unsigned int i = 0; i < 5; i++)
	{
		*(this) += new Spikes(cocos2d::Vec2(i * 1100, 230.0f), cocos2d::Vec2(i * 1100 + 50, 330.0f), cocos2d::Vec2(i * 1100 + 100, 230.0f));
		m_Scene->addChild(m_SpikesContainer[m_SpikesContainer.size() - 1]->m_Triangle.getPrimitive());
	}
}

void SpikesManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_SpikesContainer.size(); i++)
	{
		m_SpikesContainer[i]->Update(dt);
	}
}

Spikes::Spikes(const cocos2d::Vec2 & a_StartPosition, const cocos2d::Vec2 & a_MidPosiion, const cocos2d::Vec2 & a_EndPosition) : m_Triangle(a_StartPosition, a_MidPosiion, a_EndPosition)
{
}

void Spikes::Update(float dt)
{
	//cocos2d::Vec2 l_tmp = m_Triangle.getPrimitive()->getPosition();
	m_Triangle.getPrimitive()->setPosition(m_Triangle.getPrimitive()->getPositionX() - 5, m_Triangle.getPrimitive()->getPositionY());
}
