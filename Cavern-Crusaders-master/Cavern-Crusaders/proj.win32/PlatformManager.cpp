#include "PlatformManager.h"
#include "cocos2d.h"

PlatformManager::PlatformManager(cocos2d::Scene * a_Scene)
{
	m_Scene = a_Scene;
}

void PlatformManager::operator+=(Platform *a_Platform)
{
	for (unsigned int i = 0; i < m_PlatformContainer.size(); i++)
	{
		if (m_PlatformContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_PlatformContainer.push_back(a_Platform);
}

void PlatformManager::operator-=(Platform *a_Platform)
{
	for (unsigned int i = 0; i < m_PlatformContainer.size(); i++)
	{
		if (m_PlatformContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_PlatformContainer.push_back(a_Platform);
}

Platform * PlatformManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_PlatformContainer.size())
	{
		return m_PlatformContainer[a_Index];
	}
	return nullptr;
}

void PlatformManager::update(float a_deltaTime)
{
	for (unsigned int i = 0; i < m_PlatformContainer.size(); i++)
	{
		m_PlatformContainer[i]->Update(a_deltaTime);
	}
}

void PlatformManager::Generate()
{

	//this function should change with each student
	// I would give bonus marks here if they do something interesting
	for (unsigned int i = 0; i < 3; i++)
	{
		*(this) += new Platform(cocos2d::Vec2(i * 550, 500.0f), cocos2d::Vec2(i * 550 + 100, 550.0f));
		m_Scene->addChild(m_PlatformContainer[m_PlatformContainer.size() - 1]->m_Square.getPrimitive());
	}
}

Platform::Platform(const cocos2d::Vec2 & a_StartPosition, const cocos2d::Vec2 & a_EndPosition) : m_Square(a_StartPosition, a_EndPosition)
{
}

void Platform::Update(float a_deltaTime)
{
	m_Square.getPrimitive()->setPosition(m_Square.getPrimitive()->getPositionX() - 5, m_Square.getPrimitive()->getPositionY());
}
