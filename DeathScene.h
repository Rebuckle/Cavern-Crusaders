#ifndef __DEATH_SCENE_H__
#define __DEATH_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class DeathScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(DeathScene);

	cocos2d::Sprite *mySprite;

	void GameReturn(Ref *pSender);
	void MenuReturn(Ref *pSender);
	void ExitGame(Ref *pSender);
	void getScore(float score);

	cocos2d::Label *scoreCount;
	float p_score;
};

#endif // !__DEATH_SCENE_H__
