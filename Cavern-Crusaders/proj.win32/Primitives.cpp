#include "Primitives.h"
#include "2d/CCDrawNode.h"

//initialize List
/////Square//////
BathMat::PrimitiveSquare::PrimitiveSquare(const cocos2d::Vec2 & a_StartPostion, const cocos2d::Vec2 & a_EndPostion)
	: m_Node(cocos2d::DrawNode::create())
{
	//drawing primitive square
	m_Node->drawRect(a_StartPostion, a_EndPostion, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
}

BathMat::PrimitiveSquare::PrimitiveSquare()
{
	//realse the memory
	m_Node->release();
}

cocos2d::DrawNode * BathMat::PrimitiveSquare::getPrimitive()
{
	return m_Node;
}
////////////////


/////Cricle/////
BathMat::PrimitiveCricle::PrimitiveCricle(const cocos2d::Vec2 & a_StartPostion, const float & a_Radius)
	: m_Node(cocos2d::DrawNode::create())
{
	//drawing primitive cricle 
	m_Node->drawDot(a_StartPostion, a_Radius, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
}

BathMat::PrimitiveCricle::PrimitiveCricle()
{
	//realse the memory
	m_Node->release();
}

cocos2d::DrawNode * BathMat::PrimitiveCricle::getPrimitive()
{
	return m_Node;
}
///////////////

/////Capuslse/////
BathMat::PrimitiveCapsualse::PrimitiveCapsualse(const cocos2d::Vec2 & a_StartPostion, const cocos2d::Vec2 & a_EndPostion, const cocos2d::Vec2 &a_Startoffset, const cocos2d::Vec2 &a_Endoffset, const float & a_Radius)
	: m_Node(cocos2d::DrawNode::create())
{
	//drawing primitive Capsualse
	m_Node->drawDot(a_StartPostion, a_Radius, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	m_Node->drawDot(a_EndPostion, a_Radius, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
	m_Node->drawLine(a_StartPostion - a_Startoffset, a_EndPostion - a_Endoffset, cocos2d::Color4F(1.0f, 0.0f, 0.0f,1.0f));
	m_Node->drawLine(a_StartPostion + a_Startoffset, a_EndPostion + a_Endoffset, cocos2d::Color4F(1.0f, 0.0f, 0.0f, 1.0f));
}

BathMat::PrimitiveCapsualse::PrimitiveCapsualse()
{
	//reaslse the memory of the class
	m_Node->release();
}

cocos2d::DrawNode * BathMat::PrimitiveCapsualse::getPrimitive()
{
	return m_Node;
}
/////////////////