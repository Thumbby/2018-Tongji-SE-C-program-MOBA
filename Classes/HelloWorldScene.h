#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include"HRocker.h"
#include"Hero.h"
#include "Monster.h"
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
private:Sprite* background;
		Point pos;
		int nowDirection = 0;
		int flag = 0;
public:
	Image* image;

	//Sprite* background2;
	HRocker* rocker;
	Hero* hero;
	Monster* monster;
	Monster* monster2;
	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void update(float dt);
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	cocos2d::Color4B getColor(int x, int y);

	CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H_