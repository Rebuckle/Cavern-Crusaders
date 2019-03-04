#include "Bats.h"
#include "cocos2d.h"
#include "physics\CCPhysicsWorld.h"

BatsManager::BatsManager(cocos2d::Scene * scene)
{
	m_Scene = scene;
}


void BatsManager::operator+=(Bats *a_Platform)
{
	for (unsigned int i = 0; i < m_BatsContainer.size(); i++)
	{
		if (m_BatsContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_BatsContainer.push_back(a_Platform);
}

void BatsManager::operator-=(Bats *a_Platform)
{
	for (unsigned int i = 0; i < m_BatsContainer.size(); i++)
	{
		if (m_BatsContainer[i] == a_Platform)
		{
			return;
		}
	}
	m_BatsContainer.push_back(a_Platform);
}

Bats * BatsManager::operator[](unsigned int a_Index)
{
	if (a_Index > 0 && a_Index < m_BatsContainer.size())
	{
		return m_BatsContainer[a_Index];
	}
	return nullptr;
}

void BatsManager::Generate()
{
	for (unsigned int i = 0; i < 5; i++)
	{
		*(this) += new Bats(cocos2d::Vec2(i * 600, 830.0f), 30.0f, 75.0f, 14u, false);
		m_Scene->addChild(m_BatsContainer[m_BatsContainer.size() - 1]->m_Circle.getPrimitive());
	}
}

void BatsManager::Update(float dt)
{
	for (unsigned int i = 0; i < m_BatsContainer.size(); i++)
	{
		m_BatsContainer[i]->Update(dt);
	}
}

Bats::Bats(const cocos2d::Vec2 & a_StartPosition, const float & a_Radius, const float & a_Angle, const unsigned int & a_Segments, const bool & a_DrawLineToCenter)
	: m_Circle(a_StartPosition, a_Radius, a_Angle, a_Segments, a_DrawLineToCenter)
{
}

void Bats::Update(float dt)
{
	//m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY() - 3);
	if (m_Circle.getPrimitive()->getPositionY() > m_Circle.getPrimitive()->getPositionY() - 50)
	{
		m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY() - 3);
	}
	else if (m_Circle.getPrimitive()->getPositionY() < m_Circle.getPrimitive()->getPositionY() + 50)
	{
		m_Circle.getPrimitive()->setPosition(m_Circle.getPrimitive()->getPositionX() - 5, m_Circle.getPrimitive()->getPositionY() + 3);
	}
	/*Vec2 l_tmp = m_Circle.getPrimitive()->getPosition();
	m_Circle.getPrimitive()->setPosition(l_tmp + m_Direction * m_Speed * dt);*/
}

//MovingBats::MovingBats(const cocos2d::Vec2 & a_StartPosition, const float & a_Radius, const float & a_Angle, const unsigned int & a_Segments, const bool & a_DrawLineToCenter, 
//	const cocos2d::Vec2 & a_TravStartPoint, const cocos2d::Vec2 & a_TravEndPoint, const float a_Speed)
//	: Bats(a_StartPosition, a_Radius, a_Angle, a_Segments, a_DrawLineToCenter)
//{
//	m_TravStartPoint = a_TravStartPoint;
//	m_TravEndPoint = a_TravEndPoint;
//	m_Speed = a_Speed;
//
//	m_Magnitude = a_TravStartPoint.getDistance(a_TravEndPoint);
//	cocos2d::Vec2 l_Temp = (a_TravEndPoint - a_TravStartPoint);
//	l_Temp.normalize();
//	m_Direction = l_Temp;
//}

//void MovingBats::update(float a_DeltaTime)
//{
//	Vec2 l_tmp = m_Circle.getPrimitive()->getPosition();
//	if (m_Reverse)
//	{
//		m_Circle.getPrimitive()->setPosition(l_tmp + m_Direction * m_Speed * a_DeltaTime);
//		if (l_tmp.getDistance(m_TravEndPoint) > m_Magnitude)
//		{
//			m_Reverse = !m_Reverse;
//			m_Direction = -m_Direction;
//		}
//	}
//	else
//	{
//		m_Circle.getPrimitive()->setPosition(l_tmp + m_Direction * m_Speed * a_DeltaTime);
//		if (l_tmp.getDistance(m_TravStartPoint) > m_Magnitude)
//		{
//			m_Reverse = !m_Reverse;
//			m_Direction = -m_Direction;
//		}
//	}
//}
