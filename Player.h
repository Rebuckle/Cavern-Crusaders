#ifndef  PLAYER_H_
#define PLAYER_H_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite
{
public:
	static Player * create();
	void update();
	void initPlayer(Player * character);
	~Player();

	//movement
	void move(int directionVal);
	void idle();
	void jump();

	//variables
	//Player * character;

	Animate * idleAnimate;
	Animate * runAnimate;
	Animate * jumpAnimate;

	cocos2d::PhysicsBody *playerPhys;

	bool moving, jumping, falling;
	int direction;
};

#endif // ! PLAYER_H_
