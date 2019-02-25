#pragma once
//forward declaring
//our class uses Vec2 which is in cocos
namespace cocos2d
{
	class Vec2;
	class DrawNode;
}

namespace BathMat
{
	class PrimitiveSquare
	{
	public:
		//called when a object of PrimitiveSquare is called
		PrimitiveSquare(const cocos2d::Vec2 &a_StartPostion,const cocos2d::Vec2 &a_EndPostion);
		//called when an object Primite is destyred
		PrimitiveSquare();

		cocos2d::DrawNode *getPrimitive();
	private:
		//we use this to draw the square
		cocos2d::DrawNode *m_Node;
	};

	class PrimitiveCricle
	{
	public:
		//called when a object of primitive cricle is called by the program
		PrimitiveCricle(const cocos2d::Vec2 &a_StartPostion, const float &a_Radius);
		//called when an primitive cricle is destryed by the program
		PrimitiveCricle();

		cocos2d::DrawNode *getPrimitive();
	private:
		//we use this to draw the cricle 
		cocos2d::DrawNode *m_Node;
	};

	class PrimitiveCapsualse
	{
	public:
		//called when a object of primitive capsualse is called by the program
		PrimitiveCapsualse(const cocos2d::Vec2 &a_StartPostion,const cocos2d::Vec2 &a_EndPostion,const cocos2d::Vec2 &a_Startoffset, const cocos2d::Vec2 &a_Endoffset, const float &a_Radius);
		//called when an primitive capsualse is destryed by the program
		PrimitiveCapsualse();

		cocos2d::DrawNode *getPrimitive();
	private:
		//we use this to draw the capsualse
		cocos2d::DrawNode *m_Node;
	};
}