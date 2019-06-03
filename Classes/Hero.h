#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__
#include "cocos2d.h"
#include "Timecounter.h"
#include <map>
USING_NS_CC;
enum hero_direction
{
	FRONT = 1,
	RIGHT = 2,
	LEFT = 3,
	BACK = 4
};
class Hero : public Layer
{
public:
	friend class HelloWorld;
	friend class ShopLayer;
	bool isRun;
	int direction;
	int Max_Exp(int level);
	Point position;
	Sprite* sprite;
	static Hero* createHeroSprite(Point position, int direction, const char* name);
	void heroInit(Point position, int direction, const char* name);
	virtual bool init();
	Animate* createAnimate(int direction, const char* action, int num);
	void setAction(int direction, const char* action, int num);
	void moveTo(float x, float y);
	void Death();
	void Experience_System(int exp,int Level_Exp);
	void Money_System(int money);
	void Get_Attack(int damage);
	std::map<int, int>Weapon;
	CREATE_FUNC(Hero);
private:
	int ID;
	String name;
	int Money;
	float HP, MP;
	float HP_Recover, MP_Recover;
	int MaxHP = 100;
	int MaxMP = 100;
	float Attack, Skill_Enhance, Defense, Resistance;
	float  Attack_Speed, Attack_Range;
	int Exp,Level;
	float Critical_Rate;
	float speed = 5;
	float DeadTime;
	float RebornTime;
	int Reward_Money, Reward_Exp;
	int Skill_Q_On_Release;
	float Skill_Q_Cool_Down = 10;
	int Skill_W_On_Release;
	float Skill_E_Cool_Down = 10;
	int Skill_E_On_Release; 
};
#endif