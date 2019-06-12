#ifndef __HELLOWORLD_SCENE_H__

#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include<typeinfo>
#include"Hero.h"

#include "Monster.h"

#include "Tower.h"
#include <vector>
#include "TimeCounter.h"
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

	Hero* _hero;

	int counter = 0;

	Monster* monster;

	Monster* solider;

	Vector<Monster*> m_soliderManager;
	//TimeCounter* soliderTimeCounter;

	TimeCounter* m_timeCounter;

	TimeCounter* soliderTimeCounter;

	TimeCounter* HeroTimeCounter;

	TimeCounter* DeadTime;

	TimeCounter* skillTimeCounter;

	TimeCounter* _heroAttack;

	TimeCounter* _heroDeath;

	int _heroLife;

	TimeCounter* Atk;

	TimeCounter* Skill_Q;

	TimeCounter* Skill_W;

	TimeCounter* Skill_E;

	TimeCounter* Skill_R;

	Sprite* sprBar;

	Sprite* sprBar2;

	Sprite* sprBlood;

	Sprite* Effect_Q;

	Sprite* Effect_W;

	Label* label;

	MenuItemImage* outButton;

	ProgressTimer* progress;

	ProgressTimer* progress2;

	Sprite* _sprBar;

	Sprite* _sprBar2;

	Sprite* _sprBlood;

	ProgressTimer* _progress;

	ProgressTimer* _progress2;

	static cocos2d::Scene* createScene(int ID);

	virtual bool init();

	virtual void update(float dt);

	virtual bool onTouchBegan(Touch* touch, Event* unused_event);

	cocos2d::Color4B getColor(int x, int y);

	CREATE_FUNC(HelloWorld);

	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);

	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);

	void Shop(Ref* psender);

	vector<Sprite*> bullet;

	vector<Sprite*> bullett;

	vector<Tower*> tower;

	vector<TimeCounter*> timec;

	string level;

	int choice = 2;
};



#endif // __HELLOWORLD_SCENE_H_