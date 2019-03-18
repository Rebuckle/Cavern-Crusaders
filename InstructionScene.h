#ifndef __INSTRUCTION_SCENE_H__
#define __INSTRUCTION_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class InstructionScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(InstructionScene);

	cocos2d::Sprite *mySprite;

	void Instructions(Ref *pSender);
	void MenuReturn(Ref *pSender);
};

#endif // !__INSTRUCTION_SCENE_H__
