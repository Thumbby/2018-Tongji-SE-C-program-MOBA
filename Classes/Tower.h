#include "cocos2d.h"
#include "Hero.h"
using namespace cocos2d;
class Tower :public Hero
{
public:
	virtual bool init();
	void update();
	CREATE_FUNC(Tower);
	Sprite* tower;
	float Attack;
	float HP;
	float MaxHP;
	float range;
	bool isAttack;
	Sprite* sprBar;
	Sprite* sprBlood;
	ProgressTimer* progress;
};