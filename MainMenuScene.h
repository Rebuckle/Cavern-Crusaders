#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#include "cocos2d.h"
using namespace cocos2d;

class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);

	cocos2d::Sprite *mySprite;

	void StartGame(Ref *pSender);
	void Instructions(Ref *pSender);
	void ExitGame(Ref *pSender);
};

#endif // !__MAINMENU_SCENE_H__
