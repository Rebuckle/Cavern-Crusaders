#ifndef  PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
	static Player * create();
	void update();
	void initPlayer();
	~Player();

	//movement
	void move(int directionVal);
	void idle();

	//variables
	Animate * idleAnimate;
	Animate * runAnimate;

	bool moving;
	int direction;
};

#endif // ! PLAYER_H_
