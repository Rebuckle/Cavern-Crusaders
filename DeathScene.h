#ifndef __DEATH_SCENE_H__
#define __DEATH_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class DeathScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(unsigned int tempScore);

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(DeathScene);

	cocos2d::Sprite *mySprite;

	void GameReturn(Ref *pSender);
	void MenuReturn(Ref *pSender);
	void ExitGame(Ref *pSender);
};

#endif // !__DEATH_SCENE_H__
