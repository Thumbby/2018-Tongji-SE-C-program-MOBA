#ifndef __HERO_SCENE_H__
#define __HERO_SCENE_H__
#include "cocos2d.h"
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
	Point position;
	Sprite* sprite;
	static Hero* createHeroSprite(Point position, int direction, const char* name);
	void heroInit(Point position, int direction, const char* name);
	virtual bool init();
	Animate* createAnimate(int direction, const char* action, int num);
	void setAction(int direction, const char* action, int num);
	void moveTo(float x, float y);
	void Add_Price(int Money, int Exp) {
		Money_Num = Money_Num + Money;
		Exp_Num = Exp_Num + Exp;
	}
	void HP_Reduce(int Damage);
	std::map<int,int>Weapon;
	CREATE_FUNC(Hero);
private:
	int ID;
	String name;
	int Money,Money_Num;
	int HP, MP, HP_Recover, MP_Recover,Max_HP,Max_MP;
	int Attack, Skill_Enhance, Defense, Resistance;
	int  Attack_Speed, Attack_Range;
	int Exp, Exp_Num, Level,Max_Exp;
	float speed =3;
};
#endif
