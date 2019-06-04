#ifndef __MONSTER_SCENE_H__
#define __MONSTER_SCENE_H__
#include "cocos2d.h"
USING_NS_CC;

class Monster : public Layer
{
public:
	int isAlive = 1;
	int isAttacked = 0;
	int monsterHp = 1000;
	int direction;
	Point position;
	Sprite* sprite;
	static Monster* createMonsterSprite(Point position, int direction, const char* action);
	void monsterInit(Point position, int direction, const char* action);
	virtual bool init();
	void runAttack(Monster* enemy);
	void doAttack();
	void runBack();
	void doStand();
	void beAttacked(float dt);
	void waiting();
	void waitingAttack();
	void waitingUpdate(float dt);
	Animate* createAnimate(int direction, const char *action, int num,int time);
	//void setAction(int direction, const char *action, int num);
	CREATE_FUNC(Monster);
};
#endif