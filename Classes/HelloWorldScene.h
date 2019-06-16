#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#include "cocos2d.h"
#include<typeinfo>
#include"Hero.h"
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
	//英雄和小兵单位
	Hero* hero;
	Hero* _hero;
	Hero* soldier_7;
	Hero* soldier_8;
	Hero* soldier_9;
	Hero* _soldier_7;
	Hero* _soldier_8;
	Hero* _soldier_9;

	int counter = 0;
	//英雄计时器
	TimeCounter* HeroTimeCounter;
	TimeCounter* DeadTime;
	TimeCounter* skillTimeCounter;
	TimeCounter* _heroAttack;
	TimeCounter* _heroDeath;
	TimeCounter* buff;

	//小兵计时器
	TimeCounter* Attack_7;
	TimeCounter* Attack_8;
	TimeCounter* Attack_9;
	TimeCounter* _Attack_7;
	TimeCounter* _Attack_8;
	TimeCounter* _Attack_9;

	TimeCounter* Death_7;
	TimeCounter* Death_8;
	TimeCounter* Death_9;
	TimeCounter* _Death_7;
	TimeCounter* _Death_8;
	TimeCounter* _Death_9;

	//野怪计时器
	TimeCounter* Death_monster;

	int _heroLife;

	//英雄技能
	TimeCounter* Atk;
	TimeCounter* Skill_Q;
	TimeCounter* Skill_W;
	TimeCounter* Skill_E;
	TimeCounter* Skill_R;

	//英雄血条和技能特效等
	Sprite* sprBar;
	Sprite* sprBar2;
	Sprite* sprBlood;
	Sprite* Effect_Q;
	Sprite* Effect_W;
	Label* label;
	Label* _label;

	//UI菜单
	MenuItemImage* outButton;
	ProgressTimer* progress;
	ProgressTimer* progress2;

	//AI血条和技能特效等
	Sprite* _sprBar;
	Sprite* _sprBar2;
	Sprite* _sprBlood;
	Sprite* _sprMagic;
	ProgressTimer* _progress;
	ProgressTimer* _progress2;

	//小兵
	Sprite* sprBar_7;
	Sprite* sprBar_8;
	Sprite* sprBar_9;
	Sprite* _sprBar_7;
	Sprite* _sprBar_8;
	Sprite* _sprBar_9;
	Sprite* sprBlood_7;
	Sprite* sprBlood_8;
	Sprite* sprBlood_9;
	Sprite* _sprBlood_7;
	Sprite* _sprBlood_8;
	Sprite* _sprBlood_9;
	ProgressTimer* progress_7;
	ProgressTimer* progress_8;
	ProgressTimer* progress_9;
	ProgressTimer* _progress_7;
	ProgressTimer* _progress_8;
	ProgressTimer* _progress_9;

	//野怪血条
	Sprite* spr_monster;
	Sprite* sprblood_monster;
	ProgressTimer* progress_monster;

	static cocos2d::Scene* createScene(int ID);
	virtual bool init();
	virtual void update(float dt);
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	cocos2d::Color4B getColor(int x, int y);
	CREATE_FUNC(HelloWorld);
	virtual void onKeyPressed(EventKeyboard::KeyCode keycode, Event* event);
	virtual void onKeyReleased(EventKeyboard::KeyCode keycode, Event* event);
	void win();
	void lose();
	void Shop(Ref* psender);

	//子弹
	vector<Sprite*> bullet;
	vector<Sprite*> bullett;
	vector<Sprite*> bullett7;
	vector<Sprite*> bullett8;
	vector<Sprite*> bullett9;
	vector<Sprite*> _bullett7;
	vector<Sprite*> _bullett8;
	vector<Sprite*> _bullett9;
	vector<Sprite*> _bullett;
	vector<Tower*> tower;
	vector<TimeCounter*> timec;

	string level;
	string _level;
	int choice = 2;
};



#endif // __HELLOWORLD_SCENE_H_