#include "cocos2d.h"
#include "Hero.h"
using namespace cocos2d;
class Tower:public Layer
{	
public:
		virtual bool init();
	    void update();
        CREATE_FUNC(Tower);
	Sprite* tower;
	int Attack;
	int HP;
	int MaxHP;
	int range;

	Sprite* sprBar;

	Sprite* sprBlood;

	ProgressTimer* progress;



	

};
