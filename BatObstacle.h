#pragma once

#include <vector>
#include "Primitives.h"
#include "cocos2d.h"

USING_NS_CC;

class BatObstacle : public cocos2d::Sprite
{
public:
	static BatObstacle * create();
	~BatObstacle();
	double calcX(int init_Velocity, double angle);
	double calcY(int init_Velocity, double angle);
	void initBat(BatObstacle * batOb);
	void Update(float dt);
	void spawnBat();
	void delBat();

private:
	int init_Velocity = 20;
	double angle = 0.05;
	const double gravity = -9.801, PI = 3.141592654;
	double xPosition = 0, yPosition = 0;
	int distanceInterval = 0;
	bool batExist;
	Animate * batAnimate;
};