#ifndef __HELLOWORLD_SCENE_H__

#define __HELLOWORLD_SCENE_H__



#include "cocos2d.h"

#include"Hero.h"

#include "Monster.h"

#include "Tower.h"

#include "TimeCounter.h"

#include <vector>
USING_NS_CC;
using namespace std;


class HelloWorld : public cocos2d::Layer

{

private:Sprite* background, mouse;

		Point pos;

		int nowDirection = 0;

		int flag = 0;

public:

	int ID = 0;

	Image* image;

	//Sprite* background2;

	Hero* hero;

	int counter = 0;

	Monster* monster;

	Monster* solider;

	Vector<Monster*> m_soliderManager;
	//TimeCounter* soliderTimeCounter;

	TimeCounter* m_timeCounter;

	TimeCounter* soliderTimeCounter;

	TimeCounter* HeroTimeCounter;

	TimeCounter* skillTimeCounter;

	TimeCounter* Atk;

	TimeCounter* Skill_Q;

	TimeCounter* Skill_W;

	TimeCounter* Skill_R;

	Sprite* sprBar;

	Sprite* sprBar2;

	Sprite* sprBlood;

	Sprite* Effect_Q;

	Tower* tower;

	Label* label;

	MenuItemImage* outButton;

	ProgressTimer* progress;

	ProgressTimer* progress2;

	static cocos2d::Scene* createScene(int ID);

	virtual bool init();

	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);

	cocos2d::Color4B getColor(int x, int y);

	CREATE_FUNC(HelloWorld);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	virtual bool onContactBegin(const PhysicsContact& contact);

	void Shop(Ref* psender);

	vector<Sprite*> bullet;

	PhysicsWorld* m_world;

	void setPhyWorld(PhysicsWorld* world) { m_world = world; };

	int choice = 0;
};



#endif // __HELLOWORLD_SCENE_H_