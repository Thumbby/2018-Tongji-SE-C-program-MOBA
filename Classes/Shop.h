#ifndef __SHOP_H__
#define __SHOP_H__

#include "cocos2d.h"

class Shop : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menuOut(Ref* psender);
	void menuIn(Ref* psender);
	void buildScene1();
	void buildScene2();
	CREATE_FUNC(Shop);

};

#endif // __HELLOWORLD_SCENE_H__